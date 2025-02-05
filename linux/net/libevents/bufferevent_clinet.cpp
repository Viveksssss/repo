#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <iostream>
using namespace std;


void cmd_msg_cb(int fd,short event,void*arg); // for senting message
void server_msg_cb(struct bufferevent *bev, void *arg); // for listening server message
void event_cb(struct bufferevent *bev, short event, void *arg); // for abnormal event

int main(int argc,char**argv){
    if(argc < 3){
        cerr << "please input 2 parameter\n";
        return -1;
    }

    struct event_base *base = event_base_new();

    struct bufferevent *bev = bufferevent_socket_new(
        base,
        -1,/* if sockfd is -1, it means we will set it ltter*/
        BEV_OPT_CLOSE_ON_FREE
    );

    struct event *ev_cmd = event_new(
        base,
        STDIN_FILENO,
        EV_PERSIST | EV_READ,
        cmd_msg_cb,
        (void *)bev /* normally we sent the bufferevent to cb 'cmd_msg_cb',so we can use it to write */
    );

    event_add(ev_cmd, nullptr);

    struct sockaddr_in6 addr;
    memset(&addr, 0x00, sizeof(addr));
    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(atoi(argv[2]));
    inet_pton(AF_INET6, argv[1], &addr.sin6_addr);

    bufferevent_socket_connect(
        bev,
        (struct sockaddr*)&addr,
        sizeof(addr)
    ); // to connect to server

    bufferevent_setcb(
        bev,
        server_msg_cb,
        nullptr,
        event_cb,
        (void*)ev_cmd  /* normally we sent the event for free it */
    );

    bufferevent_enable(bev, EV_READ | EV_PERSIST);

    event_base_dispatch(base);

    event_free(ev_cmd);
    bufferevent_free(bev);
    event_base_free(base);

    cout << " finished \n ";

    return 0;
}


void cmd_msg_cb(int fd,short event,void*arg){
    char msg[1024];
    int len = read(fd, msg, sizeof(msg));
    if(len < 0){
        perror("read fail\n");
        exit(1);
    }

    struct bufferevent *bev = (struct bufferevent *)arg;
    bufferevent_write(bev, msg, len);
} 
void server_msg_cb(struct bufferevent *bev, void *arg){
    char msg[1024];
    size_t len = bufferevent_read(bev, msg, sizeof(msg));
    msg[len] = '\0';
    cout << "recv " << msg << "from server\n";

} 
void event_cb(struct bufferevent *bev, short event, void *arg){
    if(event&BEV_EVENT_EOF){
        cout << "connection closed\n";
    }else if(event&BEV_EVENT_ERROR){
        cout << "some error\n";
    }else if(event&BEV_EVENT_CONNECTED){
        cout << "connected to server\n";
        return;
    }

    bufferevent_free(bev);
    struct event *ev = (struct event *)arg;
    event_free(ev);
} 
