#include<iostream>
#include<memory>
#include<cstring>
using namespace std;
template<class T>

class Array{
    private:
        T*arr; //pointer to real array address

        int arr_size; //size of the array

        int arr_capacity; //capacity of the array

    public:
        //constructor
        int size(){
            return this -> arr_size;
        }

        int capacity(){
            return this -> arr_capacity;
        }
        Array(){
            this -> arr_capacity = 16;
            this -> arr_size = 16;
            this -> arr = new T[16];
            memset(this -> arr,0,16);
        }
        Array(int capcacity){
            this -> arr_capacity = capcacity;
            this -> arr_size = arr_capacity;
            this -> arr = new T[capcacity];
        }
        Array(int capacity,T s){
            this -> arr_capacity = capacity;
            this -> arr_size = capacity;
            this -> arr = new T[capacity];
            memset(this -> arr,s,capacity);
        }
        //copy constructor
        Array(const Array<T>&arr){
            this -> arr_capacity = arr.arr_capacity;
            this -> arr_size = arr.arr_size;
            if(this -> arr != nullptr)
                delete[] this -> arr;
            this -> arr = new T[arr.arr_capacity];
            memcpy(this -> arr,arr.arr,arr.arr_size*sizeof(T));
        }
        //destructor
        ~Array(){
            if(this -> arr !=nullptr){
                delete[] this -> arr;
                this -> arr = nullptr;
            }
            this -> arr_capacity = 0;
            this -> arr_size = 0;
        }
        //operator overloading
        T& operator=(const Array<T>&arr){
            if(this->arr){
                delete[] this->arr;
                this -> arr = nullptr;
            }
            this -> arr_capacity = arr.arr_capacity;
            this -> arr_size = arr.arr_size;
            this -> arr = new T[arr.arr_capacity];
            memcpy(this -> arr,arr.arr,arr.arr_size*sizeof(T));
            return *this;
        }

        T& operator[](int index){
            if(index < 0 || index >= this -> arr_capacity)
                throw std::out_of_range("Index out of range");
            return this -> arr[index];
        }

        void push_back(T val){
            if(this -> arr_size == this -> arr_capacity){
                this -> arr_capacity *=2;
                T* new_arr = new T[this -> arr_capacity];
                memcpy(new_arr,this -> arr,this -> arr_size*sizeof(T));
                delete[] this -> arr;
                this -> arr = new_arr;
                this -> arr[this->arr_size++] = val;
            }
            else{
                this -> arr[this->arr_size++] = val;
            }
        }

        void pop_back(){
            if(this -> arr_size == 0)
                throw std::out_of_range("Array is empty");
            this -> arr_size--;
        }

        
};

