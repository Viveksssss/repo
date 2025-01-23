//cpp lib
#include <cctype>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<memory.h>
#include<iostream>

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


/*  reveive message
 *  ssize_t recvfrom(int sockfd,void*buf,size_t len,int flags,struct sockaddr*src_addr,socklen_t*addrlen);
 *      ARGS:
 *          flags:default is 0
 *
 *          src_addr:out parameter
 *
 *          addrlen:the size of accept
 *      RETURN:
 *          successfully:the size of we received
 *
 *          error:-1
 *
 *
 *  sent message
 *  ssize_t sendto(int sockfd,const void*buf,size_t len,int flags,const struct sockaddr*dest_addr,socklen_t addrlen);
 *      ARGS:
 *          dest_addr:the destination address
 *
 *          addrlen:the size of writen
 *
 *      RETURN:
 *          successfully:the size of we writen
 *
 *          error:-1
 * */

using namespace std;

int main(int argc,char*argv[]){
    int cfd = socket(AF_INET,SOCK_DGRAM,0);
    int ret;
    struct sockaddr_in addr;
    addr.sin_port = htons(9999);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if((ret = bind(cfd,(struct sockaddr*)&addr,sizeof(addr))) == -1){
        perror("bind error!\n");
        return -1;
    }

    char buf[64];
    memset(buf,0x00,sizeof(buf));
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    char bufs[32];
    while(1){
        int n =recvfrom(cfd,buf,sizeof(buf),0,(struct sockaddr*)&client,&len);
        std::cout  << "received message from ip:" << inet_ntop(AF_INET,&client.sin_addr,bufs,sizeof(bufs)) << "\t"<<"port:"<< ntohs(client.sin_port) <<"\n";
        for(int i = 0;i<n;i++){
            buf[i] = toupper(buf[i]);
        }
        //UDP 是无连接协议，每次通信都需要明确指定目标地址。
        sendto(cfd,buf,n,0,(struct sockaddr*)&client,len);
    }
    close(cfd);


    return 0;
}
