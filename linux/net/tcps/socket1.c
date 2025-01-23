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
    if (sfd<0){
        perror("socket error\n");
        return -1;
    }  

    struct sockaddr_in serv;
    bzero(&serv,sizeof(serv));
    serv.sin_family =AF_INET;
    serv.sin_port = htons(9999);
    inet_pton(AF_INET,"192.168.1.10",&serv.sin_addr);
    int ret = bind(sfd,(struct sockaddr*)&serv,sizeof(serv));
    if(ret<0){
        perror("error\n");
        return -1;
    }
    listen(sfd,128);
   
    struct sockaddr_in client;
    socklen_t len = sizeof(client);

    int cfd = accept(sfd,(struct sockaddr*)&client,&len);
    char bufs[16];
    printf("Now we have connected\n");
    printf("the ip:%s,the port:%d\n",inet_ntop(AF_INET,&client.sin_addr.s_addr,bufs,sizeof(bufs)),ntohs(client.sin_port));



    printf("sfd = [%d],cfd = [%d]\n",sfd,cfd);
    int n = 0;
    char buf[1024];
    while(1){
        memset(buf,0x00,sizeof(buf));
        n = read(cfd,buf,sizeof(buf));
        if(n == 0){
            printf("the connect is break!\n");
            break;
        }
        printf("n = %d,buf = %s\n",n,buf);
        for(int i = 0;i<n;i++){
            buf[i] = toupper(buf[i]);
        }
        
        write(cfd,buf,n); 
    }

    close(sfd);
    close(cfd);

    return 0;
}
