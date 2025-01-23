#ifndef __THREADPOOL_H_
#define __THREADPOOL_H_

#include<cstdlib>
#include<pthread.h>
#include<unistd.h>
#include<assert.h>
#include<cstring>
#include<cerrno>
#include<functional>
#include<queue>
#include<vector>



#define DEFAULT_TIME 10  // detect once every 10 seconds
#define MIN_WAIT_TASK_NUM 10  // if queue_size > this,add thread to pool
#define DEFAULT_THREAD_VARY 10 // quantity created each time


namespace thread{
using function =  std::function<void*(void*)> ;

class threadpool_tast_t;
class threadpool_t;

threadpool_t*threadpool_create(int,int,int); // create a single pointer to pool
void threadpool_free(threadpool_t*ptr); // clear resource

class threadpool_t{
public:
    
    friend threadpool_t*threadpool_create(int,int,int); // friend func
    friend void threadpool_free(threadpool_t*ptr);  // friend func
    ~threadpool_t(); // desconstruction
    int threadpool_add(threadpool_t *pool, function func, void *arg); // add task to pool
    int threadpool_destroy(threadpool_t *pool); // destroy the pool
    int threadpool_all_threadnum(threadpool_t *pool); // get the num of all threads
    int threadpool_busy_num(threadpool_t *pool); // get the num of busy threads
    bool is_thread_live(pthread_t tid);
    bool shutdown; // the flag of status for pool
    pthread_mutex_t lock; // to lock this
    pthread_mutex_t busy_thread_counter;// to lock busy thread num
    pthread_cond_t queue_not_full; // the task thread wait for this para arguement
    pthread_cond_t queue_not_empty; // if the task queue not empty,notice the thread which wait for task
private:
    pthread_t adjust_tid;          // manager thread
    std::vector<pthread_t>threads; // store threads
    std::queue<threadpool_tast_t>task_queue;
    int min_thr_mun; // minimum quantity of task threads in pool
    int max_thr_num; // maximun quantity of task threads in pool
    int live_thr_num; // num of surviving threads
    int wait_exit_thr_num; // num of threads waiting for destroying
    int busy_thr_num; // num of busy threads 
    int queue_size; // size of queue
    int queue_max_size; // the max size of queue
    threadpool_t(int _min_thr_num = 1,int _max_thr_num = 20,int _queue_max_size = 50);

    static void*threadpool_thread(void*);
    static void*adjust_thread(void*);
};

class threadpool_tast_t{
public:
    function func;
    void *arg;
};

}


#endif
