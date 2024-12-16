#include "Set.h"

template <class T>
bool Set<T>::member(const T &x)
{
    return std::find(rep.begin(), rep.end(), x) != rep.end();
}
template <class T>
void Set<T>::insert(const T &x)
{
    if (!member(x))
        rep.push_back(x);
}
template <class T>
void Set<T>::remove(const T &x)
{
    typename std::list<T>::iterator it = std::find(rep.begin(), rep.end(), x);
    if (it != rep.end())
        rep.erase(it);
}
template <class T>
std::size_t Set<T>::size() const
{
    return rep.size();
}
template <class T>
bool Set<T>::empty() const
{
    return rep.empty();
}
template <class T>
void Set<T>::clear()
{
    rep.clear();
}
