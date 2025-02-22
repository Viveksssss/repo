#include "head.hpp"
using namespace std;
int main(){
    ThreadPool*p = ThreadPool::create_threadpool(5,10);
    int i = 0;
    for(;i<50;i++){
        p->addtask(p);
    }
    
    sleep(10);
    p->destroy(p);
    return 0;
}
