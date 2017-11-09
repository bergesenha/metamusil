#pragma once

#include <type_stack.hpp>

#include <type_traits>


namespace metamusil
{
namespace t_stack
{


// represents a type as its base type and qualifiers/modifiers in a stack
template <class BaseType, class... Tags>
struct type_descriptor
{
};


// represents qualifiers/modifiers at run time
enum class type_tag
{
    pointer_tag,
    const_tag,
    lreference_tag,
    rreference_tag
};

typedef std::integral_constant<type_tag, type_tag::pointer_tag> Pointer;
typedef std::integral_constant<type_tag, type_tag::const_tag> Const;
typedef std::integral_constant<type_tag, type_tag::lreference_tag> LReference;
typedef std::integral_constant<type_tag, type_tag::rreference_tag> RReference;


// apply a qualifier/modifier to type from a Tag
template <class T, class Tag>
struct apply;

template <class T>
struct apply<T, std::integral_constant<type_tag, type_tag::pointer_tag>>
{
    typedef T* type;
};

template <class T>
struct apply<T, std::integral_constant<type_tag, type_tag::const_tag>>
{
    typedef const T type;
};

template <class T>
struct apply<T, std::integral_constant<type_tag, type_tag::lreference_tag>>
{
    typedef T& type;
};

template <class T>
struct apply<T, std::integral_constant<type_tag, type_tag::rreference_tag>>
{
    typedef T&& type;
};

template <class T, class Tag>
using apply_t = typename apply<T, Tag>::type;


// compose a type from a type_stack
template <class TypeStack>
struct compose;

template <class T>
struct compose<type_descriptor<T>>
{
    typedef T type;
};

template <class T, class Tag, class... RestTags>
struct compose<type_descriptor<T, Tag, RestTags...>>
    : compose<type_descriptor<apply_t<T, Tag>, RestTags...>>
{
};

template <class TypeStack>
using compose_t = typename compose<TypeStack>::type;
}
}
