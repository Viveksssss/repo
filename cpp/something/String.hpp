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

class String
{
private:
    char *str;
    int str_size;

public:
    String();
    String(const char *str);
    String(const String &strs);
    ~String();

    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

    String &operator=(const String &s);
    String &operator=(const char *s);
    char &operator[](int index);

    String operator+(const String &s);
    String operator+(const char *s);

    bool operator==(const String &s);
    bool operator==(const char *s);
};

String::String() : str(nullptr), str_size(0) {}

String::String(const char *str)
{
    str_size = strlen(str);
    this->str = new char[strlen(str) + 1];
    strcpy(this->str, str);
}

String::String(const String &strs) : str_size(0), str(nullptr)
{
    str_size = strlen(strs.str);
    this->str = new char[strlen(strs.str) + 1];
    strcpy(this->str, strs.str);
}

String::~String()
{
    delete[] this->str;
}

std::ostream &operator<<(std::ostream &os, const String &s)
{
    os << s.str;
    return os;
}

std::istream &operator>>(std::istream &is, String &s)
{
    if (s.str)
    {
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

String &String::operator=(const String &s)
{
    if (this != &s)
    {
        delete[] this->str;
        this->str = new char[strlen(s.str) + 1];
        strcpy(this->str, s.str);
        this->str_size = s.str_size;
    }
    return *this;
}

String &String::operator=(const char *s)
{
    if (this->str != s)
    {
        delete[] this->str;
        this->str = new char[strlen(s) + 1];
        strcpy(this->str, s);
        this->str_size = strlen(s);
    }
    return *this;
}

char &String::operator[](int index)
{
    return this->str[index];
}

String String::operator+(const String &s)
{
    int newsize = strlen(this->str) + strlen(s.str);
    char *temp = new char[newsize + 1];
    strcpy(temp, this->str);
    strcat(temp, s.str);
    String newString(temp);
    delete[] temp;
    return newString;
}

String String::operator+(const char *s)
{
    int newsize = strlen(this->str) + strlen(s);
    char *temp = new char[newsize + 1];
    strcpy(temp, this->str);
    strcat(temp, s);
    String newString(temp);
    delete[] temp;
    return newString;
}

bool String::operator==(const String &s)
{
    return strcmp(this->str, s.str) == 0;
}

bool String::operator==(const char *s)
{
    return strcmp(this->str, s) == 0;
}