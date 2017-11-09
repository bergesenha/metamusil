#pragma once

namespace metamusil
{
namespace t_stack
{
template <class...>
struct type_stack
{
};

// push type onto stack
template <class TypeStack, class T>
struct push;

template <class... Ts, class T>
struct push<type_stack<Ts...>, T>
{
    typedef type_stack<T, Ts...> type;
};

template <class TypeStack, class T>
using push_t = typename push<TypeStack, T>::type;

// access type on top of stack
template <class TypeStack>
struct top;

template <class T, class... Ts>
struct top<type_stack<T, Ts...>>
{
    typedef T type;
};

template <class TypeStack>
using top_t = typename top<TypeStack>::type;


// pop type off top of stack
template <class TypeStack>
struct pop;

template <class T, class... Ts>
struct pop<type_stack<T, Ts...>>
{
    typedef type_stack<Ts...> type;
};

template <class TypeStack>
using pop_t = typename pop<TypeStack>::type;
}
}
