// #include "String.h"

// ostream& operator<<(ostream&os,String&s){
//     os << s.str; 
//     return os;
// }
// istream& operator>>(istream&cin,String&s){
//     if(s.str){
//         delete[]s.str;
//         s.str = nullptr;
//         s.str_size = 0;
//     }
//     char buff[1024];
//     cin >> buff;
//     s.str = new char[strlen(buff)+1];
//     strcpy(s.str,buff);
//     s.str_size = strlen(buff);
//     return cin;
// }

// String& String::operator=(const String&s){
//     if(this->str){
//         delete[]this->str;
//         this->str = nullptr;
//     }
//     this->str = new char[strlen(s.str)+1];
//     strcpy(this->str,s.str);
//     this->str_size = strlen(s.str);

// }
// String& String::operator=(const char*s){
//     if(this->str){
//         delete[]this->str;
//         this->str = nullptr;
//     }
//     this->str = new char[strlen(s)+1];
//     strcpy(this->str,s);
//     this->str_size = strlen(s);
// }

// char& String::operator[](int index){
//     return this->str[index];
// }

// String String::operator+(String&s){
//     int newsize = strlen(this->str)+strlen(s.str);
//     char *temp = new char[newsize];
//     strcat(temp,this->str);
//     strcat(temp,s.str);
//     String newString = temp;
//     delete[]temp;  //勿忘
//     return newString;
// }
// String String::operator+(const char*s){
//     int newsize = strlen(this->str)+strlen(s);
//     char *temp = new char[newsize];
//     strcat(temp,this->str);
//     strcat(temp,s);
//     String  newString = temp;
//     delete[]temp;   //勿忘
//     return newString;
// }

// bool String::operator==(const String&s){
//     if(strcmp(s.str,this->str)==0)
//         return true;
//     return false;
// }
// bool String::operator==(const char*s){
//     if(strcmp(this->str,s)==0)
//         return true;
//     return false;
// }


#include "String.h"

String::String() : str(nullptr), str_size(0) {}

String::String(const char* str) {
    str_size = strlen(str);
    this->str = new char[strlen(str) + 1];
    strcpy(this->str, str);
}

String::String(const String& strs) : str_size(0), str(nullptr) {
    str_size = strlen(strs.str);
    this->str = new char[strlen(strs.str) + 1];
    strcpy(this->str, strs.str);
}

String::~String() {
    delete[] this->str;
}

std::ostream& operator<<(std::ostream& os, const String& s) {
    os << s.str;
    return os;
}

std::istream& operator>>(std::istream& is, String& s) {
    if (s.str) {
        delete[] s.str;
        s.str = nullptr;
        s.str_size = 0;
    }
    char buff[1024];
    is >> buff;
    s.str = new char[strlen(buff) + 1];
    strcpy(s.str, buff);
    s.str_size = strlen(buff);
    return is;
}

String& String::operator=(const String& s) {
    if (this != &s) {
        delete[] this->str;
        this->str = new char[strlen(s.str) + 1];
        strcpy(this->str, s.str);
        this->str_size = s.str_size;
    }
    return *this;
}

String& String::operator=(const char* s) {
    if (this->str != s) {
        delete[] this->str;
        this->str = new char[strlen(s) + 1];
        strcpy(this->str, s);
        this->str_size = strlen(s);
    }
    return *this;
}

char& String::operator[](int index) {
    return this->str[index];
}

String String::operator+(const String& s) {
    int newsize = strlen(this->str) + strlen(s.str);
    char* temp = new char[newsize + 1];
    strcpy(temp, this->str);
    strcat(temp, s.str);
    String newString(temp);
    delete[] temp;
    return newString;
}

String String::operator+(const char* s) {
    int newsize = strlen(this->str) + strlen(s);
    char* temp = new char[newsize + 1];
    strcpy(temp, this->str);
    strcat(temp, s);
    String newString(temp);
    delete[] temp;
    return newString;
}

bool String::operator==(const String& s) {
    return strcmp(this->str, s.str) == 0;
}

bool String::operator==(const char* s) {
    return strcmp(this->str, s) == 0;
}