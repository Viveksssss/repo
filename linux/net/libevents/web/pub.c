#include "./pub.h"

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
int web_event.cppget_line(int sock, char *buf, int size)
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
