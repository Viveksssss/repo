#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<assert.h>

#define BUFFER_SIZE 4096

/* 主状态机状态 */
enum CHECK_STATE {
    CHECK_STATE_REQUESTLINE = 0,  // 解析请求行
    CHECK_STATE_HEADER,           // 解析头部字段
    CHECK_STATE_CONTENT           // 解析消息体（本示例暂不实现）
};

/* 从状态机状态 */
enum LINE_STATUS {
    LINE_OK = 0,    // 完整行
    LINE_BAD,       // 错误行
    LINE_OPEN       // 不完整行
};

/* HTTP处理结果 */
enum HTTP_CODE {
    NO_REQUEST,         // 请求不完整
    GET_REQUEST,        // 获得完整请求
    BAD_REQUEST,        // 语法错误
    FORBIDDEN_REQUEST,  // 权限不足
    INTERNAL_ERROR,     // 内部错误
    CLOSED_CONNECTION   // 连接关闭
};
 
/* 从状态机：解析行内容 */
enum LINE_STATUS parse_line(char* buffer, int& checked_index, int& read_index) {
    for(; checked_index < read_index; ++checked_index) {
        char temp = buffer[checked_index];
        if(temp == '\r') {
            if((checked_index + 1) == read_index)
                return LINE_OPEN; // 请求不完整
            if(buffer[checked_index + 1] == '\n') {
                buffer[checked_index++] = '\0';
                buffer[checked_index++] = '\0';
                return LINE_OK; // 请求完整
            }
            return LINE_BAD;
        } else if(temp == '\n') {
            if(checked_index > 1 && buffer[checked_index - 1] == '\r') {
                buffer[checked_index-1] = '\0';
                buffer[checked_index++] = '\0';
                return LINE_OK; // 请求完整
            }
            return LINE_BAD; // 请求错误
        }
    }
    return LINE_OPEN; // 请求不完整
}

/* 解析请求行 */
enum HTTP_CODE parse_requestline(char* temp, enum CHECK_STATE& checkstate) {
    char* url = strpbrk(temp, " \t");
    if(!url) return BAD_REQUEST;
    *url++ = '\0'; //     *** 请求头 GET htt://www.baidu.com/index.html HTTP/1.1
    
    char* method = temp; // GET/POST 
    // OST
    if(strcasecmp(method, "GET") != 0)  // 仅支持GET方法
        return BAD_REQUEST; // 
        
    url += strspn(url, " \t");
    char* version = strpbrk(url, " \t");
    if(!version) return BAD_REQUEST;
    *version++ = '\0';
    
    version += strspn(version, " \t");
    if(strcasecmp(version, "HTTP/1.1") != 0)
        return BAD_REQUEST;
    
    checkstate = CHECK_STATE_HEADER;  // 转移至解析头部状态
    return NO_REQUEST;
}

/* 主处理函数 */
enum HTTP_CODE parse_content(char* buffer, int& checked_index, 
                            enum CHECK_STATE& checkstate, 
                            int& read_index, int& start_line) {
    enum LINE_STATUS linestatus = LINE_OK;
    
    while((linestatus = parse_line(buffer, checked_index, read_index)) == LINE_OK) {
        char* szTemp = buffer + start_line;
        start_line = checked_index;
        
        switch(checkstate) {
            case CHECK_STATE_REQUESTLINE: {
                enum HTTP_CODE retcode = parse_requestline(szTemp, checkstate);
                if(retcode == BAD_REQUEST)
                    return BAD_REQUEST;
                break;
            }
            case CHECK_STATE_HEADER: {
                if(szTemp[0] == '\0') {  // 遇到空行表示头部结束
                    return GET_REQUEST;
                }
                // 处理头部字段（此处可扩展）
                if(strncasecmp(szTemp, "Host:", 5) == 0) {
                    szTemp += 5;
                    szTemp += strspn(szTemp, " \t");
                    printf("Host: %s\n", szTemp);
                }
                break;
            }
            default:
                return INTERNAL_ERROR;
        }
    }
    
    if(linestatus == LINE_OPEN)
        return NO_REQUEST;
    else
        return BAD_REQUEST;
}

int main(int argc, char* argv[]) {
    if(argc <= 2) {
        printf("Usage: %s ip port\n", basename(argv[0]));
        return 1;
    }
    
    const char* ip = argv[1];
    int port = atoi(argv[2]);
    
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);
    
    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);
    
    int ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);
    
    ret = listen(listenfd, 5);
    assert(ret != -1);
    
    while(1) {
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        int connfd = accept(listenfd, (struct sockaddr*)&client, &client_len);
        if(connfd < 0) {
            perror("accept error");
            continue;
        }
        
        char buffer[BUFFER_SIZE];
        memset(buffer, '\0', BUFFER_SIZE);
        int data_read = 0;
        int read_index = 0;    // 已读数据位置
        int checked_index = 0; // 已解析数据位置
        int start_line = 0;    // 行起始位置
        
        enum CHECK_STATE checkstate = CHECK_STATE_REQUESTLINE;
        while(1) {
            data_read = recv(connfd, buffer + read_index, 
                            BUFFER_SIZE - read_index, 0);
            if(data_read == -1) {
                perror("recv error");
                break;
            } else if(data_read == 0) {
                printf("Remote connection closed\n");
                break;
            }
            read_index += data_read;
            
            enum HTTP_CODE result = parse_content(buffer, checked_index, 
                                                  checkstate, read_index, 
                                                  start_line);
            if(result == GET_REQUEST) {
                const char* ok_response = 
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html\r\n"
                    "\r\n"
                    "<html><body>"
                    "<p>Hello World</p>"
                    "<a href = \"ww.baidu.com\">sss</a>"
                    "</body></html>"
                    ;
                send(connfd, ok_response, strlen(ok_response), 0);
                break;
            } else if(result == BAD_REQUEST) {
                const char* bad_response = 
                    "HTTP/1.1 400 Bad Request\r\n"
                    "Content-Length: 0\r\n\r\n";
                send(connfd, bad_response, strlen(bad_response), 0);
                break;
            }
        }
        close(connfd);
    }
    close(listenfd);
    return 0;
}

