#ifndef PERSONIMPL_H
#define PERSONIMPL_H

#include<string>
#include "Person.h"
class PersonImpl{
    public:
        friend class Person;
        PersonImpl(int age_,std::string name_,int address_):age(age_),name(name_),address(address_){};
    private:
        int age;
        std::string name;
        int address;
};

#endif