// #pragma once
// #include<bits/stdc++.h>
// using namespace std;

// class String{
//     private:
//         char*str;
//         int str_size;
//     public:
//         String():str(nullptr),str_size(0){}
//         String(const char*str){
//             str_size = strlen(str);
//             this->str = new char[strlen(str)+1];
//             strcpy(this->str,str);
//         }
//         String(const String&strs):str_size(0),str(nullptr){
//             str_size = strlen(strs.str);
//             this ->str = new char[strlen(strs.str)+1];
//             strcpy(this->str,strs.str);
//         }
//         ~String(){
//             if(this->str!=nullptr){
//                 delete[]this->str;
//             }
//         }
//         // ostream& operator<<(ostream&os);
//         friend ostream& operator<<(ostream&os,String&s);
//         friend istream& operator>>(istream&cin,String&s);
//         String& operator=(const String&s);
//         String& operator=(const char*s);
//         char&operator[](int index);
//         //class String can not be reload with return value type reference
//         //becase the variable newString is a temporary object.
//         String operator+(String&s);
//         String operator+(const char*s);
//         bool operator==(const String&s);
//         bool operator==(const char*s);
     
        
// };


#pragma once

#include <iostream>
#include <cstring>

class String {
private:
    char* str;
    int str_size;

public:
    String();
    String(const char* str);
    String(const String& strs);
    ~String();

    friend std::ostream& operator<<(std::ostream& os, const String& s);
    friend std::istream& operator>>(std::istream& is, String& s);

    String& operator=(const String& s);
    String& operator=(const char* s);
    char& operator[](int index);

    String operator+(const String& s);
    String operator+(const char* s);

    bool operator==(const String& s);
    bool operator==(const char* s);
};