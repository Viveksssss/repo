#include "Set.cpp"
#include <iostream>

using namespace std;
int main(){
    Set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    s.insert(6);
    s.insert(7);
    s.insert(8);
    s.insert(9);
    s.insert(10);

    for (int i = 0; i < 11;i++){
        std::cout << i << ":  " << s.member(i) << std::endl;
    }

    return 0;
}