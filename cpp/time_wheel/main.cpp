#include "time_wheel.hpp"
#include <unistd.h>
#include <signal.h>
using namespace std;
static tw tw;
void sig_handler(int signum){
    tw.tick();
    alarm(TIME_OUT);
}

void handler(tw_data*data){
    printf("timer %d expired\n",data->timer->rotation);
}
int main(){
    signal(SIGALRM,sig_handler);
    alarm(TIME_OUT);
    for(int i = 0;i<100;i++){
        tw.add_timer(i,handler);
    }
    while(1){
        sleep(1);
    }

    return 0;
}