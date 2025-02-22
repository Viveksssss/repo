
#include"./wrapp.c"
#include <asm-generic/socket.h>
#include <signal.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/epoll.h>

/*
 *  int epoll_create(int size);
 *    TARGET:create an epoll instance
 *    RETURN:root of a tree(red-black tree) pointing to instance
 *
 *  int epoll_ctl(int epfd,int op,int fd,struct epoll_event*event);
 *    ARGS:
 *      epfd:the root of tree
 *      op:operations on the epoll
 *          EPOLL_CTL_ADD:add
 *          EPOLL_CTL_MOD:modify
 *          EPOLL_CTL_DEL:delete
 *      epoll_event:
 *          uint32_t events:epoll events
 *              EPOLLIN
 *              EPOLLOUT
 *              EPOLLERR
 *          epoll_data_t data:user data variable
 *              void *ptr
 *              int fd
 *              uint32_t u32
 *              uint64_t u64
 *    TARGET:add/delete/modify the fd and tree 
 *    
 *    RETURN:
 *      0:success
 *      -1:error
 *
 *    int epoll_wait(int epfd,struct epoll_event*events,int maxevents,int timeout); 
 *    ARGS:
 *        epfd:root of tree
 *        events:events of reveiced 
 *        maxevents:the size of events
 *        timeout:
 *            -1/0/>0
 *
 *    RETURN:
 *        the num of events
 * */



int main(int argc,char*argv[]){
    int fd = Socket(AF_INET,SOCK_STREAM,0);

    int opt = 1;
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int));
    struct sockaddr_in *adr = Init();
    Bind(fd,adr,sizeof(*adr));
    Listen(fd,128);

    int epfd = epoll_create1(0);

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = fd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&ev);

    struct epoll_event events[1024];
    char buf[64];
    memset(buf,0x00,sizeof(buf));
    int cfd;
    int sockfd;
    while(1){
        int n = epoll_wait(epfd,events,1024,-1);
        if(n<0){
            if(errno == EINTR){
                continue;
            }
            break;
        }

        for(int i = 0;i<n;i++){
            //1
            sockfd = events[i].data.fd;
            if(sockfd == fd){
                cfd = accept(fd,NULL,NULL);
                ev.data.fd = cfd;
                ev.events = EPOLLIN;
                epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&ev);
                continue;
            }
            //2
            int len = read(sockfd,buf,sizeof(buf));
            if(len<=0){
                close(sockfd);
                epoll_ctl(epfd,EPOLL_CTL_DEL,sockfd,NULL);
                perror("connect break...\n");
                continue;
            }
            printf("len = %d,buf = %s",len,buf);
            for(int i = 0;i<len;i++){
                buf[i] = toupper(buf[i]);
            }
            write(sockfd,buf,sizeof(buf));
        }
    }

    close(fd);
    return 0;
}
