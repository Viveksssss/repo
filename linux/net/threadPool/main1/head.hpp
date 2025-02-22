#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<memory.h>
#include<iostream>
#include<pthread.h>
#include<unistd.h>
class ThreadPool{
public:
    static ThreadPool* create_threadpool(int thrnum,int maxtasknum);
    void destroy(ThreadPool*pool);// destroy the pool
    void addtask(ThreadPool*pool);// add task to pool
    static void *thrRun(void *args); // the work for thread
    static void taskRun(void*arg);// the actual work for thread

private:
    struct PoolTask{
        int tasknum;// the num of task
        void*arg;// point to self
        void (*task_func)(void*args);// call_back function
    };
    
    ThreadPool(){};// private the construction

    int max_job_num;// the max job num
    int job_num;// the actual job num of pool
    int beg; //the begin flags / num of task PoolTask *tasks;
    int job_push;// the position of queue that we add task(produce)
    int job_pop;// the positon of queue where we del task(consume)
    int thr_num; // the max num of threads;
    int shutdown;// 0 for normal,1 for destroy
    PoolTask *tasks;
    pthread_t*threads;
    pthread_mutex_t pool_lock;
    pthread_cond_t empty_task;
    pthread_cond_t not_empty_task;
};




