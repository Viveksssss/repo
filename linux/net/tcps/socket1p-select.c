
#include"./wrapp.c"
#include <asm-generic/socket.h>
#include <ctype.h>
#include <netdb.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>


/*
 * int select(int nfds,fd_set*readfds,fd_set*writefds,fd_set*exceptfds,struct timeval *timeout);
 * */

int main(int argc,char*argv[]){
    int fd = Socket(AF_INET,SOCK_STREAM,0);

    int opt = 1;
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int));
    struct sockaddr_in *adr = Init();
    Bind(fd,adr,sizeof(*adr));
    Listen(fd,128);

    fd_set readfds;
    fd_set tmpfds;
    
    FD_ZERO(&readfds);
    FD_ZERO(&tmpfds);

    FD_SET(fd,&readfds);
    

    int n;
    int maxfd = fd;
    int cfd;
    char buf[64];
    while(1){
        tmpfds = readfds;
        n = select(maxfd+1,&tmpfds,NULL,NULL,NULL);
        printf("n = %d\n",n);
        if(FD_ISSET(fd,&tmpfds)){
            cfd = accept(fd,NULL,NULL);
            FD_SET(cfd,&readfds);

            printf("%d\n",cfd);
            if(cfd>maxfd){
                maxfd = cfd;
            }
            if(--n){
                continue;
            }
        }
        for(int i = fd+1;i<=maxfd;i++){
            if(FD_ISSET(i,&tmpfds)){
                memset(buf,0x00,sizeof(buf));
                int len = read(i,buf,sizeof(buf));
                if(len<=0){
                    close(i);
                    FD_CLR(i,&readfds);
                    printf("client disconnect %d",i);
                    continue;
                }else{
                    printf("len = %d,buf = %s",len,buf);
                    for(int i = 0;i<len;i++){
                        buf[i] = toupper(buf[i]);
                    }
                    write(i,buf,sizeof(buf));
                }

                if(--n==0){
                    break;
                }
            }
        }
    }

    close(fd);
    return 0;
}
