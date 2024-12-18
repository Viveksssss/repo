// #include<bits/stdc++.h>
// using namespace std;

// class base{
//     public:
//         int age;
//         char *name;
//     public:
//         base(int a, char *n):age(a),name(n){
//             cout<<"Constructor of base class called"<<endl;
//         }
//         virtual ~base(){
//             cout<<"Destructor of base class called"<<endl;
//             delete[] name;
//         }
//         base(const base& b){
//             cout<<"Copy constructor of base class called"<<endl;
//             age=b.age;
//             name=new char[strlen(b.name)+1];//char*尾部有\0，所以需要+1
//             strcpy(name,b.name);
//         }
//         base& operator=(const base&b){
//             cout<<"Assignment operator of base class called"<<endl;
//             if(this!=&b){
//                 age=b.age;
//                 delete[] name;
//                 name=new char[strlen(b.name)+1];
//                 strcpy(name,b.name);
//             }
//             return *this;
//        } 

//        virtual void display(){
//             cout<<"Age: "<<age<<", Name: "<<name<<endl;
//        }

// };

// class derived:public base{
//     public :
//         int marks;
//         char *subject;
//     public:
//         derived(int a,char*n,int m,char* p):base(a,n),marks(m),subject(p){
//             cout<<"Constructor of derived class called"<<endl;
//         }
//         ~derived() override{
//             cout<<"Destructor of derived class called"<<endl;
//         }
//         derived(const derived& d):base(d),marks(d.marks){
//             cout<<"Copy constructor of derived class called"<<endl;
//         }
//         derived& operator=(const derived&d){
//             cout<<"Assignment operator of derived class called"<<endl;
//             if(this!=&d){
//                 base::operator=(d);
//                 marks=d.marks;
//             }
            
//             return *this;
//         }
//         void display(){
//             cout<<"Marks: "<<marks<<endl;
//         }

// };

// class awov{
//     public :
//         awov(){
//             cout<<"Constructor of awov class called"<<endl;
//         }
//         virtual ~awov() {
//             cout << "Destructor of awov class called" << endl;
//         }
//         awov(const awov&){
//             cout<<"Copy constructor of awov class called"<<endl;
//         }
        
//         awov(const awov &&){
//             cout<<"Move constructor of awov class called"<<endl;
//         }

//         virtual void display(){ cout<<"awov class"<<endl; }
// };



// class awov1:public awov{
//     public :
//         char *name;

//         awov1(char*p):name(p){
//             cout<<"Constructor of awov1 class called"<<endl;
//         }
//         ~awov1() override{
//             // awov::~awov();没必要显式调用，子类的析构调用时，父类的析构会自动调用
//             cout<<"Destructor of awov1 class called"<<endl;
//         }
//         awov1(const awov1&a):awov(a),name(new char[strlen(a.name)+1]){
//             cout<<"Copy constructor of awov1 class called"<<endl;
//             strcpy(name,a.name);
//         }

//         awov1(const awov1&&){
//             cout<<"Move constructor of awov1 class called"<<endl;
//         }

//         void display() override{    cout<<"awov1 class"<<endl; }
// };

// template<int N>
// constexpr static int Fib = Fib<N-1> + Fib<N-2>;
// template<>
// constexpr  int Fib<0> = 0;
// template<>
// constexpr  int Fib<1> = 1;
// #include<queue>

// // explicit 防止编译器自动继续进行的隐式转换
// class MyString{
//     public:
//     MyString(const char*str){

//     }
//     explicit MyString(int len){ //假如explicit后，s = 123;就是错误的，不会有歧义

//     }
// };


// int main(){
//     //***************************************
//         std::ios_base::sync_with_stdio(0);
//         std::cin.tie(0);
//         std::cout.tie(0);
//         //***************************************
//     // cout << Fib<30><<endl;
//     // cout << Fib<20><<endl;
//     MyString s("asdasd");
//     s ="sdasd";
//     s = "123";//没问题因为编译器会自动构造==的构造器--为防止这种自动构造，我们可以假如关键字explicit


// }


//单例模式
// #include<bits/stdc++.h>
// using namespace std;

// class Chairman{
//     // public:
//     private:
//         static Chairman*Singleman;
//         Chairman(){}
//         Chairman(const Chairman&){}
//     public:
//         static Chairman*get_instance(){
//             return Singleman;
//         }
// };
// Chairman* Chairman::Singleman = new Chairman;

// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************

//     Chairman*s = Chairman::get_instance();
//     Chairman*s2 = Chairman::get_instance();
//     cout << s<<endl;
//     s = nullptr;//这里虽然可以改变s的指针，但仅仅改变的是指向单例的指针，通过单例创造出来的指针对象不受影响
//     std::cout<<s<<"\n";
//     std::cout<<s2<<"\n";

//     return 0;
// }



//单例模式-打印机案例
// #include<bits/stdc++.h>
// using namespace std;

// class Print{
//     private:
//         Print(){cout << "Print调用"<<endl;}//通过单例模式，在main还未开始之前就可以打印文字
//         Print(const Print&){}
//     private:
//         static Print* SinglePrinter;
//     public:
//         static Print*get_instance(){
//             return SinglePrinter;
//         } 
// };
// Print*Print::SinglePrinter = new Print;

// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************
//     cout << "main函数调用"<<endl;
//     Print* pt = Print::get_instance();
//     cout << pt;

//     return 0;
// }

// #include<bits/stdc++.h>
// using namespace std;

// class animal{
//     public :int a;
//     public:
//         virtual void speak() const{//virtual关键字使得子类可以重写父类的speak方法
//             cout << "animal speak"<<endl;
//         }
// };

// class dog :virtual public animal{
//     public :
//         void speak()const override{
//             cout << "dog speak"<<endl;
//         }
// };

// class cat :virtual public animal{
//     public :
//         void speak() const override{
//             cout << "cat speak"<<endl;
//         }
// };

// void doSpeak(const animal&a){//传入引用，实现多态性
//     a.speak();
// }
// template<int N>
// constexpr static int Fib = Fib<N-1>+Fib<N-2>;
// template<> constexpr int Fib<0> = 0;
// template<> constexpr int Fib<1> = 1;
// //template<> indicate that we wre specialize the template for N=0 and N=1

// int main(){
      
//     // cout << *((int*)*(int*)&hhh+1)<<endl;//通过地址偏移量找到cat
//     // cout << *((int*)*((int*)&hhh+1)+1)<<endl;//通过地址偏移量找到dog

//     //通过地址偏移量找到a
//     // cout << ((animal*)((char*)&hhh+*((int*)*(int*)&hhh+1)))->a<<endl;
//     // cout << *((int*)((char*)&hhh+*((int*)*((int*)&hhh+1)+1)))<<endl;

    
//     // animal*p = new dog;
//     // ((void(*)()) (*(int*)*(int*)p))();
//     cout << Fib<30><<endl;
    
// }


//当包含含有类模板的文件的时候，我们通常不会将.h和.cpp文件分开，而是将所有的类模板都放在一个文件中，这样可以减少编译时间。
//同时,后缀名约定为.hpp



//友元函数（含模板）的类外实现：复杂
//首先类内定义，同时函数名后要加<>,表示是模板函数
//然后在类外实现，加上模板参数正常编写
//但是仍然编译不通过，原因是，我们在类外实现时，需要实例化模板，但是实例化模板需要知道模板参数，而模板参数在类外无法获得，所以编译器无法实例化模板。
//解决方法：
//首先在类外全局声明友元函数
//同时把参数涉及到的类也声明出来
// #include"String.cpp"
// #include<bits/stdc++.h>
// using namespace std;


// //example 1
// template<class T1,class T2>
// class Person;

// template<class T1,class T2>
// void ShowPerson(Person<T1,T2>&p);


// //example 2
// template<class T1,class T2>
// void hhh(T1 name,T2 age);

// template<class T1,class T2>
// class Person{
//     T1 name;
//     T2 age;
//     public :
//         friend void ShowPerson<>(Person<T1,T2>&p);
//         friend void hhh<>(T1 name,T2 age);
//         Person(T1 name,T2 age);        
// };

// //out of class implementation of template functions needs to be like this:
// template<class T1,class T2>
// Person<T1,T2>::Person(T1 name,T2 age){
//     this -> name = name;
//     this -> age = age;
// }


// //example  1
// template<class T1,class T2>
// void ShowPerson(Person<T1,T2>&p){
// }

// //example 2
// template<class T1,class T2>
// void hhh(T1 name,T2 age){
// }


// int main(){
//     //***************************************
//     // std::ios_base::sync_with_stdio(0);
//     // std::cin.tie(0);
//     // std::cout.tie(0);
//     //***************************************
//     // Person<String,int>p =Person<String,int>("John",2);
//     // ShowPerson(p);
//     // hhh<String ,int>("John",2);

    
//     return 0;
// }


// #include<bits/stdc++.h>
// #include<stdexcept>
// using namespace std;


// class myexception{
//     public:
//         myexception(){cout << "constructor of myexception called"<<endl;}
//         myexception(const myexception& e){cout << "copy constructor of myexception called"<<endl;}
//         ~myexception(){cout << "destructor of myexception called"<<endl;}
// };

// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************
//     //1.0
//     // try{
//     //     throw myexception();
//     // }
//     // catch(myexception e){
//     //     cout << "catch exception"<<endl;
//     // }
//     // //2.0
//     // try{
//     //     throw myexception();
//     // }
//     // catch(myexception &e){
//     //     cout << "catch exception"<<endl;
//     // }
//     //3.0不适用
//     // try{
//     //     throw &(myexception());//throwing temporary object is not secure,so we can not do this successfully. 
//     // }
//     // catch(myexception *e){
//     //     cout << "catch exception"<<endl;
//     // }

//     int a[10];
//     try{
//         cout << a[12]<<endl;
//         throw runtime_error("out of range");
//     }
//     catch(exception &e){
//         cout << e.what()<<endl;
//     }

//     return 0;
// }


// #include<iostream>
// #include<chrono>

// #include<vector>
// using namespace std;
// int main(int argc,char*argv[]){

//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);


//     // auto start = std::chrono::system_clock::now();

//     //     for(int i = 0;i<10000000;i++){
//     //         cout << i<<"\n";
//     //     }

//     // auto end = std::chrono::system_clock::now();

//     // std::chrono::duration<double> diff = end-start;
//     // std::cout << "代码运行时间: " << diff.count() << " 秒\n";


//     stacj

// }

// #include<bits/stdc++.h>
// using namespace std;

// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************
//     auto start = std::chrono::system_clock::now();
//     vector<int>vec1;
//     vec1.reserve(10000000);
//     std::iota(vec1.begin(),vec1.end(),1);
//     vector<int>vec2;
//     vec2.reserve(10000000);
//     std::copy(vec1.begin(),vec1.end(),std::back_inserter(vec2));
//     // for(int i = 0;i<10000000;i++){
//         // vec2[i] = vec1[i];
//     // }
//     auto end = std::chrono::system_clock::now();

//     std::chrono::duration<double> diff = end-start;
//     std::cout << "代码运行时间: " << diff.count() << " 秒\n";


//     return 0;
// }




#include<bits/stdc++.h>
using namespace std;

//NVI(Non-Virtual Interface)手法
// class pureclass{
//     public:
//         virtual ~pureclass(){
//             cout << "pureclass destructor called"<<endl;
//         }
//     private:
//         virtual void display() const= 0;
// };

// void pureclass::display() const{
//     cout << "pureclass display"<<endl;
// }

// class derivedclass : public pureclass{
//     public:
//         void displays() const{
//             this->display();
//         }
//         virtual ~derivedclass(){
//             cout << "derivedclass destructor called"<<endl;
//         } 

//     private:
//         virtual void display() const override{
//             cout << "derivedclass display"<<endl;
//         }
// };


//Startegy pattern
class Gamecharacter;
int defaultHealthCalc(const Gamecharacter &gc){
    return 100;
}
class Gamecharacter{
    public :
        typedef int(*HealthCalc)(const Gamecharacter &);
        Gamecharacter(HealthCalc hcf = defaultHealthCalc):healthcalc(hcf){}
        int getHealth() const{
            return healthcalc(*this);
        }
    private:
        HealthCalc healthcalc;
};
//函数指针
typedef int (*func)(const int, const int);
//回调函数
int add(const int a,const int b){
    return a + b;
}
int minuss(const int a,const int b){
    return a - b;
}
//高阶函数
int funcc(func f,const int a,const int b){
    return f(a,b);
}


class Game{
    public:
        virtual void play(){
            cout << "yes" << endl;
        }
};
class GameFirst:public Game{
    public :
        void play(){
            cout << "first game" << endl;
        }
};
class GameSecond:public GameFirst{
    public :
        void play(){
            cout << "second game" << endl;
        }
};

int main()
{
    //***************************************
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    //***************************************
    // cout << funcc(add, 1, 2) << endl;
    // cout << funcc(minuss, 1, 2) << endl;

    // std::function<int(const int, const int)> funs1 = add;
    // std::function<int(const int, const int)> funs2 = std::bind(minuss, 1, 2);
    // cout << funs1(1, 2) << endl;
    // cout << funs2(1, 2) << endl;
    Game player1;
    GameFirst player2;
    GameSecond player3;
    std::function<void()> func1 = std::bind(&Game::play, &player1);
    std::function<void()> func2 = std::bind(&Game::play, &player2);
    std::function<void()> func3 = std::bind(&Game::play, &player3);
    func1();
    func2();
    func3();
    return 0;
}
