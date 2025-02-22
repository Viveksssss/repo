// #include <iostream>
// using namespace std;

// template<typename T>
// struct ArgType{
//     using type = const T&;
// };

// template<>
// struct ArgType<int>{
//     using type = int;
// };

// template<typename T>
// struct ArgType<T *>{
//     using type = T *;
// };

// class myclass{
// };

// template<typename T>
// void show(typename ArgType<T>::type t){
//     cout << t << endl;
// }
// int main()
// {
//     show<int>(10);
//     int a = 10;
//     myclass p = myclass();
//     myclass *q = &p;
//     show<myclass*>(q);
//     show<int>(20);

//     return 0;
// }


// #include<bits/stdc++.h>


// //Substitution Failure Is Not An Error(SFINAE)

// //假设要匹配的T很大,第一个模板函数匹配失败,不会报错,而是会接着尝试下一个模板函数,直到找到匹配的模板函数 \
// 如果都没有匹配的模板函数,编译器会报错.
// template<bool cond,typename T>
// struct enable_if{};

// template<typename T>
// struct enable_if<true,T>{
//     using type = T;
// };

// template <bool cond, typename T>
// using enable_if_t = typename enable_if<cond, T>::type;

// template<typename T>
// void f(enable_if_t<sizeof(T) <= sizeof(T*), T> t){
//     std::cout << "small";
//     std::cout << std::is_integral<T>::value << std::endl;
// }

// template<typename T>
// void f( enable_if_t<(sizeof(T) > sizeof(T*)), T>const &t){
//     std::cout << "big";
//     std::cout << std::is_integral<T>::value << std::endl;
// }



// struct myclass{
//     int a;
//     double s;
//     double ss;
//     double sss;
// };

// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************

//     int a;
//     double b;
//     char c;
//     f<int>(a);
//     f<double>(b);
//     f<char>(c);

//     f<myclass>(myclass());
        

//     return 0;
// }



// #include<bits/stdc++.h>
// using namespace std;
// //变参的三种展开 \
 1.直接展开 \
 2.嵌套展开 \
 3.折叠展开 


// template<typename T>
// T Sum(const T&t){
//     return t;
// }

// template<typename T,typename... Args>
// T Sum(const T&t,Args...args){
//     return abs(t) + Sum<Args...>(args...);
// }

// template <typename... Args>
// auto sum(Args...args){
//     return (args + ...);
// }

// template<typename...Args>
// void print(const Args&...args){
//     // (std::cout << (... << (args*2))) << std::endl;
//     // ((std::cout << (args * 2) << " "), ...) << std::endl;
//     // ((std::cout << (args+5) <<" "),...) << endl;
//     (std::cout << ... << (args * 10)) << endl;
// }

// template<typename...Args>
// auto dot(Args...args){
//     return  (args *...);
// }

// template<int...Args>
// auto sum(){
//     return (Args + ...);
// }

// template<int...Args>
// auto ssum(){
//     return (1 + ... + Args);
// }
// template<typename T>
// void hhh(T &&p){
//     if(std::is_same_v<T,int>){
//         std::cout << "int" << std::endl;
//     }else if(is_same_v<T,int&>){
//         std::cout << "int&" << std::endl;
//     }
// }
// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************

//     std::cout << sum<1, 2, 3, 4, 5>() << endl;
//     hhh(1);
//     int i = 10;
//     hhh(i);
//     return 0;
// }


// #include<bits/stdc++.h>
// using namespace std;

// void process(int&i){
//     std::cout << "int&" << endl;
// }
// void process(int&&i){
//     std::cout << "int&&" << endl;
// }

// template<typename T>
// void test(T&&v){
//     process(std::forward<T>(v));
// }


// // 关键分析步骤：
// // 模板参数推导：test(10)中的10是右值，T被推导为int，函数参数v的类型为int&&（右值引用）。

// // 变量v的值类别：虽然v的类型是右值引用，但作为具名变量，它本身是一个左值（所有具名变量都是左值）。

// // 函数重载匹配：调用process(v)时，传递的是左值v，因此匹配void process(int&)版本。


// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************

//     int a = 100;
//     test(10);
//     test(a);
//     process(10);
//     process(a);
//     return 0;
// }


// #include<bits/stdc++.h>

// //限定模板参数必须是整形
// template<typename T>
// typename std::enable_if<std::is_integral<T>::value,T>::type
// add (T a, T b)
// {
//     return a + b;
// }


// //限定模板参数必须实现特定接口
// struct test1{
//     int method(){
//         std::cout << "ok " <<std::endl;
//         return 1;
//     }
// };
// struct test2{
//     void method(){
//         std::cout << "yes" << std::endl;
//     }
// };




// template<typename T1,typename T2> 
// struct is_same{
//     constexpr static bool value = false;
// };

// template<typename T>
// struct is_same<T,T>{
//     constexpr static bool value = true;
// };

// template<typename T1,typename T2>
// constexpr bool is_same_v = is_same<T1,T2>::value;




// // template<typename T>
// // std::enable_if_t<is_same_v<decltype(T{}.method()),void> ,void>
// // f(const T&t){
// //     std::cout << "yes" << std::endl;
// // }


// //类型萃取
// template<typename T>
// struct RemoveRef{
//     using type = T;
// };
// template<typename T>
// struct RemoveRef<T&>{
//     using type = T;
// };
// template<typename T>
// struct RemoveRef<T&&>{
//     using type = T;
// };
// template<typename T>
// using RemoveRef_t = typename RemoveRef<T>::type;


// template<typename T>
// struct ToInt{
//     using type = int;
// };
// // template<typename T>
// // std::enable_if_t<is_same_v<typename ToInt<decltype(std::declval<T>().method())>::type,int> ,void>
// // f(const T&t){
// //     std::cout << "yes 2" << std::endl;
// // }


// template<typename T>
// std::enable_if_t<std::is_void_v<std::void_t<decltype(std::declval<RemoveRef_t<T> >().method())>>,void>
// f(const T&t){
//     std::cout << "yes 2" << std::endl;
// }

// template<typename...Args>
// void print(const Args&...args){
//     ((std::cout << (args*10)),...)<<std::endl;
// }

// // template<typename...Args>
// // void print(const Args&...args){
// //     (std::cout << ... << (args * 10)) << std::endl;
// // }



// int
// main()
// {
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************

//     print(1,2,3,4,5);
//     return 0;
// }


// #include<bits/stdc++.h>
// using namespace std;

// void*Alloc(size_t size){
//     char buf[size];
//     void*p = buf;
//     return p;
// }


// template<typename T,typename...Args>
// T*Create(Args&&...args){
//     T*buf = static_cast<T*>(Alloc(sizeof(T)));
//     return new (buf) T(std::forward<Args>(args)...);
// }

// class Circle{
//     public:
//         Circle(double r){}
// };
// class Test{
//     public:

//         // Test(Circle C){}
//         // Test(Circle &C){}
//         Test(Circle&&C){}
// };


// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************

//     Circle c(10);
//     // Test*t = Create<Test,Circle&>(c);
//     // Circle*p = Create<Circle>(10);

//     Test*p = Create<Test,Circle&&>(std::move(c));
//     // Test*p = Create<Test,Circle&&>(10);


//     int a = 10;
//     auto p1 = std::forward<int&&>(10);
//     auto p2 = std::forward<int&>(a);

//     std::cout << std::is_same_v<decltype(p1),int> << std::endl;
//     std::cout << std::is_same_v<decltype(p1),int&> << std::endl;
//     std::cout << std::is_same_v<decltype(p1),int&&> << std::endl;
//     std::cout << std::is_same_v<decltype(p2),int> << std::endl;
//     std::cout << std::is_same_v<decltype(p2),int&> << std::endl;
//     std::cout << std::is_same_v<decltype(p2),int&&> << std::endl;

//     std::string s = "asdsadasdasdxfdsfdsfdasf";
//     auto it = std::find(s.begin(),s.end(),'x');
//     std:: cout << s.end() - it << std::endl;
//     return 0;
// }


// #include<bits/stdc++.h>
// using namespace std;

// template<typename T>
// constexpr bool smalltype = sizeof(T) <= sizeof(void*);
// struct Test{
//     int arr[100];
// };


// template<typename T>
// requires smalltype<T> && std::is_trivial_v<T>
// void f(T&&t){
//     std::cout << "yes" << endl;
// }


// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************
//     Test t;
//     f(2);

//     return 0;
// }


#include<bits/stdc++.h>
#include<climits>
#include<cstdint>
#include<random>
#include<ctime>
#include<execution>
#include<type_traits>
using namespace std;


/**
 * @brief 
 * 
 * @param a 
 * @return unsigned long long int 
 */
unsigned long long int func(int a){
    return a>1?a*func(a-1):1;
}



/**
 * @brief 
 * 
 * @param i 
 * @return decltype(auto) 
 */
decltype(auto) func2(int i){
    return (i);
}


template<typename T>
void func3(T t){
    if(std::is_integral_v<T>){
        std::cout << "int" << std::endl;
    }else{
        std::cout << "not int" << std::endl;
    }
}

double func4(const long num){
    double step = 1.0/num;
    double sum = 0.0;
#pragma omp parallel for reduction(+:sum)
    for(int i = 0;i<num;i++){
        double x = (i+0.5)*step;
        sum += 4.0/(1.0+x*x);
    }
    return step*sum;
}



int main(){
    //***************************************
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    //***************************************
    int a = 10;
    std::cout << (std::is_same_v<int&&,decltype((func2(10)))>) << std::endl;
    std::cout << (std::is_rvalue_reference_v<decltype((func2(10)))>) << std::endl;
}

