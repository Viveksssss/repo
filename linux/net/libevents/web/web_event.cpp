#include <sstream>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <event2/bufferevent.h>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <fcntl.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <event2/event.h>
#include <vector>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <string>


#define _DIR_PREFIX_FILE_ "./html/dir_header.html"
#define _DIR_TAIL_FILE_ "./html/dir_tail.html"

const char *get_mine_type(const char *name);
int get_line(int sock, char *buf, int size);
int hexit(char c);
void strencode(char *to, size_t tosize, const char *from);
void strdecode(char *to, char *from);
int copy_header(struct bufferevent *bev,int op,std::string msg,std::string filetype,long filesize);
void listener_cb(struct evconnlistener *listener, int fd, struct sockaddr *addr, int socklen, void *arg);
int copy_file(struct bufferevent *bev, const std::string strFile);
int send_dir(struct bufferevent *bev, const std::string strPath);
void read_cb(struct bufferevent*, void*ctx);
void bevent_cb(struct bufferevent *bev, short what,void*tmp);
int http_request(struct bufferevent *bev, std::string path);



const char *get_mine_type(const char *name)
{
    const char *dot;
    dot = strrchr(name, '.');
    if (dot == (char *)0)
    {
        return "text/plain; charset=utf-8";
    }
    if (strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0)
        return "text/html; charset=utf-8";
    if (strcmp(dot, ".jpg") == 0 || strcmp(dot, ".jpeg") == 0)
        return "image/jpeg";
    if (strcmp(dot, ".gif") == 0)
        return "image/gif";
    if (strcmp(dot, ".png") == 0)
        return "image/png";
    if (strcmp(dot, ".css") == 0)
        return "text/css";
    if (strcmp(dot, ".au") == 0)
        return "audio/basic";
    if (strcmp(dot, ".wav") == 0)
        return "audio/wav";
    if (strcmp(dot, ".avi") == 0)
        return "video/x-msvideo";
    if (strcmp(dot, ".mov") == 0 || strcmp(dot, ".qt") == 0)
        return "video/quicktime";
    if (strcmp(dot, ".mpeg") == 0 || strcmp(dot, ".mpe") == 0)
        return "video/mpeg";
    if (strcmp(dot, ".vrml") == 0 || strcmp(dot, ".wrl") == 0)
        return "model/vrml";
    if (strcmp(dot, ".midi") == 0 || strcmp(dot, ".mid") == 0)
        return "audio/midi";
    if (strcmp(dot, ".mp3") == 0)
        return "audio/mpeg";
    if (strcmp(dot, ".ogg") == 0)
        return "application/ogg";
    if (strcmp(dot, ".pac") == 0)
        return "application/x-ns-proxy-autoconfig";

    return "text/plain; charset=utf-8";
}
int cppget_line(int sock, char *buf, int size)
{
    int i = 0;
    char c = '\0';
    int n;
    while((i<size-1)&&(c!='\n')){
        n = recv(sock, &c, 1, 0);
        if(n>0){
            if(c == (char)'\r'){
                n = recv(sock, &c, 1, MSG_PEEK);//MSG_SEEK的作用是将套接字的读指针移到下一个可读位置，但不读取数据。
                if((n>0)&&(c == '\n'))
                    recv(sock, &c, 1, 0);
                else
                    c = '\n';
            }

            buf[i] = c;
            i++;
        }
        else{
            c = '\n';
        }
    }
    buf[i] = '\0';
    return (i);
}

//将字符转换成16进制
int hexit(char c)
{
        if (c >= '0' && c <= '9')
            return c - '0';
        if (c >= 'a' && c <= 'f')
            return c - 'a' + 10;
        if (c >= 'A' && c <= 'F')
            return c - 'A' + 10;
    
        return 0;
}
void strencode(char *to, size_t tosize, const char *from)
{
    int token;

    for (token = 0; *from != '\0' && token + 4 < tosize;++from){
        if(isalnum(*from) || strchr("/_.-~",*from)!=(char*)0){
            *to = *from;
            ++to;
            ++token;
        }else{
            sprintf(to, "%%%02x", (int)*from & 0xff);
            to += 3;
            token += 3;
        }
    }
    *to = '\0';
}
void strdecode(char *to, char *from)
{
    for ( ; *from != '\0'; ++to, ++from) {
    
            if (from[0] == '%' && isxdigit(from[1]) && isxdigit(from[2])) {
                *to = hexit(from[1])*16 + hexit(from[2]);//
                from += 2;                      //
            } else
                *to = *from;
        }
        *to = '\0';
}




int copy_header(struct bufferevent *bev, int op, std::string msg, std::string fileType, long fileSize){
    std::ostringstream oss;
    oss << "HTTP/1.1 " << op << " " << msg << "\r\n";
    oss << "Content-Type: " << fileType << "\r\n";

    if(fileSize >=0 ){
        oss << "Content-Length: " << fileSize << "\r\n";
    }
    oss << "\r\n";
    bufferevent_write(bev, oss.str().c_str(),oss.str().size());
    return 0;
}
int copy_file(struct bufferevent *bev, const std::string strFile){
    std::ifstream file(strFile, std::ios::in | std::ios::binary);
        if (!file) {
            std::cerr << "Failed to open file: " << strFile << std::endl;
            return -1;
        }
    
        file.seekg(0, std::ios::end);
        size_t fileSize = file.tellg();
        file.seekg(0, std::ios::beg);
    
        char* buffer = new char[fileSize];
        file.read(buffer, fileSize);
        file.close();
    
        bufferevent_write(bev, buffer, fileSize);
        delete[] buffer;
        return 0;
}
int send_dir(struct bufferevent *bev, const std::string strPath){
    copy_file(bev, _DIR_PREFIX_FILE_);
    struct dirent **dir;
    int num = scandir(strPath.c_str(), &dir, 0, alphasort);
    if(num < 0){
        std::cerr << "scandir error\n";
        return -1;
    }else {
        char buffer[1024] = {0};
        while (num--)
        {
            struct stat st;
            std::string fullpath = strPath + "/" + dir[num]->d_name;
            stat(fullpath.c_str(), &st);
            if (S_ISREG(st.st_mode))
            {
                memset(buffer, 0x00, sizeof(buffer));
                sprintf(buffer, "<li><a href='%s'>%32s</a>    %8ld</li>", dir[num]->d_name, dir[num]->d_name, st.st_size);
                bufferevent_write(bev, buffer, strlen(buffer));
            }
            else if (S_ISDIR(st.st_mode))
            {
                memset(buffer, 0x00, sizeof(buffer));
                sprintf(buffer, "<li><a href='%s/'>%32s</a>    %8ld</li>", dir[num]->d_name, dir[num]->d_name, st.st_size);
                bufferevent_write(bev, buffer, strlen(buffer));
            }
        }
    }
    copy_file(bev, _DIR_TAIL_FILE_);
    free(dir);
    return 0;
}

void read_cb(struct bufferevent *bev, void*ctx){
    struct event_base *base = (struct event_base *)ctx;
    char buffer[1024] = {0};
    char method[10], path[1024], protocol[10];
    int n = bufferevent_read(bev, buffer, sizeof(buffer));
    if(n > 0){
        std::istringstream iss(buffer);
        iss >> method >> path >> protocol;
        if(strcasecmp(method,"get") == 0){
            char bufline[256];
            write(STDOUT_FILENO, buffer, n);

            while((n == bufferevent_read(bev, bufline, sizeof(bufline)) )> 0){
                write(STDOUT_FILENO, bufline, n);
            }
            http_request(bev, path);
        }
    }
}
void bevent_cb(struct bufferevent *bev, short what,void*tmp){
    if(what & BEV_EVENT_EOF){
        std::cout << "client closed\n";
        bufferevent_free(bev);
    }else if(what&BEV_EVENT_ERROR){
        std::cerr << "client closed with error\n";
    }else if(what&BEV_EVENT_CONNECTED){
        std::cout << "client connected\n";
    }
}
void listener_cb(struct evconnlistener *listener, int fd, struct sockaddr *addr, int socklen, void *arg)
{
    //定义与客户端通信的bufferevent
    struct event_base *base = (struct event_base *)arg;
    struct sockaddr_in *client = (struct sockaddr_in *)addr;
    std::cout << "client ip:" << inet_ntoa(client->sin_addr) << " port:" << ntohs(client->sin_port) << std::endl;
    struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev,read_cb,NULL,bevent_cb,base);//设置回调
    bufferevent_enable(bev,EV_READ|EV_WRITE);//启用读和写
}


int http_request(struct bufferevent *bev, std::string path){
    int i = 0;
    int j = 0;
    for (; j < path.size();i++,j++){
        if(path[j] == '%'&&isxdigit(path[j+1])&&isxdigit(path[j+2])){
            path[i] = hexit(path[j+1])*16 + hexit(path[j+2]);
            j+=2;
        }else{
            path[i] = path[j];
        }
    }
    path.resize(i);

    std::string strPath = path;
    if (strPath == "/" )
    {
        strPath = "./";
    }
    else
    {
        strPath = path.substr(1);
    }

    struct stat sb;
    if (stat(strPath.c_str(), &sb) < 0)
    {
        copy_header(bev, 404, "NOT_FOUND", get_mine_type("error.html"), -1);

        copy_file(bev, "error.html");
        return -1;
    }
    if(S_ISDIR(sb.st_mode)){
        copy_header(bev, 200, "OK", get_mine_type("ww.html"), sb.st_size);
        send_dir(bev, strPath);
    }
    if(S_ISREG(sb.st_mode)){(
        copy_header(bev, 200, "OK", get_mine_type(strPath.c_str()), sb.st_size));
        copy_file(bev, strPath);
    }
    return 0;
}

int main(int argc,char *argv[])
{
    char workdir[] = "/home/vivek/webpath";
    chdir(workdir);
    struct event_base *base = event_base_new();//创建根节点
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(9999);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    struct evconnlistener * listener =evconnlistener_new_bind(base,
                                     listener_cb, base, LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE, -1,
                                                        (struct sockaddr *)&serv, sizeof(serv));//连接监听器
    

    event_base_dispatch(base);//循环

    event_base_free(base); //释放根节点
    evconnlistener_free(listener);//释放链接监听器
    return 0;
}
