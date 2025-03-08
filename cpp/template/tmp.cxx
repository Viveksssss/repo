/**
 * @file tmp.cxx
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-02-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include<atomic>
#include<iostream>
#include<syncstream>
#include<thread>
#include<memory>

template<typename T>
class LockFreeStack{
    private:
        struct node{
            T data;
            std::shared_ptr<node>next;
            node(T data):data(data){}
        };

        std::atomic<std::shared_ptr<node>>head;
    public:
        LockFreeStack() = default;
        LockFreeStack(const LockFreeStack&) = delete;
        LockFreeStack& operator=(const LockFreeStack&) = delete;

        void push(T data){
            std::shared_ptr<node>new_node(new node(data));
            new_node->next = head.load();
            while(!head.compare_exchange_strong(new_node->next,new_node));
            std::osyncstream(std::cout) << "push "<<data<<std::endl;
        }

        bool pop(){
            std::shared_ptr<node>old_head = head.load();
            if(!old_head){
                return false;
            }
            while(old_head&&!head.compare_exchange_strong(old_head,old_head->next));
            if(old_head){
                std::osyncstream(std::cout) << "pop "<<old_head->data<<std::endl;
                return true;
            }

            return false;
        }
};


void pushs(LockFreeStack<int>&stack,int start,int end){
    for(int i = start;i<end;i++){
        stack.push(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void pops(LockFreeStack<int>&stack,int count){
    for (int i = 0; i < count; i++){
        stack.pop();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
}


int main(){
    LockFreeStack<int>stack;
    std::thread t1(pushs,std::ref(stack),0,100);
    std::thread t2(pops,std::ref(stack),100);
    t1.join();
    t2.join();
    return 0;
}