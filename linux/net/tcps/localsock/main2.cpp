//c lib
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<memory.h>
#include<bits/stdc++.h>
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
#include<sys/un.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<netdb.h>
using namespace std;


int main(int argc,char*argv[]){
    int cfd = socket(AF_UNIX,SOCK_STREAM,0);
    struct sockaddr_un serv;
    bzero(&serv,sizeof(serv));
    

    serv.sun_family = AF_UNIX;
    strcpy(serv.sun_path,"./client.sock");

    socklen_t len = sizeof(serv);
    int ret = connect(cfd,(struct sockaddr*)&serv,len);
    char buf[64];
    while(1){
        memset(buf,0x00,sizeof(buf));
        int n = read(STDIN_FILENO,buf,sizeof(buf));
        write(cfd,buf,sizeof(buf));
        n = read(cfd,buf,sizeof(buf));
        cout << buf << "\n";
    }
    close(cfd);

    return 0;
}
