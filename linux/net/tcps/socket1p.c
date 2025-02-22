
#include"./wrapp.c"
#include <asm-generic/socket.h>
#include <signal.h>
#include <sys/socket.h>
#include <unistd.h>


//port reuse:   int setsockopt(int sockfd,int level,int option,const void*val,socklen_t len);
/*
 *  setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int));
 * */

int main(int argc,char*argv[]){
    int fd = Socket(AF_INET,SOCK_STREAM,0);

    int opt = 1;
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int));
    struct sockaddr_in *adr = Init();
    Bind(fd,adr,sizeof(*adr));
    Listen(fd,128);
    Accept(fd,NULL,NULL);



    return 0;
}
