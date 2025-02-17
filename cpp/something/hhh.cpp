#include <bits/stdc++.h>

#include <stdarg.h>
using namespace std;

void Printf(const char*format,...){
    va_list args;
    va_start(args,format);

    while(*format){
        if(*format == '%'){
            format++;
            if(*format == 'd'){
                int value = va_arg(args,int);
                cout << value;
            }else if(*format == 's'){
                char*s = va_arg(args,char*);
                cout << s;
            }
        }else{
            putchar(*format);
        }

        format++;
    }
}
int main(){
    Printf("hello my %s,are you %d ?\n\n\n","pettor",25);
}
