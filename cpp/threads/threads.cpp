// #include<bits/stdc++.h>
// #include<thread>

// using namespace std;


// void func(std::string&&name){
//     std::cout << name << std::endl;
// }

// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************
//     const int N = 10;
//     std::array<std::thread,N>threads;
//     for(int i = 0;i<N;i++){
//         threads[i] = std::thread(func,std::move(std::string("Thread")+std::to_string(i+1)));
//     }

//     for(int i = 0;i<N;i++){
//         threads[i].join();
//     }
//     return 0;
// }



// #include<thread>
// #include<iostream>
// #include<array>
// #include<vector>
// #include<unistd.h>


// /**
//  * @brief 
//  * 
//  * @tparam Iter 
//  * @tparam Op 
//  * @tparam BOp 
//  * @tparam Result 
//  * @param first 
//  * @param last 
//  * @param transform 
//  * @param reduce 
//  * @param res 
//  */
// template<typename Iter,typename Op,typename BOp,typename Result>
// void transform_reduce(Iter first,Iter last,Op transform,BOp reduce,Result&res){
//     for(auto it = first;it!=last;it++){
//         res = reduce(res,transform(*it));
//     }
//     sleep(2);
// }

// int main(){
//     const int N = 10000;
//     std::vector<double>numbers;
//     numbers.reserve(N);
//     for(int i = 0;i<N;i++){
//         numbers.push_back((double)i/N);
//     }

//     auto transform = [](double x){
//         return x*x;
//     };
//     auto reduce = [](double a,double b){
//         return a+b;
//     };

//     const int N_Thread = 8;
//     std::vector<std::thread>threads;
//     std::array<double,N_Thread>subResult{0};

//     for(int i = 0;i<N_Thread;i++){
//         auto low = numbers.begin()+i*numbers.size()/N_Thread;

//         auto high = numbers.begin()+(i+1)*numbers.size()/N_Thread;

//         threads.push_back(
//             std::thread(
//                 transform_reduce<std::vector<double>::iterator,
//                 decltype(transform),
//                 decltype(reduce),
//                 double>,low,high,transform,reduce,std::ref(subResult[i])
//             )           
//         );
//     }
//     double result = 0;
//     for (int j = 0; j < N_Thread; j++){
//         threads[j].join();
//         result = reduce(result, subResult[j]);
//     }
//     std::cout << "Result: " << result << std::endl;
//     return 0;
// }




// #include<bits/stdc++.h>
// #include<mutex>
// using namespace std;
// int a = 0;

// class Log{
// public:

//     static Log& getInstance(){
//         //懒汉模式->main之后创建
//         //恶汉模式->main之前创建
//         static Log *log = nullptr;
//         std::call_once(flag,
//         [&]()->void{ 
//             if(log == nullptr)
//                 log = new Log(); 
//         });
//         return *log;
//     }

//     void log(string message){
//         std::cout << __TIME__ << " " << message << std::endl;
//     }

// private:
//     Log(){}
//     Log& operator=(const Log&) = delete;
//     Log(const Log&) = delete;
//     static std::once_flag flag;
// };

// std::once_flag Log::flag;

// void func(){
//     Log::getInstance().log("error");
// }

// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************

//     std::thread t1(func);
//     std::thread t2(func);
//     t1.join();
//     t2.join();


//     return 0;
// }

// #include<bits/stdc++.h>
// #include<mutex>
// #include<condition_variable>
// #include<queue>
// #include<thread>
// using namespace std;

// std::queue<int>q_queue;

// std::mutex q_mutex;
// std::condition_variable q_cv_empty;
// std::condition_variable q_cv_notempty;
// void producer(){
//     for(int i = 0;i<10000;i++){
//             std::unique_lock<std::mutex> lock(q_mutex);

//             while(q_queue.size()>=100){
//                 q_cv_empty.wait(lock);
//             }

//             q_queue.push(i);
//             std::cout << "Producer: " << i << std::endl;
//             q_cv_notempty.notify_one();
        
//     }
// }

// void consumer(){
//     while(1){
        
//             std::unique_lock<std::mutex> lock(q_mutex);
//             while(q_queue.empty()){
//                 q_cv_notempty.wait(lock);
//             }
//             int data = q_queue.front();
//             q_queue.pop();
//             std::cout << "Consumer: " << data << std::endl;
//             q_cv_empty.notify_one();
        
//     }
// }

// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************

//     std::thread t1(producer);
//     std::thread t2(consumer);
//     std::this_thread::sleep_for(std::chrono::seconds(5));

//     t1.join();
//     t2.join();
//     return 0;
// }

//future async

// #include<bits/stdc++.h>
// #include<atomic>
// using namespace std;

// void func1(std::promise<int>&&p){
    
//     p.set_value(200);
   
// }


// void func2(std::future<int>&&p){
//     int result = p.get();
//     std::cout << "Result: " << result << std::endl;
    
// }
// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************
//     // int a = 0;
//     // std::future<int> f1 = std::async(std::launch::async,func,std::ref(a));
//     // std::cout << "f1.get(): " << f1.get() << std::endl;
//     // std::cout << "a: " << a << std::endl;



//     // int a = 0;
//     // std::packaged_task<int(int&)>task(std::bind(func,std::ref(a)));
//     // // task(a);
//     // auto p = task.get_future();
//     // std::thread t(std::move(task),std::ref(a));
//     // // std::this_thread::sleep_for(std::chrono::seconds(2));
//     // std::cout << p.get() << std::endl;
//     // std::cout << a << std::endl;
//     // t.join();
//     std::promise<int> p1;
//     std::future<int> p2 = p1.get_future();
//     std::thread t1(func1,std::move(p1));
//     std::thread t2(func2,std::move(p2));
//     t1.join();
//     t2.join();
    

//     return 0;
// }

// #include<thread>
// #include<iostream>
// #include<vector>
// #include<future>
// void teacher(std::promise<void>&&p){
//     std::cout << "上课" << std::endl;
//     std::this_thread::sleep_for(std::chrono::seconds(3));
//     p.set_value();
//     std::cout << "下课" << std::endl;
// }


// std::mutex m;
// void student(std::shared_future<void>&&sf){
//     sf.wait();
//     std::lock_guard<std::mutex> lock(m);
//     std::cout << "再见" << "(" << std::this_thread::get_id() << ")" << std::endl;
// }


// int main(){
//     std::promise<void>p;
//     std::shared_future<void>f = p.get_future();
//     std::thread t(teacher,std::move(p)); 
    
    
//     std::vector<std::thread>v;
//     v.reserve(20);
//     for(int i = 0;i<20;i++){
//         v.emplace_back(std::thread(student,f));
//     }
//     t.join();
//     for(auto& th : v){
//         th.join();
//     }
    
    

//     return 0;
// }

// #include<bits/stdc++.h>

// std::timed_mutex m1;
// std::timed_mutex m2;
// int a = 0;
// void func1(){
//     while(true){
//         std::unique_lock lock1(m1,std::defer_lock);
//         std::unique_lock lock2(m2,std::defer_lock);
//         if(!lock1.try_lock_for(std::chrono::milliseconds(100))){
//             continue;   
//         }
//         if(!lock2.try_lock_for(std::chrono::milliseconds(100))){
//             continue;
//         }
//         a ++;
//         std::cout << a << std::endl;
//     }
// }
// void func2(){
//     while(true){
//         std::unique_lock lock2(m2,std::defer_lock);
//         std::unique_lock lock1(m1,std::defer_lock);
//         if(!lock1.try_lock_for(std::chrono::milliseconds(100))){
//             continue;
//         }
//         if(!lock2.try_lock_for(std::chrono::milliseconds(100))){
//             continue;   
//         }
//         a ++;
//         std::cout << a << std::endl;
//     }
// }

// int main(){
//     std::thread t1(func1);
//     std::thread t2(func2);
//     t1.join();
//     t2.join();
//     return 0;
// }


// #include<bits/stdc++.h>

// std::timed_mutex m1;
// std::timed_mutex m2;
// int a = 0;
// void func1(){
//     while(true){
//         std::scoped_lock(m1,m2);
//         a ++;
//         std::cout << a << std::endl;
//     }
// }
// void func2(){
//     while(true){
//         std::scoped_lock(m2,m1);
//         a ++;
//         std::cout << a << std::endl;
//     }
// }

// int main(){
//     std::thread t1(func1);
//     std::thread t2(func2);
//     t1.join();
//     t2.join();
//     return 0;
// }


// #include<bits/stdc++.h>
// using namespace std;
// std::shared_mutex smtx;
// std::mutex mtx;
// int a = 0;
// void writes(){
//     std::lock_guard<std::mutex>lock(mtx);
//     a ++;
//     cout << "write: " << a << endl;
//     std::this_thread::sleep_for(std::chrono::seconds(1));
// }
// void reads(){
//     std::shared_lock<std::shared_mutex> lock(smtx);
//     cout << "read: " << a << endl;
//     std::this_thread::sleep_for(std::chrono::milliseconds(500));
// }


// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************
//     std::thread t1([](){
//         while(1){
//             writes();
//         }
//     });
//     std::vector<std::thread>v;
//     v.reserve(4);
//     for(int i = 0;i<4;i++){
//         v.emplace_back(std::thread(
//             [](){
//                 while(1){
//                     reads();
//                 }
//             }
//         ));    
//     }
//     t1.join();
//     for(auto& th : v){
//         th.join();
//     }

//     return 0;
// }


// #include<semaphore>
// #include<thread>
// #include<iostream>
// #include<vector>
// #include<mutex>
// #include<chrono>
// #include<syncstream>

// template<size_t N = 10>
// class CarPark{
// public:
//     CarPark():sem(N){}
//     int enter(){
//         sem.acquire();
//         std::unique_lock lock(mtx);
//         for(int i = 0;i < N;i++){
//             if(spaces[i] == ""){
//                 std::ostringstream oss;
//                 oss << "Car "<<std::this_thread::get_id()<<" entered at "<<i;
//                 spaces[i] = oss.str();
//                 std::osyncstream(std::cout)<<oss.str()<<std::endl;
//                 return i;
//             }    
//         }    
//         throw std::logic_error("No space available!");
//     }

//     void dothing(){
//         std::this_thread::sleep_for(std::chrono::seconds(1));
//     }
//     void leave(int idx){
//         std::osyncstream(std::cout)<< "Car "<<std::this_thread::get_id()<<" leaving"<<std::endl;
//         {
//             std::unique_lock lock(mtx);
//             spaces[idx].clear();
//         }
//             sem.release();
//     }

//     void func(){
//         int spaceid = enter();
//         dothing();
//         leave(spaceid);
//     }
// private:
//     std::array<std::string,N>spaces;
//     std::counting_semaphore<N>sem;
//     std::mutex mtx;
// };

// int main(){
//     const int NCar = 100;
//     const int NSpace = 5;
//     CarPark<NSpace>parks;
//     std::vector<std::thread>vec;
//     for(int i = 0;i<NCar;i++){
//         vec.emplace_back(std::thread(
//             [&parks](){
//                 parks.func();
//             }
//         ));
//     }
//     for(auto&e:vec){
//         e.join();
//     }
//     return 0;
// }




// #include<bits/stdc++.h>

// int func(int x){
//     int a ;
//     std::this_thread::sleep_for(std::chrono::seconds(2));
//     a = x;
//     return a;
// }

// int main(){
//     std::packaged_task<int(int)>task(func);
//     std::cout << "直接调用-------------------"<<std::endl;
//     std::future<int>f1 = task.get_future();
//     task(20);
//     std::cout << "Result : "<<f1.get() << std::endl;
//     task.reset();


//     std::cout << "线程调用-------------------"<<std::endl;

//     f1 = task.get_future();
//     std::thread t(std::move(task),30);
//     std::cout << "Result : "<<f1.get() << std::endl;
//     t.join();

//     return 0;
// }




// #include<bits/stdc++.h>

// struct Runner{
//     std::string name;
//     int time{0};

//     void run(std::latch&start,std::latch&end){
//         start.wait();
//         auto start_time = std::chrono::system_clock::now();
//         std::this_thread::sleep_for(std::chrono::seconds(rand()%10));
//         auto end_time = std::chrono::system_clock::now();
//         time = std::chrono::duration_cast<std::chrono::seconds>(end_time-start_time).count();
//         end.count_down();
//     }

//     bool operator<(const Runner&other){
//         return this->time<other.time;
//     }
// };

// int main(){
//     srand(time(0));
//     std::vector<Runner>runners = {Runner{"张三"},Runner{"李四"},Runner{"王五"},Runner{"马六"}};
//     std::latch start{1};
//     std::latch finish{runners.size()};
//     std::vector<std::thread>threads;
//     for(int i = 0;i<runners.size();i++){
//         threads.emplace_back(&Runner::run,
//         &runners[i],
//         std::ref(start),
//         std::ref(finish));
//     }
//     std::cout << "start race..."<< std::endl;
//     start.count_down();
//     finish.wait();
//     for(auto &p:threads){
//         p.join();
//     }

//     std::cout << "race end..."<<std::endl;
//     std::sort(runners.begin(),runners.end());
//     for(auto&runner:runners){
//         std::cout << runner.name << " : " << runner.time << std::endl;
//     }
//     return 0;
// }   





// #include<bits/stdc++.h>
// using namespace std;
// class Participant{
// public:
//     std::string name;
//     bool alive;
//     Participant(std::string name):name(name),alive(true){}

//     template<typename Barrier>
//     void run(Barrier&b){
//         std::this_thread::sleep_for(std::chrono::seconds(1));
//         for(int i = 0;i<5;i++){
//             std::this_thread::sleep_for(std::chrono::seconds(1));
//             int num = rand()%3;
//             if( num == 0){
//                 b.arrive_and_drop();
//                 alive = false;
//                 break;
//             }else {
//                 b.arrive_and_wait();
//             }
//         }
//     }

//     bool is_alive(){
//         return alive;
//     }
// private:

// };
// int main(){
//     srand(time(0));
//     std::vector<Participant>participants= {
//         Participant("张三"),
//         Participant("李四"),
//         Participant("王五"),
//         Participant("马六"),
//         Participant("哈七"),    
//     };
//     int round = 0;

//     auto func = [&]()->void{
//         round++;
//         std::cout << "Round :"<<round<<"\t";
//         int count = 0;
//         for(auto &p : participants){
//             if(p.is_alive()){
//                 std::cout << p.name <<" ";
//                 count++;
//             }    
//         }
//         std:cout << endl;
//         if(count == 0){
//             std::cout << "over ..." << std::endl;    
//         }
//     };


//     std::barrier finish(participants.size(),func);
//     std::vector<std::thread>threads;
//     for(auto &p : participants){
//         threads.emplace_back([&p,&finish](){
//             p.run(finish);
//         });
//     }
//     for(auto &t : threads){
//         t.join();
//     }


//     return 0;
// }





// #include <coroutine>
// #include <iostream>
// #include <thread>
 
// namespace Coroutine {
//   struct task {
//     struct promise_type {
//       promise_type() {
//         std::cout << "1.create promie object\n";
//       }
//       task get_return_object() {
//         std::cout << "2.create coroutine return object, and the coroutine is created now\n";
//         return {std::coroutine_handle<task::promise_type>::from_promise(*this)};
//       }
//       std::suspend_never initial_suspend() {
//         std::cout << "3.do you want to susupend the current coroutine?\n";
//         std::cout << "4.don't suspend because return std::suspend_never, so continue to execute coroutine body\n";
//         return {};
//       }
//       std::suspend_never final_suspend() noexcept {
//         std::cout << "13.coroutine body finished, do you want to susupend the current coroutine?\n";
//         std::cout << "14.don't suspend because return std::suspend_never, and the continue will be automatically destroyed, bye\n";
//         return {};
//       }
//       void return_void() {
//         std::cout << "12.coroutine don't return value, so return_void is called\n";
//       }
//       void unhandled_exception() {}
//     };
 
//     std::coroutine_handle<task::promise_type> handle_;
//   };
 
//   struct awaiter {
//     bool await_ready() {
//       std::cout << "6.do you want to suspend current coroutine?\n";
//       std::cout << "7.yes, suspend becase awaiter.await_ready() return false\n";
//       return false;
//     }
//     void await_suspend(
//       std::coroutine_handle<task::promise_type> handle) {
//       std::cout << "8.execute awaiter.await_suspend()\n";
//       std::thread([handle]() mutable { handle(); }).detach();
//       std::cout << "9.a new thread lauched, and will return back to caller\n";
//     }
//     void await_resume() {}
//   };
 
//   task test() {
//     std::cout << "5.begin to execute coroutine body, the thread id=" << std::this_thread::get_id() << "\n";//#1
//     co_await awaiter{};
//     std::cout << "11.coroutine resumed, continue execcute coroutine body now, the thread id=" << std::this_thread::get_id() << "\n";//#3
//   }
// }// namespace Coroutine
 
// int main() {
//   Coroutine::test();
//   std::cout << "10.come back to caller becuase of co_await awaiter\n";
//   std::this_thread::sleep_for(std::chrono::seconds(1));
 
//   return 0;
// }


// #include<bits/stdc++.h>
// using namespace std;

// struct channel{
// public:
//     void getData(){
//         std::cout << "consumer is waiting for data ...\n";
//         dataReady.wait(false);
//         std::cout << "consumer got data : " << data << "\n";
//         dataReady.clear();
//     }


//     void setData(std::string&&data){
//         std::this_thread::sleep_for(std::chrono::seconds(3));
//         std::cout << "producer is setting data" << "\n";
//         this->data = data;
//         dataReady.test_and_set();
//         dataReady.notify_one();
//     }


// private:
//         std::string data;
//         std::atomic_flag dataReady = ATOMIC_FLAG_INIT;
// };



// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************
//     channel c;
//     std::thread t1(&channel::setData,&c,"hello");
//     std::thread t2(&channel::getData,&c);
//     t1.join();
//     t2.join();

//     return 0;
// }


// #include<atomic>
// #include<thread>
// #include<iostream>
// #include<functional>
// std::atomic<int>a = 0;
// int main(){
//     std::thread t1([](std::atomic<int>&a){
//         for(int i = 0;i<10000;i++){
//             a++;
//         }
//     },std::ref(a));
//     std::thread t2([](std::atomic<int>&a){
//        for(int i = 0;i<10000;i++){
//            a++;
//        } 
//     },std::ref(a));


//     t1.join();
//     t2.join();
//     std::cout << a << std::endl;
// }




#include<atomic>
#include<memory>
#include<syncstream>
#include<iostream>
#include<thread>

template<typename T>
class lfs{
private:
    struct node{
        T data;
        std::shared_ptr<node>next;
        node(T d):data(d){}

    };

    std::atomic<std::shared_ptr<node>>head;
public:
    lfs() = default;
    lfs(const lfs&other) = delete;
    lfs&operator=(const lfs&other) = delete;

    void push(T val){
        std::shared_ptr<node>new_node(new node(val));
        new_node->next = head.load();
        while(!head.compare_exchange_strong(new_node->next,new_node));
        std::osyncstream(std::cout ) << "push " << val << std::endl;
    }

    bool pop(){
        std::shared_ptr<node>old_head = head.load();
        if(!old_head){
            return false;
        }

        while(old_head&&!head.compare_exchange_strong(old_head,old_head->next));
        if(old_head){
            std::osyncstream(std::cout ) << "pop " << old_head->data << std::endl;
            return true;
        }      


        return false;     
    }

};

void pushs(lfs<int>&l,int start,int end){
    for (int i = start; i < end; i++){
        l.push(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void pops(lfs<int>&l,int count){
    for(int i = 0;i < count;i++){
        l.pop();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}


int main(){
    lfs<int>l;
    std::thread t1(pushs,std::ref(l),0,10);
    std::thread t2(pops,std::ref(l),10);
    std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    t1.join();
    t2.join();

    return 0;
}
