#include "head.hpp"
#include <iostream>
#include <pthread.h>
using namespace std;
int main(){
    thread::threadpool_t*pool = thread::threadpool_create(3,100,100);
    cout << "pool inited... \n";
    int num[20],i;
    for(i = 0;i<1000;i++){
        num[i] = i;
        cout << "addtask->" <<i <<"\n";
        pool->threadpool_add(\
            pool,(thread::function)[](void*arg)->void*{\
            cout << "thread "<<pthread_self()<<" is working task:" << *(int*)(arg)<<"\n";
            sleep(1);
            cout << "good" << endl;
            cout << "task:" <<*(int*)arg<<"is end\n";
            return nullptr;
        },\
        &num[i]\
        );
    }

    sleep(200);
    pool->threadpool_destroy(pool);
    return 0;
}
