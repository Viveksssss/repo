#ifndef SET_H
#define SET_H

#include <list>
#include <algorithm>
template<class T>
class Set{
    private:
        std::list<T> rep;
    public:
        bool member(const T &x);
        void insert(const T &x);
        void remove(const T &x);
        std::size_t size() const;
        bool empty() const;
        void clear();
};

#endif //SET_H