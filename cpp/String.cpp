#include<bits/stdc++.h>
using namespace std;
class String{
    private:
        char*str;
        int str_size;
    public:
        String():str(nullptr),str_size(0){}
        String(const char*str){
            str_size = strlen(str);
            this->str = new char[strlen(str)+1];
            strcpy(this->str,str);
        }
        String(const String&strs):str_size(0),str(nullptr){
            str_size = strlen(strs.str);
            this ->str = new char[strlen(strs.str)+1];
            strcpy(this->str,strs.str);
        }
        ~String(){
            if(this->str!=nullptr){
                delete[]this->str;
            }
        }
        // ostream& operator<<(ostream&os);
        friend ostream& operator<<(ostream&os,String&s);
        friend istream& operator>>(istream&cin,String&s);
        String& operator=(const String&s);
        String& operator=(const char*s);
        char&operator[](int index);
        //class String can not be reload with return value type reference
        //becase the variable newString is a temporary object.
        String operator+(String&s);
        String operator+(const char*s);
        bool operator==(const String&s);
        bool operator==(const char*s);
     
        
};

ostream& operator<<(ostream&os,String&s){
    os << s.str; 
    return os;
}
istream& operator>>(istream&cin,String&s){
    if(s.str){
        delete[]s.str;
        s.str = nullptr;
        s.str_size = 0;
    }
    char buff[1024];
    cin >> buff;
    s.str = new char[strlen(buff)+1];
    strcpy(s.str,buff);
    s.str_size = strlen(buff);
    return cin;
}

String& String::operator=(const String&s){
    if(this->str){
        delete[]this->str;
        this->str = nullptr;
    }
    this->str = new char[strlen(s.str)+1];
    strcpy(this->str,s.str);
    this->str_size = strlen(s.str);

}
String& String::operator=(const char*s){
    if(this->str){
        delete[]this->str;
        this->str = nullptr;
    }
    this->str = new char[strlen(s)+1];
    strcpy(this->str,s);
    this->str_size = strlen(s);
}

char& String::operator[](int index){
    return this->str[index];
}

String String::operator+(String&s){
    int newsize = strlen(this->str)+strlen(s.str);
    char *temp = new char[newsize];
    strcat(temp,this->str);
    strcat(temp,s.str);
    String newString = temp;
    delete[]temp;  //勿忘
    return newString;
}
String String::operator+(const char*s){
    int newsize = strlen(this->str)+strlen(s);
    char *temp = new char[newsize];
    strcat(temp,this->str);
    strcat(temp,s);
    String  newString = temp;
    delete[]temp;   //勿忘
    return newString;
}

bool String::operator==(const String&s){
    if(strcmp(s.str,this->str)==0)
        return true;
    return false;
}
bool String::operator==(const char*s){
    if(strcmp(this->str,s)==0)
        return true;
    return false;
}



int main(){
    //***************************************
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    //***************************************
    String s1("hello");
    String s2("world");
    std::cout<<s1<<"\n";
    std::cout<<s2<<"\n";
    std::cout<<(s1==s2)<<"\n";
    std::cout<<(s1=="hello")<<"\n";

    return 0;
}