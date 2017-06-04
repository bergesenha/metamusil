#pragma once


namespace metamusil
{
namespace t_list
{
template <class...>
struct type_list
{
};


////////////////////////////////////////////////////////////////////////////////
// get first type of a type_list
template <class TypeList>
struct head;

template <class First, class... Rest>
struct head<type_list<First, Rest...>>
{
    typedef First type;
};

template <class TypeList>
using head_t = typename head<TypeList>::type;


////////////////////////////////////////////////////////////////////////////////
// get tail of a type_list as another type_list
template <class TypeList>
struct tail;

template <class First, class... Rest>
struct tail<type_list<First, Rest...>>
{
    typedef type_list<Rest...> type;
};

template <class TypeList>
using tail_t = typename tail<TypeList>::type;


////////////////////////////////////////////////////////////////////////////////
// prepend a type to front of type_list
template <class TypeList, class T>
struct prepend;

template <class... Types, class T>
struct prepend<type_list<Types...>, T>
{
    typedef type_list<T, Types...> type;
};

template <class TypeList, class T>
using prepend_t = typename prepend<TypeList, T>::type;


////////////////////////////////////////////////////////////////////////////////
// reverse a type_list
template <class TypeList, class TypeListOut>
struct reverse;

template <class First, class... Rest, class TypeListOut>
struct reverse<type_list<First, Rest...>, TypeListOut>
    : reverse<type_list<Rest...>, prepend_t<TypeListOut, First>>
{
};

template <class TypeListOut>
struct reverse<type_list<>, TypeListOut>
{
    typedef TypeListOut type;
};

template <class TypeList>
using reverse_t = typename reverse<TypeList, type_list<>>::type;
}
}
