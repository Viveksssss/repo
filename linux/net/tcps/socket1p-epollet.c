#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <strings.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define TREE_NODE 1024
#define EP_RE_NODE 1024
#define LIS_MAX 1025
#define BUF_SIZE 4096

using namespace std;
//对于read函数进行封装,读取指定的字节
size_t Read(int fd, char *buf, size_t size){
    int nread ;
    int nleft = size;
    char *nbuf = buf;

    while(nleft){
        nread = read(fd, nbuf, nleft);
        if(nread == -1){
            if(errno == EAGAIN){
                break;
            }else if(errno == EINTR){
                nread = 0;
            }
            else{
                perror("read error");
                exit(1); 
            }
        }
        else if(nread == 0){
            break;
        }
        nleft -= nread;
        nbuf += nread;  
    }
    return(size - nleft);

}


size_t Write(int fd, const char *buf, size_t size){
    int nwrite;
    const char *nbuf = buf;
    int nleft = size;

    while(nleft){
        nwrite = write(fd, nbuf, nleft);
        if(nwrite == 0){
            break;
        }else if(nwrite == -1){
            if(errno == EINTR){
                nwrite = 0;
            }else if(errno == EAGAIN){
                nwrite == 0;
                usleep(100);
            }else{
                perror("write error");
                exit(1);
            }
        }
        nleft -= nwrite;
        nbuf += nwrite;
    }

    return(size - nleft);
}



class reactor;
class My_events;

typedef void (*CALLBACK_PTR)(reactor *temp_react, My_events *event);

class My_events{
public:
    My_events(){          //初始化成员
        fd = 0;
        events = 0;
        ptr = NULL;
        funtion_ptr = NULL;
        status = 0;
        bzero(buf, BUF_SIZE);
        len = 0;
        rec_time = 0;
        
    }

    int fd;                         //socket对应的文件描述符
    long events;                     //监听事件
    void * ptr;                     //指向自己的指针
    CALLBACK_PTR funtion_ptr;       //回调函数
    int status;                     //当前socket所处的状态位 0 -> 不在树上, 1 -> 在树上
    char buf[BUF_SIZE];             //局部缓冲区
    int len;                        //缓冲区大小
    long rec_time;                  //记录上树的时间
};

class reactor{
public:
    reactor(){
        max_pst = 0;
        main_structure();
    }
    
private:
//定义的函数
    //epoll反应堆主体框架
    void main_structure();

    //创建监听socket,lfd
    void lfd_create();

    //添加fd节点到红黑树
    void nodeadd(const int event, My_events *my_event);

    //赋予节点最初基本属性
    void nodeattr(int fd, My_events * My_event, CALLBACK_PTR funtion_ptr);

    //对于监听lfd对应读的回调函数
    static void lfd_read_callback(reactor *temp_react, My_events *event);

    //对于节点cfd对应读的回调函数
    static void cfd_read_callback(reactor *temp_react, My_events *event);

    //对于节点cfd对应写的回调函数
    static void cfd_write_callback(reactor *temp_react, My_events *event);

    //read事件超时检测
    void timeout_detection();

    //判断my_events数组内空余位置
    int freespace();

    //把节点从红黑树上摘除
    void nodedel(My_events *event);

    //改变文件属性为非阻塞
    void fd_nonblocking(int fd);

    //关闭文件描述符
    void Close(My_events *event);

//定义的变量
    //红黑树首节点
    int epfd;

    //储存节点的具体数据
    My_events my_events[TREE_NODE + 1]; //定义确定第1025个元素保存lfd的数据

    //epoll_wait函数返回的数组
    struct epoll_event ret_events[EP_RE_NODE + 1];

    //定义已有fd的my_events的最大下标位置
    int max_pst;
};

void reactor :: main_structure(){
    epfd = epoll_create(TREE_NODE + 1);  //创建红黑树节点

    lfd_create();   //创建监听节点

    while(1){

        timeout_detection();        //检测超时

        int nfd = epoll_wait(epfd, ret_events, LIS_MAX, -1);
        
        for(int i = 0; i < nfd; i++){
            My_events *ptr = (My_events *)ret_events[i].data.ptr;
            if(ret_events[i].events == EPOLLIN && ptr->events == (EPOLLIN | EPOLLET)){
                ptr->funtion_ptr(this, ptr);
                continue;
            }
            if(ret_events[i].events == EPOLLOUT && ptr->events == (EPOLLOUT | EPOLLET)){
                ptr->funtion_ptr(this, ptr);
            }
        }

    }
}

void reactor :: timeout_detection(){
    int i;
    for(i = 0; i <= max_pst; i++){
        if(my_events[i].status == 0 || my_events->events == EPOLLOUT){
            continue;
        }

        long det_time = time(NULL);

        if(det_time - my_events[i].rec_time > 60){
            cout << "one node time out " << endl;
            Close(&my_events[i]);
        }

    }

}

void reactor :: lfd_create(){

    struct sockaddr_in ser_lfd_addr;

    int lfd  = socket(AF_INET, SOCK_STREAM, 0);

    fd_nonblocking(lfd);

    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEPORT, (void *)&opt, sizeof(opt));  //设置端口复用

    ser_lfd_addr.sin_port = htons(9999);                                   //设置默认端口9999
    ser_lfd_addr.sin_family = AF_INET;
    ser_lfd_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(lfd, (struct sockaddr *)&ser_lfd_addr, sizeof(ser_lfd_addr));     //绑定地址结构

    listen(lfd, 128);  //设定监听上限

    nodeattr(lfd, &my_events[TREE_NODE], &lfd_read_callback);

    nodeadd(EPOLLIN, &my_events[TREE_NODE]);

}

void reactor :: lfd_read_callback(reactor *temp_react, My_events *event){
    sockaddr_in cli_addr;
    socklen_t cli_len;

    bzero(&cli_addr, sizeof(cli_addr));
    cli_len = sizeof(cli_addr);
    int cfd = accept(event->fd, (struct sockaddr *)&cli_addr, &cli_len);  //创建cfd
    if(cfd == -1){
        perror("accept error");
        exit(1);
    }

    temp_react->fd_nonblocking(cfd);

    int fr_psit = temp_react->freespace();

    temp_react->nodeattr(cfd, &temp_react->my_events[fr_psit], &cfd_read_callback);

    temp_react->nodeadd(EPOLLIN, &temp_react->my_events[fr_psit]);
}

void reactor :: cfd_read_callback(reactor *temp_react, My_events *event){

    int len = Read(event->fd, event->buf, sizeof(event->buf));
    if(len == 0){
       temp_react->Close(event);
       return ;
    }
    
    
    event->len = len;

    temp_react->nodedel(event);

    temp_react->nodeattr(event->fd, event, &cfd_write_callback);

    temp_react->nodeadd(EPOLLOUT, event);

}

void reactor :: Close(My_events *event){

    nodedel(event);
    bzero(event->buf, sizeof(event->buf));
    event->len = 0;
    event->ptr = NULL;
    close(event->fd);
    event->fd = 0;

}


void reactor :: cfd_write_callback(reactor *temp_react, My_events *event){
    
    Write(event->fd, event->buf, event->len);
    temp_react->nodedel(event);
    temp_react->nodeattr(event->fd, event, &cfd_read_callback);
    
    temp_react->nodeadd(EPOLLIN, event);
}


void reactor :: nodedel(My_events *event){

    int op;
    if(event->status == 1){
        op = EPOLL_CTL_DEL;
    }else{
        return;
    }

    epoll_ctl(epfd, op, event->fd, NULL);
    
    event->funtion_ptr = NULL;
    event->status = 0;
    event->events = 0;
    event->rec_time = 0;

}

void reactor :: nodeadd(const int event, My_events *my_event){

    struct epoll_event par_event;
    
    par_event.events = event | EPOLLET;         //设定节点为ET模式
    par_event.data.ptr = my_event->ptr;         //epoll_ctl函数的参数二初赋值

    int op = 0;                         //判断该节点是否在树上
    if(my_event->status == 0){
        op = EPOLL_CTL_ADD;
    }else{
        return;
    }
    
    int ret = epoll_ctl(epfd, op, my_event->fd, &par_event);
    if(ret == -1){
        perror("epoll_ctl error");
        exit(1);
    }else{
        my_event->status = 1;               //确定上树
        my_event->events = par_event.events;
        my_event->rec_time = time(NULL);    //设置上树时间
    }
}


void reactor :: nodeattr(int fd, My_events * My_event, CALLBACK_PTR funtion_ptr){

    My_event->fd = fd;             
    My_event->ptr = (void *)My_event;
    My_event->funtion_ptr = funtion_ptr;

}


void reactor :: fd_nonblocking(int fd){

    int flags = fcntl(fd, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flags);

}

int reactor :: freespace(){ 
    int i;
    for(i = 0; i < TREE_NODE; i++){
        if(my_events[i].status == 0){
            if(max_pst < i){
                max_pst = i;
                cout << "max_pst is " << max_pst << endl;
            }
            break;
        }   

    }
    return i;
}

int main(){
    reactor p;

    return 0;
}

