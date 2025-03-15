#include<iostream>
#include<coroutine>
#include<thread>
#include<chrono>
#include<future>

class promise{
public:
    struct promise_type{

        std::future<int>future;
        int r;
        promise get_return_object(){
            return promise{std::coroutine_handle<promise::promise_type>::from_promise(*this)};
        }
        std::suspend_never initial_suspend()noexcept{return{};}
        std::suspend_always final_suspend()noexcept{return{};}
        std::suspend_always yield_value(int n){
            r = n*10;
            return {};
        }
        void unhandled_exception(){}
        
    };
    std::coroutine_handle<promise_type>_h;
    ~promise(){
        _h.destroy();
    }
private:
};

struct test{
    int r;
    bool await_ready(){
        return false;
    } // 等待
    void await_suspend(std::coroutine_handle<promise::promise_type>h){ //协程暂停的时候会调用这个函数
        
        h.promise().future = std::move(std::async([this,h](){
            int n = 3;
            for(int i = 1;i<n;++i){
                (this->r)*=i;
            }
            if(!h.done())h.resume();
            return r;
        }));
    }
    int await_resume()const noexcept{return r;}
};

inline auto operator co_await(test t){
    std::cout << "co_await重载"<<std::endl;
    return t;
}

promise f(){
    test t{6};
    int a = 0;
    int v = co_await t;
    std::cout << "v:" << v << std::endl;
    co_yield 100;
}
int main(int argc, char const *argv[]){
    using namespace std::literals;
    auto result = f();
    std::cout << "main" << std::endl;
    result._h.promise().future.wait();
    // result._h.resume();
    std::cout << std::boolalpha << "done :" << result._h.done() << std::endl;
    std::cout << "co_yield value = " << result._h.promise().r << std::endl;

}
