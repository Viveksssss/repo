#include<iostream>
#include<thread>
#include<coroutine>
#include<future>
/*  
 *    this src write for coroutines
 *
 * */

class Awaiter{
public:
    bool await_ready(){
        return false;
    }

    void await_suspend(std::coroutine_handle<> handle){
        std::async([=](){
              using namespace std::chrono_literals;
              // sleep 1s
              std::this_thread::sleep_for(5s); 
              // 恢复协程
              handle.resume();
            
        });
    }
    
    Awaiter await_transform(int value) {  // 需要返回Awaiter对象
        this->value = value;
        return Awaiter(value);  // 构造包含value的Awaiter
    }

    int await_resume(){
        return value;
    }
    Awaiter(int value):value(value){}
private:
    int value;
};


class Result{
public:
    class promise_type{
    public:
        Result get_return_object(){
            return Result{std::coroutine_handle<Result::promise_type>::from_promise(*this)};
        }
        std::suspend_never initial_suspend()noexcept{return {};}
        std::suspend_never final_suspend()noexcept{return {};}
    
        void return_value(int value){
            
        }
        void unhandled_exception() {
            auto exception = std::current_exception(); // 获取当前异常
            std::rethrow_exception(exception); // 抛出异常
        }

        Awaiter await_transform(int value) {
              this->value = value;
              return Awaiter(value);
        }
        int value;
    };
    int next(){
        handle.resume();
        return handle.promise().value;
    }

    explicit Result(std::coroutine_handle<promise_type> _handle) 
            : handle(_handle) {}
private:
    std::coroutine_handle<promise_type> handle;
};


Result sequence(){
    int i = 0;
    while(true){
        co_await i++;
    }
}



int main(){
    auto generator = sequence();
    for(int i = 0;i<5;i++){
        std::cout << generator.next() << std::endl;
    }
    return 0;
}
