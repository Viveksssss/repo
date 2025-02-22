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



#include<thread>
#include<iostream>
#include<array>
#include<vector>


/**
 * @brief 
 * 
 * @tparam Iter 
 * @tparam Op 
 * @tparam BOp 
 * @tparam Result 
 * @param first 
 * @param last 
 * @param transform 
 * @param reduce 
 * @param res 
 */
template<typename Iter,typename Op,typename BOp,typename Result>
void transform_reduce(Iter first,Iter last,Op transform,BOp reduce,Result&res){
    for(auto it = first;it!=last;it++){
        res = reduce(res,transform(*it));
    }
}



int main(){
    const int N = 10000;
    std::vector<double>numbers;
    numbers.reserve(N);
    for(int i = 0;i<N;i++){
        numbers.push_back((double)i/N);
    }

    auto transform = [](double x){
        return x*x;
    };
    auto reduce = [](double a,double b){
        return a+b;
    };

    const int N_Thread = 8;
    std::vector<std::thread>threads;
    std::array<double,N_Thread>subResult{0};

    for(int i = 0;i<N_Thread;i++){
        auto low = numbers.begin()+i*numbers.size()/N_Thread;

        auto high = numbers.begin()+(i+1)*numbers.size()/N_Thread;

        threads.push_back(
            std::thread(
                transform_reduce<std::vector<double>::iterator,
                decltype(transform),
                decltype(reduce),
                double>,low,high,transform,reduce,std::ref(subResult[i])
            )           
        );
    }
    double result = 0;
    for (int j = 0; j < N_Thread; j++){
        threads[j].join();
        result = reduce(result, subResult[j]);
    }
    std::cout << "Result: " << result << std::endl;
    return 0;
}