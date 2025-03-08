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
// class Gamecharacter;
// int defaultHealthCalc(const Gamecharacter &gc){
//     return 100;
// }
// class Gamecharacter{
//     public :
//         typedef int(*HealthCalc)(const Gamecharacter &);
//         Gamecharacter(HealthCalc hcf = defaultHealthCalc):healthcalc(hcf){}
//         int getHealth() const{
//             return healthcalc(*this);
//         }
//     private:
//         HealthCalc healthcalc;
// };
// //函数指针
// typedef int (*func)(const int, const int);
// //回调函数
// int add(const int a,const int b){
//     return a + b;
// }
// int minuss(const int a,const int b){
//     return a - b;
// }
// //高阶函数
// int funcc(func f,const int a,const int b){
//     return f(a,b);
// }


// class Game{
//     public:
//         virtual void play(){
//             cout << "yes" << endl;
//         }
// };
// class GameFirst:public Game{
//     public :
//         void play(){
//             cout << "first game" << endl;
//         }
// };
// class GameSecond:public GameFirst{
//     public :
//         void play(){
//             cout << "second game" << endl;
//         }
// };

// int main()
// {
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************
//     // cout << funcc(add, 1, 2) << endl;
//     // cout << funcc(minuss, 1, 2) << endl;

//     // std::function<int(const int, const int)> funs1 = add;
//     // std::function<int(const int, const int)> funs2 = std::bind(minuss, 1, 2);
//     // cout << funs1(1, 2) << endl;
//     // cout << funs2(1, 2) << endl;
//     Game player1;
//     GameFirst player2;
//     GameSecond player3;
//     std::function<void()> func1 = std::bind(&Game::play, &player1);
//     std::function<void()> func2 = std::bind(&Game::play, &player2);
//     std::function<void()> func3 = std::bind(&Game::play, &player3);
//     func1();
//     func2();
//     func3();
//     return 0;
// }




// #include<bits/stdc++.h>
// using namespace std;

// void heapfiy(vector<int>&arr,int i,int n){
//     int lson, rson, maxs;
//     maxs = i;
//     lson = 2 * i + 1;
//     rson = 2 * i + 2;
//     if(lson<n&&arr[lson]>arr[maxs]){
//         maxs = lson;
//     }
//     if(rson<n&&arr[rson]>arr[maxs]){
//         maxs = rson;
//     }
//     if(maxs!=i){
//         swap(arr[i], arr[maxs]);
//         heapfiy(arr, maxs, n);
//     }
// }

// void heapsort(vector<int>&arr,int n){
//     int i;
//     for (i = n / 2 - 1; i >= 0;i--){
//         heapfiy(arr, i,n);
//     }
//     for (i = n - 1; i > 0; i--) {
//         swap(arr[0], arr[i]);
//         heapfiy(arr, 0, i);
//     }
// }


// int main(){
//     vector<int>arr = {1, 7, 4, 3, 67, 9, 90, 5, 4};
//     int n = 9;
//     heapsort(arr,n);
//     for (int i = 0; i < n; i++) {
//         cout << arr[i] << " ";
//     }
//     return 0;
// }




// #include<bits/stdc++.h>
// using namespace std;

// class T{
//     public :
//     explicit T(int x = 0) { cout << x << endl; }
// };

// //返回类型  函数名称（参数列表）;
// // T       t1     (int(x));有歧义，既有可能是返回类型为T的函数声明，也有可能是T(int x)的构造函数声明。
// //编译器会默认认为是第一种情况，所以会报错。


// class Top{
// };
// class Bottom:public Top{
// };

// class DD:public Bottom{
// };

// template<typename T>
// class smartptr{
//     public:
//         explicit smartptr(T*p = nullptr):ptr(p){
//         }

//         template<typename U>
//         smartptr(const smartptr<U>&other):ptr(other.get()){
//             //这个构造函数的前面不要加explicit限定
//             //这样编译器会根据raw pointer的类型隐式转换构造
//             //如果两个指针不存在隐式转换的关系，就会报错
//             //正好藉由原始指针的转换关系提供了智能指针的隐式转换
//         }
//         template<typename U>
//         smartptr<T>&operator=(const smartptr<U>&other){
//             ptr = other.get();
//             return *this;
//         }
//         template <typename U>
//         void operator=(const smartptr<U> &other){
//             ptr = other.get();
//         }

//         T* get()const{
//             return ptr;
//         }
//     private:
//         T*ptr;
// };

// int main()
// {
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************
//     smartptr<Bottom>p1(new DD);
//     smartptr<Top>p2(p1);
//     smartptr<Top> p3 = p1;

//     return 0;
// }


// #include<bits/stdc++.h>
// using namespace std;

// template<typename T>
// class Rational{
//     public:
//         Rational(const T &numberator = 0, const T &denominator = 1) : num(numberator), den(denominator) {};
//         const T &getNumerator() const { return num; }
//         const T &getDenominator() const { return den; }


//         //1.0
//         // friend
//         // const Rational<T> operator*(const Rational<T> &r1, const Rational<T> &r2)
//         // {
//         //     return Rational<T>(r1.getNumerator() * r2.getNumerator(), r1.getDenominator() * r2.getDenominator());
//         // }

//         //2.0
//         friend
//         const Rational<T>operator*(const Rational<T> &r1,const Rational<T>&r2){
//             return multiplay(r1, r2);
//         }
//     private:
//         T num;
//         T den;
// };

// // template<typename T>
// // const Rational<T> operator*(const Rational<T> &r1, const Rational<T> &r2)
// // {
// //     return Rational<T>(r1.getNumerator() * r2.getNumerator(), r1.getDenominator() * r2.getDenominator());
// // }

// template<typename T>
// const Rational<T> multiplay(const Rational<T> &r1, const Rational<T> &r2) {
//     return Rational<T>(r1.getNumerator() * r2.getNumerator(), r1.getDenominator() * r2.getDenominator());
// }

// class T{
//     public:
//     T(int x):t(x){}
//     private:
//         int t;
// };


// class test{
//     public:
//         test(){
//             t = new int[100000000000000L];
//         }
//     private:
//         int* t;
// };

// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************
//     // Rational<int> r1(1, 2);
//     // Rational<int> r2(3, 4);
//     // Rational<int> r3 = 2 * r1; // const Rational<T> operator*(const Rational<T> &r1)做不到
//     // // Rational<double>r4(1.5, 2.5);
//     // // Rational<double>r5(1.5, 2.5);
//     // // Rational<double> r6 = r4 * r3;
//     // T t = 10;
//     // Rational<int> r7 = 6;
//     // cout << r3.getNumerator() << "/" << r3.getDenominator() << endl;
//     // // cout << r6.getNumerator() << "/" << r6.getDenominator() << endl;
//     // cout << r7.getNumerator() << "/" << r7.getDenominator() << endl;


//     std::set_new_handler([]()noexcept{
//         cout << "out of memory" << endl;
//     });
//     test *t = new(std::nothrow) test;

//     // 在这个例子中，new int[100000000000000L] 会立即失败，并且会调用 new_handler。new_handler 输出 "out of memory"，然后返回，
//     // 但这并没有结束程序的执行。new 表达式在 new_handler 返回后仍然会尝试分配内存，因为 new 失败时不会自动返回 nullptr，
//     // 除非使用了 std::nothrow。但由于 new_handler 没有改变程序的控制流（它没有抛出异常或终止程序），
//     // 所以 new 表达式会再次尝试分配内存，导致 new_handler 再次被调用，形成一个无限循环。 return 0;
    
//     return 0;
// }

// #include <iostream>
// #include <new> // 包含全局set_new_handler和operator new

// class Widget
// {
// public:


//     // 声明静态成员变量，用于存储当前的new-handler
//     static std::new_handler currentHandler;

//     // 设置Widget的new-handler
//     static std::new_handler set_new_handler(std::new_handler p) throw()
//     {
//         std::new_handler oldHandler = currentHandler;
//         currentHandler = p;
//         return oldHandler;
//     }

//     // Widget的operator new
//     static void *operator new(std::size_t size) 
//     {
//         // 使用NewHandlerHolder来确保new-handler的正确恢复
//         NewHandlerHolder h(std::set_new_handler(currentHandler));
//         void *ptr = ::operator new(size);
//         if (!ptr)
//         {
//             // 如果内存分配失败，调用Widget的new-handler
//             if (currentHandler)
//             {
//                 currentHandler();
//             }
//             else
//             {
//                 throw std::bad_alloc();
//             }
//         }
//         return ptr;
//     }

//     //构造函数
//     Widget(){
//         t = new int[100000000000000L];
//     }

//     // 析构函数
//     ~Widget()
//     {
//         // 这里不需要特别处理，因为全局new-handler已经在operator new中被恢复
//     }

// private:
//     // 资源管理类，用于确保new-handler的正确恢复
//     int *t;
//     class NewHandlerHolder
//     {
//     public:
//         explicit NewHandlerHolder(std::new_handler nh) : handler(nh){}
//         ~NewHandlerHolder()
//         {
//             std::set_new_handler(handler);
//         }

//     private:
//         std::new_handler handler;
//         NewHandlerHolder(const NewHandlerHolder &); // 阻止拷贝
//         NewHandlerHolder &operator=(const NewHandlerHolder &);
//     };
// };

// // 初始化静态成员变量
// std::new_handler Widget::currentHandler = 0;

// void outOfMem(){
//     std::cout << "Out of memory!" << std::endl;
    
//     std::abort(); // 或者其他错误处理逻辑
//     //这里如果不调用abort/exit结束程序，程序会继续运行，但是会导致内存泄漏，因为new_handler没有被恢复，导致内存无法释放。
//     //同时，编译器会不同的尝试分配内存，导致无限循环
// }

// int main(){
//     // 设置全局new_handler为outOfMem函数
//     std::set_new_handler(outOfMem);

//     // 尝试创建Widget对象
//     Widget *w = new Widget;

//     // 清理
//     delete w;


//     return 0;
// }

// #include<bits/stdc++.h>
// using namespace std;
// class T{
//     public:
//         T(){
//             // throw std::runtime_error(__PRETTY_FUNCTION__);
//         }
//         static void *operator new(std::size_t size){
//             cout << __PRETTY_FUNCTION__ << "size:"<<size<<endl;
//             return ::operator new(size);
//         }
//         static void *operator new(std::size_t size,std::ostream&os){
//             auto ptr= ::operator new(size);
//             cout << __PRETTY_FUNCTION__ << "  "<<ptr<<endl;
//             return ptr;
//         }
//         static void operator delete(void *ptr){
//             cout << __PRETTY_FUNCTION__ << "  "<<ptr<<endl;
//             static_cast<T *>(ptr)->~T();
//             ::operator delete(ptr);
//         } 
//         static void operator delete(void*ptr,std::ostream&os)noexcept{
//             cout << __PRETTY_FUNCTION__ << "  "<<ptr<<endl;
//             static_cast<T *>(ptr)->~T();
//             // 不调用 ::operator delete(ptr)，因为内存不是由 ::operator new 分配的
//         } 


// };

// class P
// {
// public:
//     int t;
//     P(int x = 10):t(x){}
//     static void *operator new(std::size_t size)
//     {
//         cout << __PRETTY_FUNCTION__ << "size:" << size << endl;
//         return ::operator new(size);
//     }
//     static void *operator new(std::size_t size, void*placement)
//     {
//         cout << __PRETTY_FUNCTION__ << "  " << placement << endl;
//         if(placement==nullptr){
//             throw std::bad_alloc();
//         }
//         return placement;
//     }
//     static void operator delete(void *ptr)
//     {
//         cout << __PRETTY_FUNCTION__ << "  " << ptr << endl;
//         static_cast<P *>(ptr)->~P();
//         ::operator delete(ptr);
//     }
//     static void operator delete(void *ptr, void*placement)
//     {
//         cout << __PRETTY_FUNCTION__ << "  " << placement << endl;
//         static_cast<P *>(ptr)->~P();
//         // 不调用 ::operator delete(ptr)，因为内存不是由 ::operator new 分配的
//         // 我们这里可以选择free placement，或者不做任何事情
//         //那意味着我们选择当前对象指针管理placement的内存或者让调用者去管理
//         ::operator delete[](placement);
//     }
// };

// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************
//     //1.0
//     // auto *w = new(std::cout) T();
//     // cout << "w:"<<w<<endl;
//     // delete w;
   

//     //2.0
//     char *placement = new char[sizeof(P)];
//     cout << "placement:" << static_cast<void *>(placement) << endl;

//     auto *p = new(placement) P;
//     cout <<p->t<<endl;
//     cout << "p:" << p << endl;

//     P::operator delete(p, placement);
//     p = nullptr;
//     cout << "after delete p:" << p << endl;

//     cout <<p->t<<endl;

//     return 0;
// }



// #include<bits/stdc++.h>
// using namespace std;
// const int signatrue = 0x12345678;
// class MyClass{
//     public:
//         MyClass(){}
//         static void *operator new(size_t size){
//             cout << __PRETTY_FUNCTION__ << "size:"<<size<<endl;
//             size_t real_size = size + 2 * sizeof(int) + sizeof(size_t);
//             void *begin = malloc(real_size);
//             if (!begin)
//                 throw std::bad_alloc();
            
//             *(reinterpret_cast<size_t *>(begin)) = real_size;

//             *(reinterpret_cast<int*>(reinterpret_cast<char *>(begin) + sizeof(size_t))) = signatrue;
//             *(reinterpret_cast<int*>(reinterpret_cast<char *>(begin) + real_size - sizeof(int))) = signatrue;

//             return static_cast<void *>(reinterpret_cast<char *>(begin + sizeof(size_t) + sizeof(int)));
//         }

//         static void operator delete(void *p)noexcept{
//             char *ptr = static_cast<char *>(p - sizeof(size_t) - sizeof(int));
//             size_t real_size = *(reinterpret_cast<size_t *>(ptr));
//             int startSignature = *(reinterpret_cast<int *>(ptr + sizeof(size_t)));
//             int endSignature = *(reinterpret_cast<int *>(ptr +real_size - sizeof(int)));
//             if(startSignature != signatrue || endSignature != signatrue){
//                 cout << "signature error"<<endl;
//             }
//             else
//                 cout << "delete success"<<endl;

//             free(ptr);
//         }
// };

// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************

//     MyClass *p = new MyClass();
//     delete p;
//     return 0;
// }


// #include<bits/stdc++.h>
// using namespace std;

// template <int M>
// constexpr static int fib = fib<M-1>+fib<M-2>;
// template <>
// constexpr int fib<0> = 0;
// template <>
// constexpr int fib<1> = 1;
// int main()
// {
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************

//     //1.0
//     // int(*ptr)[100];

//     // ptr = new int[1][100];
//     // for(int i=0;i<100;i++){
//     //     ptr[0][i] = i;
//     // }
//     // for(int i=0;i<100;i++){
//     //     // cout<<ptr[0][i]<<" ";
//     //     cout << *(ptr[0]+i)<< " ";
//     // }
//     // delete[] ptr;

//     //2.0
//     // const char* p[100];
    
//     // for (int i = 0; i < 100;i++){
//     //     p[i] = new char[100];
//     //     strcpy(const_cast<char*>(p[i]), "hello world");
//     // }
//     // for(int i = 0; i < 100;i++){
//     //     // cout << *(p+i) << " ";
//     //     cout << p[i] << " ";
//     // }
//     // for(int i = 0; i < 100;i++){
//     //     // delete[] *(p+i);
//     //     delete[] p[i];
//     // }

//     //3.0
//     // typedef std::string str[4];//using alias name for array of string
//     // string *pp = new str;//new str is liked new std::string[4]
//     // for (int i = 0; i < 4;i++){
//     //     pp[i] = "hello world";
//     // }
//     // for(int i = 0; i < 4;i++){
//     //     cout << *(pp+i) << " ";
//     //     // cout << pp[i] << " ";
//     // }
//     // delete[] pp;

//     cout << (fib<30>) << endl;
// }


// #include<bits/stdc++.h>
// using namespace std;
// template<typename T>
// class A{
//     public:
//         int value = 0;
//         void f(){
//             static_cast<T*>(this)->implementation();
//         }

//         static void pp();
// };
// class B:public A<B>{
//     public:
//         void implementation(){
//             value = 10;
//         }
// };
// class C:public A<C>{
//     public:
//         void implementation(){
//             value = 20;
//         }
// };
// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************
    

//     return 0;
// }

// #include<bits/stdc++.h>
// using namespace std;

// class A{
//     public:
//         A(int x) : pp(x) {}

//         operator int()const{
//             return pp;
//         }

//         ~A(){
//             cout << "destructor" << endl;
//         }
//     private:
//         int pp;
// };

// class B{
//     public:
//         class proxysize{
//             public:
//                 proxysize(int _size):theSize(_size){}
//                 int size(){
//                     return this->theSize;
//                 }
//             private:
//                 int theSize;
//         };
//         B(proxysize size){}
//         ~B(){
//             cout << "destructor" << endl;
//         }
// };

// typedef A* Aptr;
// Aptr *ptr = new Aptr[10];

// Aptr ptrs[10];

// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************
//     // for (int i = 0; i < 10;i++){
//     //     // ptr[i] = new A(i);
//     //     // cout << *ptr[i] << endl;
//     //     ptrs[i] = new A(i);
//     //     cout << *ptrs[i] << endl;
//     // }
//     // for (int i = 0; i < 10;i++){
//     //     // delete ptr[i];
//     //     delete ptrs[i];
//     // }
//     B b(7);//right
//     // B b = 8;//error

//     return 0;
// }


// #include<bits/stdc++.h>
// using namespace std;

// class A{
//     public:
//     //前置式不需要临时对象，而后置式会构造临时对象，所以前置式的效率更高
//     //非必要不使用后置++
    
//     //前置++
//     A &operator++(){
//         (*this)+=1; //重载+=实现
//         return *this;
//     }
//     //后置++   
//     //后置返回对象而非引用的原因防止 A++++出现造成混淆，等价 A.operator++(0).operator++(0)|于内建类型不一致
//     //而返回const的原因的话，是如果单纯对象，第二次的++实行在第一次A++形成的临时对象上，实际对A只加1次，反直觉
//     const A operator++(int){
//         A temp = *this;
//         ++(*this); //借助前置++实现后置++
//         return temp;
//     }
//     //前置--
//     A &operator--(){
//         (*this)+=(-1);
//         return *this;
//     }
//     //后置--
//     const A operator--(int){
//         A temp = *this;
//         --(*this);
//         return temp;
//     }

//     A&operator+=(int x){
//         (this->k) += x;
//         return *this;
//     }
    

//     int getK()const{//必须是const，否则类似(a++).getK()会报错
//         return k;
//     }
//     private:
//         int k = 0;
// };

// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************
//     A a;
//     cout << a.getK() << endl;//返回0
//     ++a;
//     cout << a.getK() << endl;//返回1
//     a++;
//     cout << a.getK() << endl;//返回2
//     // a++ ++; //error
//     ++ ++a;
//     cout << a.getK() << endl;//返回4
//     cout << (++a).getK() << endl;//返回5
//     cout << (a++).getK() << endl;//返回5
//     cout << a.getK() << endl;//返回6,因为上一个调用了a++，所以a的值已经变成6了
//     return 0;
// }

// #include<bits/stdc++.h>
// using namespace std;
// // c++对于“真假式表达式”采用的是“骤死式”(短路)实现的，即如果左边的表达式为假，则不会计算右边的表达式（从左到右）。
// // if(p!=nullptr&&strlen(p)>10)不必担心strlen调用时p为nullptr，因为左边的表达式为假，右边的表达式不会被计算。
// // 假设重载operator&&与operator||，（函数调用的形式）那么就相当于a.operator&&(b)/operator||(a,b)
// // 那么就不存在“短路”，同时不能确定评估顺序（未明确）


// class A{
//     public:
//         void* operator new(size_t size,void *ptr){
//             cout << "operator new" << endl;
//             return ptr;
//         }
//         ~A(){
//             cout << "destructor" << endl;
//         }
// };
// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************
//     void *p = malloc(2*sizeof(A));
//     A *pr = new (p) A;
//     delete pr;

//     return 0;
// }

// #include<bits/stdc++.h>
// using namespace std;
// class T{
//     public:
//         T(){
//             cout << "constructor" << endl;
//             // throw std::runtime_error(__PRETTY_FUNCTION__);
//         }
//         static void *operator new(std::size_t size){
//             cout << __PRETTY_FUNCTION__ << "size:"<<size<<endl;
//             return ::operator new(size);
//         }
//         static void *operator new(std::size_t,void*placement){
//             cout << __PRETTY_FUNCTION__ <<" "<<placement<<endl;
//             return placement;
//         }
//         static void operator delete(void *ptr){
//             cout << __PRETTY_FUNCTION__ << "  "<<ptr<<endl;
//             static_cast<T *>(ptr)->~T();
//             ::operator delete(ptr);
//         }
//         static void operator delete(void*ptr,void*placement)noexcept{
//             cout << __PRETTY_FUNCTION__ << "  "<<placement<<endl;
//             static_cast<T *>(ptr)->~T();
//             ::free(placement);
//         }
//         ~T(){
//             cout << "destructor" << endl;
//         }

// };


// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************
//     // T *ptr = new T;
//     // void *p = ptr;
//     // delete ptr;//会调用T的析构函数，因为他知道指向的类型是T
//     // delete p;//不会调用T的析构函数，因为他不知道指向的类型是T

//     void *p = malloc(sizeof(T) * 100);
//     T *ptr = new(p) T[10];
//     //千万不可delete[] ptr，因为ptr指向的内存并不是new分配的，强行使用delete[]会导致未定义行为
//     //比如此处使用delete[]会导致无限调用构造函数！！！
//     free(p)//==free(ptr)也能正确的调用析构函数;
//     return 0;
// }


// #include<bits/stdc++.h>
// using namespace std;

// class mystring{
//     public:
//         mystring(const char*s){
//             this->str = new char[strlen(s) + 1];
//             strcpy(this->str, s);
//         }
//         mystring(std::string s){
//             this->str = new char[s.size() + 1];
//             strcpy(this->str, s.c_str());
//         }
//         mystring(const mystring&s){
//             this->str = new char[strlen(s.str) + 1];
//             strcpy(this->str, s.str);
//         }
//         ~mystring(){
//             delete[] this->str;
//         }
//         char *getStr()const{
//             return this->str;
//         }

//         private : char *str;
// };
// ostream &operator<<(ostream &os,const mystring&s){
//     os << s.getStr();
//     return os;
// }

// void func(mystring s){
//     cout << s << endl;
// }

// void funcc(char*s){
//     cout << "char*" << endl;
// }
// void funcc(int c)
// {
//     cout << "int" << endl;
// }
// constexpr long long fibonacci(const int n)
// {
//     return n == 1 || n == 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);
// }

// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************
//     // c++不允许直接将 void * 隐式转换到其他类型
//     // funcc(NULL);//歧义，c++中NULL被实现为0，所以会调用int版本.本版本中报错
//     // nullptr 的类型为 nullptr_t，能够隐式的转换为任何指针或成员指针的类型，也能和他们进行相等或者不等的比较。
//     // cout << (NULL == nullptr) << endl;//输出1
//     // cout << NULL << endl;//输出0
//     // cout << nullptr << endl;//输出nullptr
//     // cout << std::is_same<decltype(nullptr),decltype(NULL)>::value << endl;//输出0
//     // cout << (nullptr == 0) << endl;//1
//     // cout << (NULL == 0) << endl;//1
//     cout << fibonacci(10) << endl;
//     return 0;
// }


#include<bits/stdc++.h>
#include<vector>
using namespace std;
class ints{
    public:
        int a;
        ints(int x) : a(x) {}

        const ints&operator+=(const ints&b){
            a += b.a;
            return *this;
        }
        ~ints(){
            cout << "destructor" << endl;
        }
        void print()const{
            cout << a << endl;
        }
        const ints operator+(const ints &a) const
        {
            return ints(*this) += a;
        }
        friend std::ostream &operator<<(ostream &os, const ints&a);
};
std::ostream &operator<<(ostream &os, const ints&a)
{
    os << a.a;
    return os;
}




template<class T>
class smart_ptr{
    public:
        explicit smart_ptr(T*p = nullptr):pointer(p){}

        T&operator*(){
            return *pointer;
        }
        T*operator->()const{
            if(this->pointer==nullptr)
                throw std::runtime_error("nullptr");
            return pointer;
        }
        ~smart_ptr(){
            if(pointer){
                delete pointer;
                pointer = nullptr;
            }
        }
        // const smart_ptr &operator=(smart_ptr&&other){
        //     if(this!=&other){
        //         if(this->pointer!=nullptr)delete this->pointer;
        //     }
        //     this->pointer = other.pointer;
        //     other.pointer = nullptr;
        //     return *this;
        // }
        bool operator!(){
            return pointer == nullptr;
        }
        T*get(){
            return pointer;
        }

        template<class newType>
        operator smart_ptr<newType>(){
            return smart_ptr<newType>(static_cast<newType*>(pointer));
        }
    private:
        T *pointer;
        const smart_ptr &operator=(const smart_ptr &) = delete;
};
class A{
    public:
        virtual void print(){
            cout << "A" << endl;
        }
    virtual ~A(){
        std::cout << "~A" << std::endl;
    }
};
class B:public A{
    public:
        void print(){
            cout << "B" << endl;
        }

    ~B(){
        std::cout << "~B" << ::std::endl;
    }
};

void func(const smart_ptr<A>&p){
    p->print();
}
int main(){
    //***************************************
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    //***************************************
    smart_ptr<A> ptr1(new A);
    smart_ptr<B> ptr2(new B);
    func(ptr1);
    // func(ptr2);
    return 0;
}
