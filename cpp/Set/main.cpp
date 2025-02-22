#include "Set.cpp"
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Compare{
    public:
        bool operator()(int a) {
            return a > 20;
        }
};
class Compare2{
    public :
    bool operator()(int a) {
        return a <= 20;
    }
};

template<typename T>
int nums(vector<int>vec, T func){
    int n = 0;
    for(size_t i=0;i<vec.size();i++){
        if(func(vec[i])){
            n++;
        }
    }
    return n;
}


class A{
    public :
        void print(int x){
            printf("%d\n",x);
        }
};
class B
{
public:
    void print(int x)
    {
        printf("%d\n", x);
    }
};
template<typename T>
class C{
    public :
        void PP(T x){
            x.print(10);
        }
};
template<typename T>
class D:public C<T>{
    public:
        using C<T>::PP;
        void TT(T x){
            // 一般来说，D继承了C，但是由于T的不确定，D并不清楚T的类型，所以在模板被具现化之前
            // 并不知道C<T>是什么，更准确来说并不知道它是否有个PP函数。
            //编译器也不会倾向于主动去base class作用域中寻找是否存在PP这个函数，
            //  PP(x);-error!

            //解决方法有三种、
        //1.this->调用
            // this->PP(x);
        //2.using声明：！同时using声明不能放在函数中，只能放在类内
            // PP(x);
        //3.明确指出作用域::这第三个方法有个不妥的地方，加入PP是个virtual，那么这样将去取消其绑定行为
            // C<T>::PP(x);

            PP(x);
        }
};


int main(){
    
    

    A a;
    C<A> c;
    c.PP(a);
    D<A> d;
    d.TT(a);
}