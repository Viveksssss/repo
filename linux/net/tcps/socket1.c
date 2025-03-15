//c lib
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<memory.h>
#include<ctype.h>  

//sys lib
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<signal.h>
#include<pthread.h>
#include<sys/mman.h>
#include<time.h>
#include<sys/time.h>

//net lib
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<netdb.h>

/*
 * int socket(int domain,int type,int protocol);
    domain: 
        AF_INET ipv4
        AF_INET6 ipv6
        AF_UNIXAF_LOCAL
    type:
        SOCK_STREAM
        SOCK_DGARM
    protocal:
        0
 * 
 * */

/*
 * int bind(int sockfd,const struct sockaddr*addr,socklen_t addrlen);
 *
 *  sockfd:the return value of socker();
 *
 *  addr:ip/port 
 *    struct sockaddr_in serv;
 *      serc.sin_family = AF_INERT;
 *      serv.sin_port = htons(8888);
 *
 *  addrlen:the memort size of addr
 *  
 * */


/*
 *int listen(int sockfd,int backlog);
    sockfd:the return value of socket();

    backlog:the biggest num of connect

 * */


/*
 *int accept(int sockfd,struct sockaddr*addr,socklen_t*addrlen);

    addr:the address of client

    addrlen:the size of addr/the size of addr after function

 * */

/*
 *int connect(int sockfd,const struct sockaddr*addr,socklen_t addrlen);
       sockfd:
       addr:
       addrlen:
 * */

  
/*
 *ssize_t recv(int sockfd,void*buf,size_t len,int flags);    (read)

 *ssize_t send(int sockfd,const void*buf,size_t len,int flags);    (write)
 *
 * */

// B 
int main(int argc,char*argv[]){
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    int a = 1;
    setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,(char*)&a,sizeof(a));
    if (sfd<0){
        perror("socket error\n");
        return -1;
    }  

    struct sockaddr_in serv;
    bzero(&serv,sizeof(serv));
    serv.sin_family =AF_INET;
    serv.sin_port = htons(9999);
    inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr);
    int ret = bind(sfd,(struct sockaddr*)&serv,sizeof(serv));
    if(ret<0){
        perror("error\n");
        return -1;
    }
    listen(sfd,128);
   
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    while(1){
        int cfd = accept(sfd,(struct sockaddr*)&client,&len);

      
        int n = 0;
        char buf[4096];
        while(1){
            memset(buf,0x00,sizeof(buf));
            n = read(cfd,buf,sizeof(buf));
            if(n == 0){
                printf("the connect is break!\n");
                break;
            }else if(n < 0){
                break;
            }
            printf("n = %d,buf = %s\n",n,buf);
            memset(buf,0x00,sizeof(buf));
            strcpy(buf,"HTTP/1.1 200 OK\r\n"
                   "Content-Type:text/html\r\n"
                   "\r\n"
                   R"(<!DOCTYPE html><html><head><meta charset="utf-8" /><title>电商类型</title></head><body><form method="post"><table  border="" ><tr ><th colspan="" align="center">问卷调查</th></tr><tr><td>姓名:</td><td><input type="text" name="" id="" value="" /></td></tr><tr><td>密码:</td><td><input type="password" name="" id="" value="" /></td></tr><tr><td>性别:</td><td><input  type="radio" name="nv" id="" value="" />:男<input  type="radio" name="nv" id="" value="" />:女</td></tr><tr><td>学历:</td><td><select name=""><option value="">本科</option><option value="">高中</option><option value="">博士</option><!-- 输入法问题打不出来shuoshi --></select></td></tr><tr><td>爱好:</td><td><input type="checkbox" name="1" id="" value="" />读书<input type="checkbox" name="1" id="" value="" />打球<input type="checkbox" name="1" id="" value="" />游戏<input type="checkbox" name="1" id="" value="" />购物</td></tr><tr><td>头像:</td><td><input type="file" name="" id="" value="" /></td></tr><tr  height = "100px"><td>简介:</td><td><textarea rows="" cols=""></textarea></td></tr><tr><td colspan="2" align="center"><input type="button" name="" id="" value="重置" /><input type="button" name="" id="" value="提交" /></td></tr></table></form></body>

)");

            write(cfd,buf,n); 
        }
        close(cfd);
    }
    close(sfd);

    return 0;
}
