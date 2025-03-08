#include<iostream>
#include<array>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<chrono>
#include<semaphore>
#include<syncstream>
#include<ctime>
#include<cstdlib>
#include<atomic>
#include<vector>
template<size_t N = 6>
class ThreadBuffer{
    public:
        ThreadBuffer():sem_reader(0),sem_writer(N){
            for(int i = 0;i<N;i++){
                buffer[i] = ' ';
            }
        }
        char prepare(){
            std::this_thread::sleep_for(std::chrono::milliseconds(rand()%900));
            return (static_cast<char>(rand()%26+'A'));
        }
        void process(){
            std::this_thread::sleep_for(std::chrono::milliseconds(rand()%1000));
        }

        void printBuffer(){
            std::osyncstream outs(std::cout);
            outs << "BUFFER: |";
            for(auto c : buffer){
                outs << c << "|";
            }
            outs << std::endl;

        }
        void writeToBuffer(int max){
            std::osyncstream(std::cout) << "writer is ok.\n";
            for(int i = 0;i<max;i++){
                char ch = prepare();
                sem_writer.acquire();
                buffer[i%buffer.size()] = ch;
                std::osyncstream(std::cout) << "写线程:写入"<<ch<<".\t\t";
                printBuffer();
                sem_reader.release();
            }
        }
        void readFromBuffer(int max){
            std::osyncstream(std::cout) << "reader is ok.\n";
            for(int i = 0;i<max;i++){
                sem_reader.acquire();
                auto idx = i%buffer.size();
                char ch = buffer[idx];
                process();
                buffer[idx] = ' ';
                std::osyncstream(std::cout) << "读线程:读出"<<ch<<".\t\t";
                printBuffer();
                sem_writer.release();
            }
        }

    private:

        std::array<char,N>buffer;
        std::counting_semaphore<N>sem_reader;
        std::counting_semaphore<N>sem_writer;
};
int main(){
    srand(time(nullptr));
    ThreadBuffer<6>tb;
    
    std::thread t2(
        [&tb](){
            tb.readFromBuffer(1000);
        }
    );
    std::thread t1(
        [&tb](){
            tb.writeToBuffer(1000);
        }
    );

    t1.join();
    t2.join();

}


