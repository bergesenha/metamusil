#pragma once

#include <type_traits>


namespace metamusil
{
namespace t_stack
{
// represents a type as its base type and qualifiers/modifiers in a stack
template <class BaseType, class... Tags>
struct type_stack
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


template <class TypeStack, class Tag>
struct push_tag;

template <class T, class... Tags, class Tag>
struct push_tag<type_stack<T, Tags...>, Tag>
{
    typedef type_stack<T, Tag, Tags...> type;
};

template <class TypeStack, class Tag>
using push_tag_t = typename push_tag<TypeStack, Tag>::type;


// decompose a given type T into type_stack of the type and tags of modifiers
// and qualifiers
template <class T, class TypeStack>
struct decompose_
{
    typedef TypeStack type;
};

template <class T, class TypeStack>
struct decompose_<T*, TypeStack>
    : decompose_<
          T,
          push_tag_t<TypeStack,
                     std::integral_constant<type_tag, type_tag::pointer_tag>>>
{
};

template <class T, class TypeStack>
struct decompose_<const T, TypeStack>
    : decompose_<
          T,
          push_tag_t<TypeStack,
                     std::integral_constant<type_tag, type_tag::const_tag>>>
{
};

template <class T, class TypeStack>
struct decompose_<T&, TypeStack>
    : decompose_<T,
                 push_tag_t<TypeStack,
                            std::integral_constant<type_tag,
                                                   type_tag::lreference_tag>>>
{
};

template <class T, class TypeStack>
struct decompose_<T&&, TypeStack>
    : decompose_<T,
                 push_tag_t<TypeStack,
                            std::integral_constant<type_tag,
                                                   type_tag::rreference_tag>>>
{
};

template <class T>
using decompose = decompose_<T, type_stack<T>>;

template <class T>
using decompose_t = typename decompose<T>::type;


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
struct compose<type_stack<T>>
{
    typedef T type;
};

template <class T, class Tag, class... RestTags>
struct compose<type_stack<T, Tag, RestTags...>>
    : compose<type_stack<apply_t<T, Tag>, RestTags...>>
{
};

template <class TypeStack>
using compose_t = typename compose<TypeStack>::type;


// create array of tags of modifiers/qualifiers
template <class TypeStack>
struct to_type_tag_array;

template <class T, class... Tags>
struct to_type_tag_array<type_stack<T, Tags...>>
{
    static constexpr const type_tag value[] = {Tags::value...};
};

template <class T, class... Tags>
constexpr const type_tag to_type_tag_array<type_stack<T, Tags...>>::value[];

template <class T>
struct to_type_tag_array<type_stack<T>>
{
    static constexpr type_tag* value = nullptr;
};

template <class T>
constexpr type_tag* to_type_tag_array<type_stack<T>>::value;
}
}
