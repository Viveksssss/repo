//web服务器程序-use epoll模型
#include <signal.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>

#include <sys/epoll.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>


#include "./wrap.h"
#include "./pub.h"


//处理http请求
int http_request(int cfd, int epfd);

int main(){
    //如果web服务器给浏览器发送数据的时候,浏览器关闭连接
    //则web服务器就会受到SIGPIPE信号,此时需要忽略
    struct sigaction act;
    act.sa_handler = SIG_IGN;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGPIPE, &act, NULL);

    //设置工作目录
    //改变当前进程的工作目录
        char path[255] = {0};
        sprintf(path, "%s/%s", getenv("HOME"), "webpath");
        chdir(path);

    //创建socket
    int lfd = tcp4bind(9999, NULL);
    
    //监听
    Listen(lfd, 128);

    //创建epoll树
    int epfd = epoll_create1(0);
    if(epfd <0 ){
        perror("epoll_create error\n");
        close(lfd);
        return -1;
    }

    //将监听文件描述符上epoll树
    struct epoll_event ev;
    ev.data.fd = lfd;
    ev.events = EPOLLIN;
    epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);

    int cfd;//通信描述符
    int sockfd;
    int n;
    struct epoll_event events[1025]; // 事件数组
    char buf[1024];
    while(1){
        n = epoll_wait(epfd, events, 1024, -1);
        if(n<0){
            if(errno == EINTR){
                continue;
            }
            break;
        }

        for (int i = 0; i < n;i++){
            sockfd = events[i].data.fd;
            if(sockfd == lfd){
                cfd = Accept(lfd, NULL, NULL);

                int flag = fcntl(cfd, F_GETFL, 0);
                fcntl(cfd, F_SETFL, flag | O_NONBLOCK);

                ev.data.fd = cfd;
                ev.events = EPOLLIN;
                epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
            }else{
                http_request(sockfd, epfd);
            }
        }
    }
}

int send_header(int cfd, char *code, char *msg, char *fileType, int len){
    char buf[1024] = {0};
        sprintf(buf, "HTTP/1.1 %s %s\r\n", code, msg);
        sprintf(buf+strlen(buf), "Content-Type:%s\r\n", fileType);
        if(len>0)
        {
            sprintf(buf+strlen(buf), "Content-Length:%d\r\n", len);
        }
        strcat(buf, "\r\n");
        write(cfd, buf, strlen(buf));
        return 0;
}

int send_file(int cfd, char *fileName){
   //打开文件
    int fd = open(fileName, O_RDONLY);
    if(fd<0)
    {
        perror("open error");
        return -1;
    }
    
    //循环读文件, 然后发送
    int n;
    char buf[1024];
    while(1)
    {
        memset(buf, 0x00, sizeof(buf));
        n = read(fd, buf, sizeof(buf));
        if(n<=0)
        {
            break;
        }
        else 
        {
            write(cfd, buf, n);
        }
    }
}

//处理http请求
int http_request(int cfd, int epfd){
    int n;
    char buf[1024];
    memset(buf, 0x00, sizeof(buf));
    n = Readline(cfd, buf, sizeof(buf));
    if(n<=0){
        Close(cfd);
        epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, NULL);
        return -1;
    }

    printf("buf = [%s]\n",buf);
    char reqType[16] = {0};
    char fileName[255] = {0};
    char protocal[16] = {0};
    sscanf(buf, "%[^ ] %[^ ] %[^ \r\n]", reqType, fileName, protocal);
    printf("--[%s]--\n", fileName);

    char *pFile = fileName;
    if(strlen(fileName)<=1){
        strcpy(pFile, "./");
    }else{
        pFile = fileName + 1;
    }

    //转换汉字编码
    strdecode(pFile, pFile);
    printf("[%s]\n",pFile);


    while(n = Readline(cfd, buf, sizeof(buf))>0);

    struct stat st;
    if(stat(pFile,&st)<0){
        printf("file not exist\n");

        send_header(cfd, "404", "Not Found", get_mine_type(".html"), 0);
        send_file(cfd, "error.html");
    }else{
        if(S_ISREG(st.st_mode)){
            printf("file exist\n");
            send_header(cfd, "200", "OK", get_mine_type(pFile), st.st_size);

            send_file(cfd, pFile);
        }else{
            printf("directory\n");
            char buffer[1024];
            send_header(cfd, "200", "OK", ".html", 0);
            send_file(cfd, "html/dir_header.htnl");
            struct dirent **namelist;

            int n = scandir(pFile, &namelist, NULL, alphasort);
            if(n<0){
                perror("scandir\n");
                close(cfd);
                epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, NULL);
                return -1;
            }else{
                while(n--){
                    printf("%s\n", namelist[n]->d_name);
                    memset(buffer, 0x00, sizeof(buffer));
                    if(namelist[n]->d_type == DT_DIR){
                        sprintf(buffer,"<li><a href=%s/>%s</a></li>", namelist[n]->d_name, namelist[n]->d_name);
                    }else{
                        sprintf(buffer,"<li><a href=%s>%s</a></li>", namelist[n]->d_name, namelist[n]->d_name);
                    }
                    free(namelist[n]);
                    write(cfd, buffer, strlen(buffer));
                }
                free(namelist);
            }
            sleep(5);
            send_file(cfd, "html/dir_footer.html");
        }
        return 0;
    }
}