#include <iostream>
using namespace std;

namespace hhh{
    class rational{
    public:
        void print() const{
            std::cout << this->upper << "/" << this->lower << std::endl;
        }

        rational(int num1 = 0, int num2 = 1) : upper(num1), lower(num2) {}

        int getupper() const{
            return this->upper;
        }
        int getlower() const // 这里的const必须要加
        // 我们可以想象，在下面的27行operator*函数中，参数tmp是一个const rational对象的引用，const说明不可以修改new对象
        // 但是我们调用了getupper()和getlower()函数，调用成员函数有改变参数的可能，编译器并不知道会不会真的改变
        // 为了避免改变，对不确定的函数都会报错
        // 我们为了让编译器知道我们调用的函数不会修改参数，因此在getupper函数后加上const关键字，告诉编译器不会修改参数内容
        // 这样编译器就不会报错了
        {
            return this->lower;
        }

        void swap(rational &a, rational &b){
            return;
        }

    private:
        int upper;
        int lower;
    };

    const rational operator*(const rational &tmp1, const rational &tmp2){
        return rational(tmp1.getupper() * tmp2.getupper(), tmp1.getlower() * tmp2.getlower());
    }
}
void swap(hhh::rational &a, hhh::rational &b) noexcept{
    a.swap(b);
}

int main(){
    hhh::rational a(2, 3);
    hhh::rational p = hhh::rational(4, 5) * a;
    hhh::rational q = a * 2;

    using std::swap;
    swap(p, q);

    p.print();
    q.print();

    return 0;
}
