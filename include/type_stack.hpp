#pragma once


namespace metamusil
{
namespace t_stack
{
// represents a type as its base type and qualifiers/modifiers in a stack
template <class, class...>
struct type_stack
{
};


enum class type_tag
{
    pointer_tag,
    const_tag,
    lreference_tag,
    rreference_tag
};

struct Pointer
{
    static const type_tag value = type_tag::pointer_tag;
};

struct Const
{
    static const type_tag value = type_tag::const_tag;
};

struct LReference
{
    static const type_tag value = type_tag::lreference_tag;
};

struct RReference
{
    static const type_tag value = type_tag::rreference_tag;
};
}
}
