#include <iostream>
#include <type_list.hpp>


template <class T>
using constify_t = const T;

template <class T>
struct sizefunc
{
    static const std::size_t value = sizeof(T);
};

using namespace metamusil::t_list;

typedef type_list<int, char, double> mylist;

template <class T>
void p(T)
{
    puts(__PRETTY_FUNCTION__);
}

int
main()
{
    p(type_for_each_t<mylist, constify_t>());
    p(value_for_each<mylist, sizefunc>::type());
    p(type_at_index_t<mylist, 0>());
    p(type_at_index_t<mylist, 1>());
    p(type_at_index_t<mylist, 2>());


    std::cout << size<mylist>::value << '\n';

    for(auto i : value_for_each<mylist, sizefunc>::value)
    {
        std::cout << i << '\n';
    }
}
