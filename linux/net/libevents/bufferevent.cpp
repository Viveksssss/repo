// c lib
#include<cstdio>
#include<cstring>
#include<cstdlib>
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

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <ctype.h>

using namespace std;

/*                                                   bufferevent
*                      * ------------------------------------------------------------------
*                      * |                                                                |
*                      * |                                                                |
*                      * |        read buffer                          write buffer       |
*                      * |                                                                |
*                      * |                                                                |
*                      * ------------------------------------------------------------------
*                      *                                kernel
*                      *                        ---------------------
*                      *                        |                   |
*                      *                        |                   |
*                      *                        | read        write |
*                      *                        |                   |
*                      *                        |                   |
*                      *                        ---------------------

    We need only to remember that what we do is to operator the bufferevent,then the underlying technology will be \
    implemented by the bufferevent.

    Therefore,when we read,we received data read from kernel        kernel read  -> read buffer
    when we write,we send data from bufferevent to kernel write     write buffer -> kernel buffer

*/

static const char MESSAGE[] = "hello world!\n"; // what we need to send
static const int PORT = 9999;   // port number
static void listener_cb(struct evconnlistener *, evutil_socket_t,
                        struct sockaddr *, int socklen, void *arg); //listen event
static void conn_writecb(struct bufferevent *, void *); //write event
static void conn_readcb(struct bufferevent *, void *); // read event
static void conn_eventcb(struct bufferevent *, short, void *); // error event
static void signal_cb(evutil_socket_t, short, void *); // to handle signal soch as ctrl+c
struct client_info
{
    char ip[64];
    int port;
};
int main(int argc,char*argv[]){
    struct evconnlistener *listener; // listener
    struct sockaddr_in6 sin; // socket address 
    struct event *signal_event; // signal event 
    struct event_base *base; // the event base

    base = event_base_new();
    if(!base){
        cerr << " create event base failed ! \n";
        return -1;
    }
    
    memset(&sin, 0x00, sizeof(sin));
    sin.sin6_family =  AF_INET6;
    sin.sin6_port = htons(PORT);
    sin.sin6_addr = in6addr_any; // listen on all interfaces

    listener = evconnlistener_new_bind(
        base, listener_cb /*here is the key point ,let's code to structure*/,
         (void *)base,
        LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,
        -1, (struct sockaddr *)&sin, sizeof(sin)); // backlog is -1,means default

    if(!listener){
        cerr << "couldn't not create a listener !\n";
        return -1;
    }

    signal_event = evsignal_new(base,SIGINT,signal_cb,(void*)base);
    if(!signal_event || event_add(signal_event,nullptr)<0){
        cerr << "couldn't not create a signal event !\n";
        return -1;
    }
    // loop to dispatch events
    event_base_dispatch(base);
    
    // free resources
    evconnlistener_free(listener);
    event_free(signal_event);
    event_base_free(base);

    return  0;
}

static void listener_cb(struct evconnlistener *listener, evutil_socket_t fd,
                        struct sockaddr *addr, int socklen, void *arg)         
{
    struct event_base *base = (struct event_base *)arg;
    struct bufferevent *bev;
    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    if(!bev){
        cerr << "couldn't not create a bufferevent !\n";
        event_base_loopbreak(base);
        return;
    }
   
    struct client_info *info = (struct client_info *)malloc(sizeof(struct client_info));
    memset(info, 0x00, sizeof(struct client_info));
    info->port = ntohs(((struct sockaddr_in *)addr)->sin_port);
    inet_ntop(AF_INET6, &(((struct sockaddr_in *)addr)->sin_addr), info->ip, sizeof(info->ip));
    bufferevent_setcb(bev, conn_readcb, conn_writecb, conn_eventcb, info);
    bufferevent_enable(bev, EV_WRITE|EV_READ);

}
static void conn_writecb(struct bufferevent *bev, void *arg){
    struct evbuffer *output = bufferevent_get_output(bev);
    if(evbuffer_get_length(output)==0){
        cout << "flushefd answer \n";
    }
}
static void conn_readcb(struct bufferevent *bev, void *arg){
    struct client_info *info = (struct client_info *)arg;
    cout << "received connection from client " << (info->ip) << ":" << (info->port) << endl;
    char buf[1024];
    memset(buf, 0x00, sizeof(buf));
    int n = bufferevent_read(bev, buf, sizeof(buf));
    cout << "received data from client : " << buf << endl;
    for (int i = 0; i < n; i++)
    {
        buf[i] = toupper(buf[i]);
    }
    bufferevent_write(bev, buf, n);
}
static void conn_eventcb(struct bufferevent *bev, short events, void *arg){
    if(events & BEV_EVENT_EOF){
        cout << "client disconnected \n";
    } else if(events & BEV_EVENT_ERROR){
        cout << "some error occurred \n";
    }
    bufferevent_free(bev);
}
static void signal_cb(evutil_socket_t fd, short events , void *arg){
    struct event_base*base = (struct event_base *)arg;
    struct timeval delay = {2, 0};

    cout << "caught an interrupt signal\n";
    event_base_loopexit(base,&delay);
}