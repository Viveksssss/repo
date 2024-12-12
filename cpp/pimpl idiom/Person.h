#ifndef PIMPL_PERSON_H_
#define PIMPL_PERSON_H_

#include<string>
#include<memory>
class Person{
    public:
        Person(int age, const std::string &name, int address);
        ~Person();

        int getAge() const;
        void setAge(int age);

        const std::string &getName() const;
        void setName(const std::string &name);

        int getAddress() const;
        void setAddress(int address);

    private:
        class PersonImpl;
        std::unique_ptr<PersonImpl> impl;
};


#endif