#ifndef TIME_WHEEL
#define TIME_WHEEL

#include <time.h>
#include <netinet/in.h>
#include <stdio.h>


#define BUFFER_SIZE 64
#define TIME_OUT 1

class tw_timer;
//数据结构
struct tw_data{
    sockaddr_in addr;
    int sockfd;
    char buf[BUFFER_SIZE];
    tw_timer*timer;
};

//定时器类
class tw_timer{
public:
    tw_timer(int _rotation,int _time_slot):cb(nullptr),rotation(_rotation),time_slot(_time_slot),next(NULL),prev(NULL){}
public:
    int rotation; /* 轮转次数 */
    int time_slot; /* 时间槽 */
    void (*cb)(tw_data*); /* 回调函数*/
    tw_data*data; /* 客户数据 */
    tw_timer*next; /* 下一个定时器 */
    tw_timer*prev; /* 上一个定时器 */
};

//时间轮
class tw{
public:
    tw():cur_slot(0){
        for(int i = 0;i<N;i++){
            slots[i] = nullptr;
        }
    }
    ~tw(){
        for(int i = 0;i<N;i++){
            tw_timer*tmp = slots[i];
            while(tmp){
                slots[i] = tmp->next;
                delete tmp;
                tmp = slots[i];
            }
        }
    }

public:
    /* 添加定时器 */
    tw_timer*add_timer(int timeout,void (*s)(tw_data*)){
        if(timeout < 0){
            return nullptr;
        }
        int ticks = 0;
        if(timeout < SI){
            ticks = 1;
        }else{
            ticks = timeout/SI;
        } 

        int rotation = ticks/N;
        int time_slot = (cur_slot+(ticks%N))%N;
        tw_timer*timer = new tw_timer(rotation,time_slot);
        timer->cb = s;
        timer->data = new tw_data;
        timer->data->timer = timer;
        if(!slots[time_slot]){
            slots[time_slot] = timer;
            timer->next = nullptr;
            timer->prev = nullptr;
        }else{
            timer->next = slots[time_slot];
            slots[time_slot]->prev = timer;
            slots[time_slot] = timer;
        }

        return timer;
    }

    /* 移除定时器 */
    void del_timer(tw_timer*timer){
        if(!timer){
            return ;
        }else{

            int ts = timer->time_slot;
            if(timer == slots[ts]){
                slots[ts] = timer->next;
                if(slots[ts]){
                    slots[ts]->prev = nullptr;
                }
                delete timer;
            }else{
                timer->prev->next = timer->next;
                if(timer->next){
                    timer->next->prev = timer->prev;
                }
                delete timer;
            }
        }
    }

    /* 时间轮转动 */
    void tick(){
        tw_timer*tmp =slots[cur_slot];
        printf("cur_slot : %d \n",cur_slot);
        while(tmp){
            if(tmp->rotation > 0){
                tmp->rotation --;
                tmp = tmp->next;
            }else{
                tmp->cb(tmp->data);
                if(tmp == slots[cur_slot]){
                    printf("delete timer from cur_slot \n");
                    slots[cur_slot] = tmp->next;
                    delete tmp;
                    if(slots[cur_slot]){
                        slots[cur_slot]->prev = nullptr;
                    }
                    tmp = tmp->next;
                }else{
                    tmp->prev->next = tmp->next;
                    if(tmp->next){
                        tmp->next->prev = tmp->prev;
                    }
                    tw_timer*next = tmp->next;
                    delete tmp;
                    tmp = next;
                }
            }
            cur_slot = (++cur_slot)%N;
        }
    }
private:
    static const int N = 60; /* 时间槽个数 */
    static const int SI = 1; /* 转动间隔*/
    tw_timer*slots[N]; /* 时间槽 */
    int cur_slot; /* 当前时间槽 */
};


#endif