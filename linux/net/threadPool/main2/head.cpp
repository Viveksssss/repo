#include  "head.hpp"
#include <iostream>
#include <new>
#include <pthread.h>
#include <signal.h>
// the default construction of pool
thread::threadpool_t::threadpool_t(int _min_thr_num ,int _max_thr_num,int _queue_max_size ){
    int i ;
    do{
        
        this->min_thr_mun = _min_thr_num;
        this->max_thr_num = _max_thr_num;

        this->busy_thr_num = 0;
        this->live_thr_num = _min_thr_num;
        this->queue_size = 0;
        this->wait_exit_thr_num = 0;
        this->queue_max_size = _queue_max_size;  
        this->shutdown = false;
        
        this->threads.resize(_max_thr_num);
        // this->task_queue.resize,don't need init

        if(pthread_cond_init(&this->queue_not_empty,nullptr)||\
        pthread_cond_init(&this->queue_not_full,nullptr)||\
        pthread_mutex_init(&this->lock,nullptr)||\
        pthread_mutex_init(&this->busy_thread_counter,nullptr)){
            std::cerr<<"init error...\n";
            break;
        } 
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

        for(int i = 0;i<min_thr_mun;i++){
            pthread_create(&this->threads[i],&attr,this->threadpool_thread,(void*)this);
        }

        pthread_create(&this->adjust_tid,&attr,adjust_thread,(void*)this);
    }while(0);
}

thread::threadpool_t*thread::threadpool_create(int _min_thr_num,int _max_thr_num,int _queue_max_size){
    try{
        threadpool_t*ptr = new threadpool_t(_min_thr_num,_max_thr_num,_queue_max_size);
        return ptr;
    }
    catch(const std::bad_alloc&e){
        std::cout << e.what() << "\n";
    }

    return nullptr;

}


void thread::threadpool_free(threadpool_t*ptr){
    pthread_mutex_lock(&ptr->lock);
    pthread_mutex_destroy(&ptr->lock);
    pthread_mutex_lock(&ptr->busy_thread_counter);
    pthread_mutex_destroy(&ptr->busy_thread_counter);
    pthread_cond_destroy(&ptr->queue_not_empty);
    pthread_cond_destroy(&ptr->queue_not_full);
    free(ptr);
}

thread::threadpool_t::~threadpool_t(){
    threadpool_free(this);
}

int thread::threadpool_t::threadpool_add(threadpool_t*pool,thread::function func,void*arg){
    pthread_mutex_lock(&pool->lock);

    while((pool->queue_size == queue_max_size)&&(!pool->shutdown)){
        pthread_cond_wait(&(pool->queue_not_full),&(pool->lock));
    }
    if(pool->shutdown){
        pthread_cond_broadcast(&pool->queue_not_empty);
        pthread_mutex_unlock(&pool->lock);
        return 0;
    }
    thread::threadpool_tast_t task;
    task.func = func;
    task.arg = arg;
    pool->task_queue.push(task);
    pool->queue_size++;
    pthread_cond_signal(&pool->queue_not_empty);

    pthread_mutex_unlock(&pool->lock);
    return 0;
}

void*thread::threadpool_t::threadpool_thread(void*threadpool){
    threadpool_t *pool = (threadpool_t*)threadpool;
    threadpool_tast_t task;

    while(1){
        pthread_mutex_lock(&pool->lock);
        //if queue.size == 0(no task),it means the thread is wating
        while((pool->queue_size==0)&&!(pool->shutdown)){
            std::cout << "thread 0x" ;
            printf("%x\n",(unsigned int)pthread_self());
            pthread_cond_wait(&pool->queue_not_empty,&pool->lock); // wait in here
            if(pool->wait_exit_thr_num>0){
                pool->wait_exit_thr_num--;
                
                if(pool->live_thr_num>pool->min_thr_mun){
                    std::cout << pthread_self() <<" is exiting\n";
                    pool->live_thr_num--;
                    pthread_mutex_unlock(&pool->lock);             
                    pthread_exit(nullptr);
                }
            }
        }
        if(pool->shutdown){
            pthread_mutex_unlock(&pool->lock);
            std::cout << pthread_self() <<"is exiting\n";
            pthread_exit(nullptr);
        }
        task.func = pool->task_queue.front().func;
        task.arg = pool->task_queue.front().arg;
        pool->task_queue.pop();
        pool->queue_size--;

        pthread_cond_broadcast(&pool->queue_not_full);
        pthread_mutex_unlock(&pool->lock);
        std::cout << pthread_self()<<"is working\n";
        pthread_mutex_lock(&pool->busy_thread_counter);
        pool->busy_thr_num++;
        pthread_mutex_unlock(&pool->busy_thread_counter);

        task.func(task.arg); // ==(*(task.func))(task.arg);
        std::cout <<pthread_self()<<"end working\n";
        pthread_mutex_lock(&pool->busy_thread_counter);
        pool->busy_thr_num--;
        pthread_mutex_unlock(&pool->busy_thread_counter);


    }
    pthread_exit(nullptr);
}

void*thread::threadpool_t::adjust_thread(void*threadpool){
    int i;
    threadpool_t *pool = (threadpool_t*)threadpool;
    while(!pool->shutdown){
        sleep(DEFAULT_TIME); // wait for thread to work
        pthread_mutex_lock(&pool->lock);
        int queue_size = pool->queue_size;
        int live_thr_num = pool->live_thr_num;
        pthread_mutex_unlock(&pool->lock);
        pthread_mutex_lock(&pool->busy_thread_counter);
        int busy_thr_num = pool->busy_thr_num;
        pthread_mutex_unlock(&pool->busy_thread_counter);
        
        if(queue_size>=MIN_WAIT_TASK_NUM&&live_thr_num<pool->max_thr_num){
            pthread_mutex_lock(&pool->lock);
            int add = 0;
            // add up to MIN_WAIT_TASK_NUM more
            for(i = 0;i<pool->max_thr_num&&\
            add<MIN_WAIT_TASK_NUM&&\  
            pool->live_thr_num<pool->max_thr_num;i++){
                if(pool->threads[i] == 0||!pool->is_thread_live(pool->threads[i])){
                    pthread_create(&pool->threads[i],nullptr,pool->threadpool_thread,(void*)pool);
                    add++;
                    std::cout << "adjust_thread do work...\n";
                    pool->live_thr_num++;
                } 
            }
            pthread_mutex_unlock(&pool->lock);
        }

        if((busy_thr_num*2)<live_thr_num && live_thr_num>pool->live_thr_num){
            pthread_mutex_lock(&pool->lock);
            pool->wait_exit_thr_num = DEFAULT_THREAD_VARY;
            pthread_mutex_unlock(&pool->lock);

            for(i = 0;i<DEFAULT_THREAD_VARY;i++){
                pthread_cond_signal(&pool->queue_not_empty);
            }
        }

    }
    return nullptr;
}

int thread::threadpool_t::threadpool_busy_num(thread::threadpool_t*pool){
    int busy_thr_num = -1;
    pthread_mutex_lock(&pool->lock);
    busy_thr_num = pool->busy_thr_num;
    pthread_mutex_unlock(&pool->lock);
    return busy_thr_num;
}

int thread::threadpool_t::threadpool_destroy(thread::threadpool_t*pool){
    int i;
    if(pool == nullptr){
        return -1;
    }
    pool->shutdown = true;
    pthread_join(pool->adjust_tid,nullptr);
    pthread_cond_broadcast(&pool->queue_not_empty);
    thread::threadpool_free(pool);
    pool = nullptr;
    return 0;
     
}

int thread::threadpool_t::threadpool_all_threadnum(thread::threadpool_t*pool){
    int all_threadnum = -1;
    pthread_mutex_lock(&pool->lock);
    all_threadnum = pool->live_thr_num;
    pthread_mutex_unlock(&pool->lock);
    return all_threadnum;
}


bool thread::threadpool_t::is_thread_live(pthread_t tid){
    int iskill = pthread_kill(tid,0);
    if(iskill == ESRCH){
        return false;
    }
    return true;
}

