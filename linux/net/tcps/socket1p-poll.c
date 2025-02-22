
#include"./wrapp.c"
#include <asm-generic/socket.h>
#include <signal.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>


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


    int maxi = 0;
    int n;
    int cfd;
    int k;
    struct pollfd client[1024];
    client[0].fd = fd;
    client[0].events = POLL_IN;
    for(int i = 1;i<1024;i++){
        client[i].fd = -1;
    }


    while(1){
        n = poll(client,maxi+1,-1);

        if(n<0){
            if(errno == EINTR){
                continue;
            }
            break;
        }
        if(client[0].revents & POLL_IN){

            if((cfd = accept(fd,NULL,NULL))<0){
                perror("accept fail\n");
                continue;
            }
            int i;
            for(i = 0;i<1024;i++){
                if(client[i].fd == -1){
                    client[i].fd = cfd;
                    client[i].events = POLL_IN;
                    break;
                }
            }
            if(i==1024){
                close(cfd);
                continue;
            }
            if(maxi<i){
                maxi = i;
            }
        }
        char buf[64];
        for(k = 1;k<=maxi;k++){
            if(client[k].fd == -1){
                continue;
            }
            if(client[k].revents & POLL_IN){
                memset(buf,0x00,sizeof(buf));
                int len = read(client[k].fd,buf,sizeof(buf));
                if(len <= 0){
                    close(client[k].fd);
                    client[k].fd = -1;
                }
                else{
                    printf("n = %d,buf = %s",n,buf);
                    for(int j = 0;j<len;j++){
                        buf[j] = toupper(buf[j]);
                    }
                    write(client[k].fd,buf,sizeof(buf));
                }
                
            }

        }

        
    }
    
    close(fd);



    return 0;
}
