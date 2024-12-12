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

// 单例模式
//  #include<bits/stdc++.h>
//  using namespace std;

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

// 单例模式-打印机案例
//  #include<bits/stdc++.h>
//  using namespace std;

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

// 当包含含有类模板的文件的时候，我们通常不会将.h和.cpp文件分开，而是将所有的类模板都放在一个文件中，这样可以减少编译时间。
// 同时,后缀名约定为.hpp

// 友元函数（含模板）的类外实现：复杂
// 首先类内定义，同时函数名后要加<>,表示是模板函数
// 然后在类外实现，加上模板参数正常编写
// 但是仍然编译不通过，原因是，我们在类外实现时，需要实例化模板，但是实例化模板需要知道模板参数，而模板参数在类外无法获得，所以编译器无法实例化模板。
// 解决方法：
// 首先在类外全局声明友元函数
// 同时把参数涉及到的类也声明出来
//  #include"String.cpp"
//  #include<bits/stdc++.h>
//  using namespace std;

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

// #include<bits/stdc++.h>
// using namespace std;

// //     int pow_mod(int x,int y,int mod){
// //         int res = 1;
// //         while(y){
// //             if(y&1)
// //                 res = res*x%mod;
// //             x = x*x%mod;
// //             y>>=1;
// //         }
// //         return res;
// //     }

// //     std::vector<int> getGoodIndices(std::vector<std::vector<int>>& variables, int target) {
// //         vector<int>vec;
// //         for(int i = 0 ; i < variables.size();i++){
// //             auto &v = variables[i];
// //             if(pow_mod(pow_mod(v[0],v[1],10),v[2],v[3])==target)
// //                 vec.push_back(i);
// //         }
// //         return vec;
// //     }

//     int pow_mod(int x,int y,int mod){
//         if(!y)return 1;//边界问题，当到最后一个x一次方，1/2 = 0，return 1;
//         int t= pow_mod(x,y/2,mod);
//         return t*t*(y&1?x:1)%mod;
//     }
//     std::vector<int> getGoodIndices(std::vector<std::vector<int>>& variables, int target) {
//         vector<int>vec;
//         for(int i = 0 ; i < variables.size();i++){
//             auto &v = variables[i];
//             if(pow_mod(pow_mod(v[0],v[1],10),v[2],v[3])==target)
//                 vec.push_back(i);
//         }
//         return vec;
//     }

// int main(){
//     //***************************************
//     std::ios_base::sync_with_stdio(0);
//     std::cin.tie(0);
//     std::cout.tie(0);
//     //***************************************

//     return 0;
// }
// #include<iostream>
// #include<vector>
// #include<algorithm>
// #include<bits/stdc++.h>
// using namespace std;

// vector<vector<int>> tricalc(vector<int>vec){
// 	vector<vector<int>>ans;
// 	std::sort(vec.begin(),vec.end());
// 	for(int i = 0;i<vec.size()-1;i++){
// 		if(i>0&&vec[i]==vec[i-1])continue;
// 		int l = i+1,r = vec.size()-1;
// 		while(l<r){
// 			int sum = vec[i]+vec[l]+vec[r];
// 			if(sum == 0){
// 				ans.push_back({vec[i],vec[l],vec[r]});
// 				while(l<r&&vec[l]==vec[l+1])l++;
// 				while(l<r&&vec[r]==vec[r-1])r--;

// 				l++,r--;
// 			}
// 			else if(sum<0)l++;
// 			else r++;

// 		}
// 	}
// 	return ans;
// }

// int main(){
// 	// vector<int>vec = {-1,0,1,2,3,-3,-6,-2,-3,6};
// 	// vector<vector<int>>ans = tricalc(vec);
// 	// for(auto p:ans){
// 	// 	cout << "[";
//     //     for(int i = 0;i<p.size();i++){
//     //         cout << p[i] << (i==p.size()-1?"]":",");
//     //     }
//     //     cout << endl;
// 	// }

// 	return 0;
// }

// #include <chrono>
// #include <iostream>
// #include <stack>
// #include <queue>
// #include <unordered_map>
// using namespace std;

// struct TreeNode
// {
//      int val;
//      TreeNode *next;
//      TreeNode(int x) : val(x), next(nullptr) {}
// };

// void traverse(TreeNode* root){
//      if(root ==NULL)return ;
//      stack<TreeNode*>stack;
//      while(!stack.empty()||root!=nullptr){
//           while(root!=nullptr){
//                stack.push(root);
//                root = root ->left;
//           }
//           root = stack.top();
//           cout << root->val << " ";
//           stack.pop();

//           root = root->right;
//      }
// }

// priority_queue<int,std::vector<int>,std::greater<int>>pr;
//     void trace(TreeNode*root){
//         if(root){
//             pr.push(root->val);
//             trace(root->left);
//             trace(root->right);
//         }
//     }

//     int kthSmallest(TreeNode* root, int k) {
//         k--;
//         while(k--&&!pr.empty()){
//             pr.pop();
//         }
//         int s = pr.top();
//         return s;
//     }

// int main(int argc, const char *argv[])
// {
//     //  TreeNode* root = new TreeNode(1);
//     //  root->left = new TreeNode(2);
//     //  root->right = new TreeNode(3);
//     //  root->left->left = new TreeNode(4);
//     //  root->left->right = new TreeNode(5);
//     //  root->right->left = new TreeNode(6);
//     //  root->right->right = new TreeNode(7);
//     //  root->right->right->right = new TreeNode(8);

//     //  kthSmallest(root,3);
//     //  cout << pr.top() << endl;

// //     TreeNode*p ;
// //     TreeNode*q ;
// //     p = q = nullptr;
// //     p = new TreeNode(1);
// //     cout << q->val << endl;
//      int n = 3;
//      bool a = -1;
//         int sum = 1;
//         int k = n;
//         while(n!=0){
//             n/=2;
//             sum*=2;
//         }
//         cout << k;
//         cout << sum << endl;

//      return 0;
// }

// #include <bits/stdc++.h>
// using namespace std;
// const int N = 1e8;
// int test()
// {
//      int sum = 0;
//      for (int i = 1; i <= N; i++)
//      {
//           sum += i;
//      }
//      return sum;
// }

// int test2()
// {
//      int sum = 0;
//      int s1 = 0;
//      int s2 = 0;
//      int s3 = 0;
//      int s4 = 0;
//      for (int i = 1; i <= N; i += 4)
//      {
//           s1 += i;
//           s2 += (i + 1);
//           s3 += (i + 2);
//           s4 += (i + 3);
//      }
//      sum = s1 + s2 + s3 + s4;
//      return sum;
// }

// int main()
// {
//      //***************************************
//      std::ios_base::sync_with_stdio(0);
//      std::cin.tie(0);
//      std::cout.tie(0);
//      //***************************************
//      chrono::steady_clock::time_point start1 = chrono::steady_clock::now();
//      int sum1 = test();
//      chrono::steady_clock::time_point end1 = chrono::steady_clock::now();
//      chrono::steady_clock::time_point start2 = chrono::steady_clock::now();
//      int sum2 = test2();
//      chrono::steady_clock::time_point end2 = chrono::steady_clock::now();

//      chrono::duration<double> elapsed_seconds1 = end1 - start1;
//      chrono::duration<double> elapsed_seconds2 = end2 - start2;
//      cout << "spend time:" << elapsed_seconds1.count() << "s" << "--->" << sum1 << endl;
//      cout << "spend time:" << elapsed_seconds2.count() << "s" << "--->" << sum2 << endl;

//      return 0;
// }

#include <iostream>

struct Storage
{
     char a;
     int b;
     double c;
     long long d;
};

struct alignas(std::max_align_t) AlignasStorage
{
     char a;
     int b;
     double c;
     long long d;
     
};
#include <tuple>
#include <vector>
using namespace std;
int main()
{
     vector<int>vec = {1, 2, 2, 4, 5};
     int k = lower_bound(vec.begin(), vec.end(), 3) - vec.begin();
     cout << k << endl;
     
     

     return 0;
}