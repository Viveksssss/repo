#include "Person.h"

#include "PersonImpl.hpp"
int Person::getAddress() const {
    return impl->address;
}
void Person::setAddress(int address) {
    impl->address = address;
}
//
int Person::getAge() const {
    return impl->age;
}
void Person::setAge(int age) {
    impl->age = age;
}
//
const std::string &Person::getName() const {
    return impl->name;
}
void Person::setName(const std::string &name) {
    impl->name = name;
}
//
Person::Person(int age, const std::string &name, int address) : impl(std::make_unique<PersonImpl>(age, name, address)) {}
Person::~Person() = default;