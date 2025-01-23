#include <cerrno>
#include <cstddef>
#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <strings.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024 // the buf size
#define TIMEOUT 60  // the limit of overtime
#define MYEVENTS_SIZE 1024
#define EPOEVENTS_SIZE 1024
#define EPOLLWAIT_SIZE 1025
#define LISTEN_SIZE 128

using namespace std;

//encapsulation of read
size_t Read(int fd,char*buf,size_t size){
    int len;
    char* nbuf = buf;
    int nlen = size;
    while(nlen){
        len = read(fd,nbuf,nlen);
        if(len == -1){
            if(errno == EINTR){
                len = 0;
            }
            else if(errno == EAGAIN){
                break;
            }
            else{
                cerr << "read error...\n";
            }
            break;
        }
        else if(len == 0){
            cout << "connection break...\n";
            break;
        }

        nlen -= len;
        nbuf += len;
    }
    for(int i = 0;i<(size-nlen);i++){
        buf[i] = static_cast<char>(toupper(static_cast<unsigned char>(buf[i])));
    }
   
    return size - nlen;
}
// encapsulation of write
size_t Write(int fd,char*buf,size_t size){
    int len;
    const char*nbuf = buf;
    int nlen = size;
    while(nlen){
        len = write(fd,nbuf,nlen);
        if(len == 0){
            break;
        }
        else if(len == -1){
            if(errno == EINTR){
                continue;
            }
            cout << "write error...\n";
            break;
        }
        nbuf += len;
        nlen -= len;
    }
    return size-nlen;
}

// pre declaration
class reactor;
class Events;

// the call_back function
typedef void (*call_back)(reactor*react,Events*event);

// core information we received,manage the information related to the event
class Events{
public:
    Events(){
        events = 0;
        ptr = nullptr;
        status = 0;
        bzero(buf,BUF_SIZE);
        len = 0;
        function_ptr = nullptr;
        begtime = 0;
    }
    int fd;
    long int events;
    void *ptr;
    call_back function_ptr;
    int status;
    char buf[BUF_SIZE];
    int len;
    int begtime;
};

//the core class/structure,which implements the Reactor Pattern and responsible for the logic
class reactor{
public:
    reactor():max_pst(0){
        main_structure();
    }
private:
    //main loop
    void main_structure();

    //init fd
    void init(reactor*react){
        for(int i = 0;i <=MYEVENTS_SIZE;i++){
            react->my_events[i].fd = -1;
        }
    }
    
    //over time detection
    void timeout_detection();

    //Determine if there is free space available
    int freespace();

    //Remove the event from the tree
    void delnode(Events*event);

    //add event to the tree
    void addnode(const int,Events*);

    //init node
    void initnode(int fd,Events*event,call_back ptr);

    //create socket and lfd
    void lfd_create();

    //set the file attr to non block
    void set_nonblock(int fd);

    //close the fd
    void Close(Events*event);

    //for lfd
    static void lfd_read_callback(reactor*react,Events*event); // for listen file

    //for cfd read
    static void cfd_read_callback(reactor*react,Events*event); // for read file

    //for cfd write
    static void cfd_write_callback(reactor*react,Events*event);// for write file


    //the root of epoll core
    int epfd;

    Events my_events[MYEVENTS_SIZE+1];

    struct epoll_event epo_events[EPOEVENTS_SIZE+1];

    int max_pst;
};


void reactor::main_structure(){
    init(this);
    epfd = epoll_create1(0);
    lfd_create();
    
    int n;
    while(1){
        timeout_detection();


        n = epoll_wait(epfd,epo_events,EPOLLWAIT_SIZE,-1);


        for(int i = 0;i < n; i++){
            Events*ptr = (Events*)epo_events[i].data.ptr;
            if((epo_events[i].events & (EPOLLIN)) && ptr->events==(EPOLLIN)){
                ptr->function_ptr(this,ptr);
            }
            else if((epo_events[i].events & (EPOLLOUT))&&ptr->events==(EPOLLOUT)){
                ptr->function_ptr(this,ptr);
            }

        }
    }
}

void reactor::timeout_detection(){
    int i;
    for(i = 0;i<=max_pst;i++){
        if(my_events[i].status == 0 || my_events[i].events == EPOLLOUT || my_events[i].fd == -1){
            continue;
        }

        long timenow = time(NULL);
        if(timenow - my_events[i].begtime>60){
            cout << "one node time out ...\n";
            Close(&my_events[i]);
        }
    }
}

void reactor::lfd_create(){
    struct sockaddr_in addr;
    int lfd = socket(AF_INET,SOCK_STREAM,0);
    set_nonblock(lfd);
    int opt = 1;
    setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,(void*)&opt,sizeof(opt));
    
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_family = AF_INET;

    int tmp;
    if((tmp = bind(lfd,(struct sockaddr*)&addr,sizeof(addr)))==-1){
        cerr << "bind error...\n";
        exit(-1);
    }
    if((tmp = listen(lfd,LISTEN_SIZE)) == -1){
        cerr << "listen error...\n";
        exit(-1);
    };
    initnode(lfd,&my_events[MYEVENTS_SIZE],&lfd_read_callback);
    addnode(EPOLLIN,&my_events[MYEVENTS_SIZE]);
}

int reactor::freespace(){
    int i ;
    for(i = 0;i<EPOEVENTS_SIZE;i++){
        if(my_events[i].status == 0){
            if(i>max_pst){
                max_pst = i;
            }
            break;
        }
    }
    return i;
}

void reactor::delnode(Events*event){
    int op;
    if(event->status == 1){
        op = EPOLL_CTL_DEL;
    }
    else{
        return;
    }
    epoll_ctl(epfd,op,event->fd,NULL);

    event->function_ptr = nullptr;
    event->status = 0;
    event->events = 0;
    event->begtime = 0;
}

void reactor::addnode(const int event,Events*my_event){
    struct epoll_event tmpevent;
    tmpevent.events = event;
    tmpevent.data.ptr = (void*)my_event;

    int op = 0;
    if(my_event->status == 0){
        op = EPOLL_CTL_ADD;
    }
    else{
        return;
    }

    int ret = epoll_ctl(epfd,op,my_event->fd,&tmpevent);
    if(ret == -1){
        cerr << "epoll_ctl error...\n";
        exit(-1);
    }
    else{
        my_event->status = 1;
        my_event->begtime = time(NULL);
        my_event->events = tmpevent.events;
    }
}

void reactor::initnode(int fd,Events*event,call_back ptr){
    event->fd = fd;
    event->ptr = event;
    event->function_ptr = ptr;
}

void reactor::set_nonblock(int fd){
    int flags = fcntl(fd,F_GETFL);
    flags |=O_NONBLOCK;
    fcntl(fd,F_SETFL,flags);
}

void reactor::Close(Events*event){
    delnode(event);
    bzero(event->buf,sizeof(event->buf));
    event->len = 0;
    event->ptr = nullptr;
    close(event->fd);
    event->fd = -1;
}

void reactor::lfd_read_callback(reactor*react,Events*event){
    sockaddr_in addr;
    socklen_t len;
    bzero(&addr,sizeof(addr));
    len = sizeof(addr);
    int cfd = accept(event->fd,(struct sockaddr*)&addr,&len);
    if(cfd == -1){
        cerr << "accept error...\n";
        exit(-1);
    }
    char*s;
    s = (char*)malloc(sizeof(char)*32);
    cout << "the connection from ip:"<<inet_ntop(AF_INET,&addr.sin_addr,s,INET_ADDRSTRLEN)<<",port:"<<htons(addr.sin_port) <<"\n";

    react->set_nonblock(cfd);
    int ret = react->freespace();
    react->initnode(cfd,&react->my_events[ret],&cfd_read_callback);
    react->addnode(EPOLLIN,&react->my_events[ret]);
}

void reactor::cfd_read_callback(reactor*react,Events*event){
    int len = Read(event->fd,event->buf,sizeof(event->buf));
    if(len == 0){
        react->Close(event);
        return;
    }

    event->len = len;
    react->delnode(event);
    react->initnode(event->fd,event,&cfd_write_callback);
    react->addnode(EPOLLOUT,event);
}

void reactor::cfd_write_callback(reactor*react,Events*event){
    Write(event->fd,event->buf,event->len);
    react->delnode(event);
    react->initnode(event->fd,event,&cfd_read_callback);
    react->addnode(EPOLLIN,event);
}

int main(){
    reactor p;
    return 0;
}


