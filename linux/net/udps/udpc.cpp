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
    struct sockaddr_in addr;
    addr.sin_port = htons(9999);
    addr.sin_family = AF_INET;
    inet_pton(AF_INET,"192.168.1.10",&addr.sin_addr);
    
    socklen_t len = sizeof(addr); 
    struct sockaddr_in ll;
    char buf[64];
    char bufs[32];
    socklen_t pp = sizeof(ll);
    memset(bufs,0x00,sizeof(bufs));
    while(1){
        memset(buf,0x00,sizeof(buf));
        cin >> buf;
        sendto(cfd,buf,strlen(buf),0,(struct sockaddr*)&addr,sizeof(addr));
        memset(buf,0x00,sizeof(buf));
        int n = recvfrom(cfd,buf,sizeof(buf),0,(struct sockaddr*)&ll,&pp);

        cout << "recv mes from ip:"<<inet_ntop(AF_INET,&ll.sin_addr,bufs,sizeof(bufs)) << "port:"<< ntohs(ll.sin_port ) << "\n";
        cout << buf << "\n";
    }

    close(cfd);

    return 0;
}
