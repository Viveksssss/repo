
#include"./wrapf.c"
#include <sys/socket.h>
#include <unistd.h>

int main(int argc,char*argv[]){
    int fd = Socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in *adr = Init();
    Bind(fd,adr,sizeof(*adr));
    Listen(fd,128);

    sigset_t sig;
    sigemptyset(&sig);
    sigaddset(&sig,SIGCHLD);
    sigprocmask(SIG_BLOCK,&sig,NULL);


    Accept(fd,NULL,NULL);




    return 0;
}
