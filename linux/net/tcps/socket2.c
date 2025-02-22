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
 *      struct sockaddr_in serv;
 *      serc.sin_family = AF_INERT;
 *      serv.sin_port = htons(8888);
 *      serv.sin_addr.serc_addr
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

// C 
int main(int argc,char*argv[]){
    int cfd = socket(AF_INET6,SOCK_STREAM,0);
    if(cfd<0){
        perror("socket error!\n");
        return -1;
    }
    struct sockaddr_in6 serv;
    serv.sin6_family =  AF_INET6;
    serv.sin6_port = htons(9999);
    inet_pton(AF_INET6,"2409:8a04:c10:d340:e59c:696c:b78a:bc1d",&serv.sin6_addr);
    int ret = connect(cfd,(struct sockaddr*)&serv,sizeof(serv));
    if(ret<0){
        perror("connect error!\n");
        return -1;
    }
    int n = 0;
    char buf[256];
    while(1){
        memset(buf,0x00,sizeof(buf));
        scanf("%s",buf);
        write(cfd,buf,sizeof(buf));

        memset(buf,0x00,sizeof(buf));
        n = read(cfd,buf,sizeof(buf));
        if(n<=0){
            printf("the connect is break\n");
            break;
        }
        printf("n = %d,buf = %s\n",n,buf);
    }
    close(cfd);
    return 0;
}
