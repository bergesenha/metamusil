#pragma once

#include <type_stack.hpp>

#include <type_traits>


namespace metamusil
{
namespace t_descriptor
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
    rreference_tag,
    array_tag,
};

typedef std::integral_constant<type_tag, type_tag::pointer_tag> Pointer;
typedef std::integral_constant<type_tag, type_tag::const_tag> Const;
typedef std::integral_constant<type_tag, type_tag::lreference_tag> LReference;
typedef std::integral_constant<type_tag, type_tag::rreference_tag> RReference;
typedef std::integral_constant<type_tag, type_tag::array_tag> Array;


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

template <class T>
struct apply<T, Array>
{
    typedef T type[];
};

template <class T, class Tag>
using apply_t = typename apply<T, Tag>::type;


// compose a type from a type_stack
template <class TypeDescriptor>
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


// make type_descriptor from type T and type_stack of tags TagStack
template <class T, class TagStack>
struct make_type_descriptor;

template <class T, class... Ts>
struct make_type_descriptor<T, t_stack::type_stack<Ts...>>
{
    typedef type_descriptor<T, Ts...> type;
};

template <class T, class TagStack>
using make_type_descriptor_t = typename make_type_descriptor<T, TagStack>::type;

// decompose a type into a type_descriptor
template <class T, class TagStack>
struct decompose_
{
    typedef make_type_descriptor_t<T, TagStack> type;
};

template <class T, class TagStack>
struct decompose_<T*, TagStack>
    : decompose_<T, t_stack::push_t<TagStack, Pointer>>
{
};

template <class T, class TagStack>
struct decompose_<const T, TagStack>
    : decompose_<T, t_stack::push_t<TagStack, Const>>
{
};

template <class T, class TagStack>
struct decompose_<T&, TagStack>
    : decompose_<T, t_stack::push_t<TagStack, LReference>>
{
};

template <class T, class TagStack>
struct decompose_<T&&, TagStack>
    : decompose_<T, t_stack::push_t<TagStack, RReference>>
{
};

template <class T, class TagStack>
struct decompose_<T[], TagStack>
    : decompose_<T, t_stack::push_t<TagStack, Array>>
{
};

template <class T>
using decompose = decompose_<T, t_stack::type_stack<>>;

template <class T>
using decompose_t = typename decompose<T>::type;


// create array of type_tags from a type_descriptor
template <class TypeDescriptor>
struct array_from_descriptor;

template <class T, class... Tags>
struct array_from_descriptor<type_descriptor<T, Tags...>>
{
    static constexpr const type_tag value[] = {Tags::value...};
};

template <class T, class... Tags>
constexpr const type_tag
    array_from_descriptor<type_descriptor<T, Tags...>>::value[];


template <class T>
struct array_from_descriptor<type_descriptor<T>>
{
    static constexpr const type_tag* value = nullptr;
};

template <class T>
constexpr const type_tag* array_from_descriptor<type_descriptor<T>>::value;
}
}
