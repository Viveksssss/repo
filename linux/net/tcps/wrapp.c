//c lib
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

void*doThing(void*args){
    int cfd = *(int*)args;
    char buf[256];
    while(1){
        memset(buf,0x00,sizeof(buf));
        int n = read(cfd,buf,sizeof(buf));
        if(n<=0){
            printf("connect exit...\n");
            break;
        }
        printf("n = [%d],buf = [%s]\n",n,buf);

        for(int i = 0;i<n;i++){
            buf[i] = toupper(buf[i]);
        }
        write(cfd,buf,sizeof(buf));
    }

    close(cfd);
    pthread_exit(NULL);
}

void Accept(int fd,struct sockaddr_in* address,socklen_t *lens){ 
    struct sockaddr_in adr;
    socklen_t len = sizeof(adr);
    char bufs[256];
    //pthread_t thread;//mutiple thread share cfd may cause wrong:we can use array to handle
    pthread_t thread[128];
    int k = -1;


    while(1){
        k++;
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

        pthread_create((thread+k),NULL,doThing,&cfd);
        //close(cfd);  !!!the main thread shouldn't close the cfd,because threads share the resources 
        pthread_detach(*(thread+k));

    }
}


