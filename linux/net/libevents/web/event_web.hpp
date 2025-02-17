#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <fcntl.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <event.h>
#include <event2/listener.h>
#include <dirent.h>
#include <event2/event.h>
#include <vector>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/event.h>
#include <string>





#define _DIR_PREFIX_FILE_ "./html/dir_header.html"
#define _DIR_TAIL_FILE_ "./html/dir_tail.html"



int copy_header(struct bufferevent *bev,int op,std::string msg,std::string filetype,long filesize);
void listener_cb(struct evconnlistener *listener, int fd, struct sockaddr *addr, int socklen, void *arg);
int copy_file(struct bufferevent *bev, const std::string strFile);
int send_dir(struct bufferevent *bev, const std::string strPath);
void read_cb(struct bufferevent*, void*ctx);
void bevent_cb(struct bufferevent *bev, short what,void*tmp);
int http_request(struct bufferevent *bev, std::string path);
