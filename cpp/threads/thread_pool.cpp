#include<iostream>
#include<vector>
#include<queue>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<functional>


class ThreadPool{
public:
    ThreadPool(int num_threads):stop(false){
        for(int i = 0;i<num_threads;i++){
            threads.emplace_back([this](){
                while(1){
                    std::unique_lock<std::mutex>lock(mtx);
                    cv.wait(lock,[this]{return stop || !tasks.empty();});

                    if(stop && tasks.empty()){
                        return;
                    }

                    auto task = std::move(tasks.front());
                    tasks.pop();

                    lock.unlock();
                    
                    task();
                }
                

            });
        }
    }


    ~ThreadPool(){
        {
            std::unique_lock<std::mutex>lock(mtx);
            this->stop = true;
        }
        cv.notify_all();
        for(auto&p : this->threads){
            p.join();
        }
    }

    //add task to queue
    template<typename F,typename...Args>
    void enqueue(F&&f,Args&&...args){
        std::function<void()>task = std::bind(std::forward<F>(f),std::forward<Args>(args)...);
        {
            std::unique_lock<std::mutex>lock(mtx);
            tasks.emplace(std::move(task));
        }
        cv.notify_one();
    }
private:
    std::vector<std::thread>threads;
    std::queue<std::function<void()>>tasks;
    std::mutex mtx;
    std::condition_variable cv;
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    bool stop;

};


int main(){
    ThreadPool pool(8);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    for(int i = 0;i<10;i++){
        pool.enqueue(
            [i](){
                std::cout<<"Task "<<i<<std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        );    
    }
    

    return 0;
}

