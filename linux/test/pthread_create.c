#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>


void *myfunction(void *p){
    printf("YES\n");
    return NULL;
}
int main(){
    pthread_t pthread;
    pthread_attr_t attr;
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    pthread_create(&pthread,NULL,myfunction,NULL);
    printf("running ok\n");
    pthread_attr_destroy(&attr); 
    return 0;
}
