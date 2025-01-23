
#include"./wrapp.c"
#include <asm-generic/socket.h>
#include <ctype.h>
#include <netdb.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>


/*
 * int select(int nfds,fd_set*readfds,fd_set*writefds,fd_set*exceptfds,struct timeval *timeout);
 * */

#define N 128;

typedef struct node{
    int fd;
    struct node*next;
}list;

list *head = NULL;
list *p = NULL;


void push(int x){
    struct node*p = (struct node*)malloc(sizeof(list));
    p->fd = x;
    p->next = head->next;
    head->next = p;
}


int main(int argc,char*argv[]){
    head = (list*)malloc(sizeof(list)); 
    head->next = NULL;
    p = head;

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
            push(cfd);
            printf("%d\n",cfd);
            if(cfd>maxfd){
                maxfd = cfd;
            }
            if(--n){
                continue;
            }
        }
        list*pre = head;
        for(p = head->next;p!=NULL;pre = pre->next,p = p->next){
            if(FD_ISSET(p->fd,&tmpfds)){
                memset(buf,0x00,sizeof(buf));
                int len = read(p->fd,buf,sizeof(buf));
                if(len<=0){
                    close(p->fd);
                    FD_CLR(p->fd,&readfds);
                    pre ->next = pre->next->next;
                    printf("client disconnect %d",p->fd);
                    continue;
                }else{
                    printf("len = %d,buf = %s",len,buf);
                    for(int i = 0;i<len;i++){
                        buf[i] = toupper(buf[i]);
                    }
                    write(p->fd,buf,sizeof(buf));
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
