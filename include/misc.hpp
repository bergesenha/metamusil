#pragma once


namespace metamusil
{
////////////////////////////////////////////////////////////////////////////////
// negates a unary metapredicate
template <template <class> class UnaryPredicate>
struct negate
{
    template <class T>
    struct negative_predicate
    {
        static const bool value = !UnaryPredicate<T>::value;
    };

    template <class T>
    using type = negative_predicate<T>;
};
}
