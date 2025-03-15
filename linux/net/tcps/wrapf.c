#ifndef __HHH
#define __HHH


//c lib
#include <bits/types/sigset_t.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<memory.h>
#include<errno.h>

//sys lib
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<signal.h>
#include<pthread.h>
#include<sys/mman.h>
#include<time.h>
#include<sys/time.h>
#include<sys/wait.h>

//net lib
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<netdb.h>


int Socket(int domain,int type,int protocol){
    int fd = socket(domain,type,protocol);
    if(fd<0){
        perror("socket error!\n");
        return -1;
    }
    return fd;
}

struct sockaddr_in* Init(){
    static struct sockaddr_in adr;
    bzero(&adr,sizeof(adr));
    adr.sin_family = AF_INET;
    adr.sin_port = htons(9999);
    inet_pton(AF_INET,"127.0.0.1",(struct sockaddr*)&adr.sin_addr);
    return &adr;
}

void Bind(int fd,struct sockaddr_in*adr,int len){
    again:
    int n = bind(fd,(struct sockaddr*)adr,len);
    if(n == -1){
        perror("bind error!\n");
        goto again;
    }
}


int Listen(int fd,int len){
    int n = listen(fd,len);
    if(n==-1){
        perror("listen error!\n");
        return -1;
    }
    return 0;
}
void waitchild(){
    pid_t wpid;
    int wstatus;
    while((wpid = waitpid(-1,&wstatus,WNOHANG))>0){
        if (WIFEXITED(wstatus)) {
            printf("Child process %d exited with status %d\n", wpid, WEXITSTATUS(wstatus));
        } else if (WIFSIGNALED(wstatus)) {
            printf("Child process %d was killed by signal %d\n", wpid, WTERMSIG(wstatus));
        }
    }

}


void Accept(int fd,struct sockaddr_in* address,socklen_t *lens){ 
        struct sockaddr_in adr;
        socklen_t len = sizeof(adr);
        char bufs[256];
    while(1){
        again:
        int cfd = accept(fd,(struct sockaddr*)&adr,&len);
        if(cfd<0){
            if(errno == EINTR || errno == ECONNABORTED){
                goto again;
            }
            else return;
        }
        memset(bufs,0x00,sizeof(bufs));
        printf("connect with ip = %s , port = %d",inet_ntop(AF_INET,&adr.sin_addr.s_addr,bufs,sizeof(bufs)),ntohs(adr.sin_port));
      
        pid_t pid = fork();
        if(pid<0){
            perror("fork error!\n");
            break;
        }
        else if(pid>0){
            struct sigaction act;
            act.sa_handler = waitchild;
            act.sa_flags = 0;
            sigemptyset(&act.sa_mask);
            sigaction(SIGCHLD,&act,NULL);

            sigset_t mask;
            sigemptyset(&mask);
            sigaddset(&mask,SIGCHLD);
            sigprocmask(SIG_UNBLOCK,&mask,NULL);


            close(cfd);
        }
        else{
            

            close(fd);
            while(1){
               
                char buf[256];
                memset(buf,0x00,sizeof(buf));
                int n = read(cfd,buf,sizeof(buf));
                if(n<=0){
                    printf("connect break...\n");
                    exit(0);
                }
                printf("n = %d,buf = %s\n",n,buf);
                for(int i = 0;i<n;i++){
                    buf[i] = toupper(buf[i]);
                }
                write(cfd,buf,sizeof(buf));
            }
            close(cfd);
            exit(0);
        }

    }
}


#endif 
