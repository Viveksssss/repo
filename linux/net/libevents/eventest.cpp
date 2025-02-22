#include<iostream>
#include<cstdlib>
#include<cstring>
#include<event2/event.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>


using namespace std;

/*
    1.socket
    2.setsockopt
    3.bind
    4.listen
    5.event_base_new
        struct event_base*base = event_base_new();
    6.event_new
        struct event*ev = event_new(base, sockfd, EV_READ|EV_PERSIST, read_cb, arg);
    7.event_add
        event_add(ev, NULL);
    8.event_base_dispatch
        event_base_dispatch(base);
    9.event_free
        event_free(ev);
    10.event_base_free
        event_base_free(base);


    typedef void(*event_callback_fn)(evutil_socket_t, short, void*)

        void connection_cb(evutil_socket_t sockfd, short events, void*arg){
            int cfd = accept(sockfd, NULL, NULL);
            if(cfd>0){
                struct event*ev = event_new( base, cfd, EV_READ|EV_PERSIST, read_cb, arg);
                event_add(ev,nullptr);
            }
        }

        void read_cb(evutil_socket_t sockfd, short events, void*arg){
            char buf[1024];
            memset(buf,0,sizeof(buf));
            int n = recv(sockfd,buf,sizeof(buf),0);
            if(n<=0){
                close(sockfd);
                event_del(ev);
                event_free(ev);
            }
            write(sockfd,buf,n);
        }
*/


struct MyData{
    int sockfd;
    struct event *ev;
};

void read_cb(evutil_socket_t sockfd, short events, void*arg){
    struct MyData *data = (struct MyData *)arg;
    struct event *ev = data->ev;
    char buf[1024];
    memset(buf,0,sizeof(buf));
    int n = read(sockfd,buf,sizeof(buf));
    cout << "size:" << n << "\n";
    if (n <= 0)
    {
        cerr << "client disconnected\n";
        close(sockfd);
        event_del(ev);
        event_free(ev);
        delete data;
        return;
    }
    for (int i = 0; i < n;i++){
        buf[i] = toupper(buf[i]);
    }
    write(sockfd,buf,n);
}

void connection_cb(evutil_socket_t sockfd, short events, void*arg){
        int cfd = accept(sockfd, nullptr, nullptr);
        struct event_base *base = (struct event_base *)arg;
        auto data = new MyData{cfd, nullptr};
        if (cfd > 0){
            data->ev = event_new(base, cfd, EV_READ | EV_PERSIST, read_cb, data);
            if(data->ev == nullptr){
                cerr << "fail to create event\n";
                close(cfd);
                delete data;
                event_base_loopexit(base, nullptr);
                return;
            }
            event_add(data->ev, nullptr);
        }
}



int main(){
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));

    listen(sockfd, 128);

    struct event_base *base = event_base_new();
    if(base == nullptr){
        cerr << "fail to create event_base\n";
        return -1;
    }

    struct event *ev = event_new(base, sockfd, EV_READ | EV_PERSIST, connection_cb, base);
    if(ev == nullptr){
        cerr << "fail to create event\n";
        return -1;
    }

    event_add(ev, nullptr);

    event_base_dispatch(base);

    event_free(ev);

    event_base_free(base);

    close(sockfd);

    return 0;
    
}