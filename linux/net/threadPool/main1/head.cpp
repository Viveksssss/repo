#include "head.hpp"
#include <pthread.h>
#include <string.h>
using namespace std;

ThreadPool* ThreadPool::create_threadpool(int thrnum,int maxtasknum){
    cout << "call from : " << __FUNCTION__<< "\n";
    static ThreadPool*pool;
    pool = new ThreadPool;

    pool->thr_num = thrnum;
    pool->max_job_num = maxtasknum;
    pool->shutdown = 0;
    pool->job_push = 0;
    pool->job_pop = 0;
    pool->job_num = 0;
    pool->beg = 0;

    pool->tasks = (PoolTask*)malloc(sizeof(PoolTask)*maxtasknum);

    pthread_mutex_init(&pool->pool_lock,NULL);
    pthread_cond_init(&pool->empty_task,NULL);
    pthread_cond_init(&pool->not_empty_task,NULL);
    int i = 0;
    pool->threads = (pthread_t*)malloc(sizeof(pthread_t)*thrnum);
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    for(int i = 0;i<thrnum;i++){
        pthread_create(pool->threads+i,&attr,thrRun,(void*)pool);
    }
    return pool;
};
void ThreadPool::destroy(ThreadPool*pool){
    pool->shutdown=1;
    pthread_cond_broadcast(&pool->not_empty_task);
    int i = 0;
    for(i = 0;i<pool->thr_num;i++){
        pthread_exit(&pool->threads[i]);
    }
    pthread_cond_destroy(&pool->not_empty_task);
    pthread_cond_destroy(&pool->empty_task);
    pthread_mutex_destroy(&pool->pool_lock);
    free(pool->tasks);
    free(pool->threads);
    delete(pool);
}

void* ThreadPool::thrRun(void*args){
    ThreadPool*pool = (ThreadPool*)args;
    int taskpos = 0;
    PoolTask*task;
    while(1){
        pthread_mutex_lock(&pool->pool_lock);

        while(pool->job_num<=0&&!pool->shutdown){
            pthread_cond_wait(&pool->not_empty_task,&pool->pool_lock);
        }
        if(pool->job_num){
            taskpos = (pool->job_pop++)%pool->max_job_num;
            task = new PoolTask(pool->tasks[taskpos]);
            task->arg = task;
            pool->job_num --;
            pthread_cond_signal(&pool->empty_task);
        }

        if(pool->shutdown){
            pthread_mutex_unlock(&pool->pool_lock);
            free(task);
            pthread_exit(nullptr);
        }
        pthread_mutex_unlock(&pool->pool_lock);
        task->task_func(task->arg);
    }
}

void ThreadPool::addtask(ThreadPool*pool){
    pthread_mutex_lock(&pool->pool_lock);

    while(pool->max_job_num<=pool->job_num){
        pthread_cond_wait(&pool->empty_task,&pool->pool_lock);
    }
    int taskpos  = (pool->job_push++)%pool->max_job_num;
    pool->tasks[taskpos].tasknum = beg++;
    pool->tasks[taskpos].arg = (void*)&pool->tasks[taskpos];
    pool->tasks[taskpos].task_func = pool->taskRun;
    pool->job_num++;

    pthread_mutex_unlock(&pool->pool_lock);
    pthread_cond_signal(&pool->not_empty_task);
}

void ThreadPool::taskRun(void*args){
    PoolTask*task = (PoolTask*)args;
    int num = task->tasknum;
    cout << "task "<<num <<" is running "<<pthread_self() <<"\n";

    sleep(1);
    cout << "task "<<num<<" is done "<<pthread_self()<<"\n";
} 
