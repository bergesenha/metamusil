#pragma once
#include <cstddef>
#include <utility>


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
// append a type to the back of a type_list
template <class TypeList, class T>
struct append;

template <class... Types, class T>
struct append<type_list<Types...>, T>
{
    typedef type_list<Types..., T> type;
};

template <class TypeList, class T>
using append_t = typename append<TypeList, T>::type;


////////////////////////////////////////////////////////////////////////////////
// append a type to the back of a type_list if the type satisfies UnaryPredicate
template <class TypeList,
          class T,
          template <class> class UnaryPredicate,
          bool Satisfies = UnaryPredicate<T>::value>
struct append_if
{
    typedef TypeList type;
};

template <class TypeList, class T, template <class> class UnaryPredicate>
struct append_if<TypeList, T, UnaryPredicate, true>
{
    typedef append_t<TypeList, T> type;
};

template <class TypeList, class T, template <class> class UnaryPredicate>
using append_if_t = typename append_if<TypeList, T, UnaryPredicate>::type;


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


////////////////////////////////////////////////////////////////////////////////
// concatenate two type_lists
template <class TypeList1, class TypeList2>
struct concat;

template <class... Types1, class... Types2>
struct concat<type_list<Types1...>, type_list<Types2...>>
{
    typedef type_list<Types1..., Types2...> type;
};

template <class TypeList1, class TypeList2>
using concat_t = typename concat<TypeList1, TypeList2>::type;


////////////////////////////////////////////////////////////////////////////////
// apply TypeMetaFunction to each type in TypeList and return type_list of the
// resulting types, where TypeMetaFunction is a type alias.
template <class TypeList, template <class> class TypeMetaFunction>
struct type_transform;

template <class... Types, template <class> class TypeMetaFunction>
struct type_transform<type_list<Types...>, TypeMetaFunction>
{
    typedef type_list<TypeMetaFunction<Types>...> type;
};

template <class TypeList, template <class> class TypeMetaFunction>
using type_transform_t =
    typename type_transform<TypeList, TypeMetaFunction>::type;


////////////////////////////////////////////////////////////////////////////////
// apply TypeMetaFunction to each type in TypeList and return array of the
// result of TypeMetaFunction on each type in TypeList.
template <class TypeList, template <class> class TypeMetaFunction>
struct value_transform;

template <class... Types, template <class> class TypeMetaFunction>
struct value_transform<type_list<Types...>, TypeMetaFunction>
{
    typedef decltype(TypeMetaFunction<head_t<type_list<Types...>>>::value) type;
    static constexpr type value[] = {TypeMetaFunction<Types>::value...};
};

template <template <class> class TypeMetaFunction>
struct value_transform<type_list<>, TypeMetaFunction>
{
    typedef std::nullptr_t type;
    static constexpr std::nullptr_t value = nullptr;
};

template <class... Types, template <class> class TypeMetaFunction>
constexpr typename value_transform<type_list<Types...>, TypeMetaFunction>::type
    value_transform<type_list<Types...>, TypeMetaFunction>::value[];


////////////////////////////////////////////////////////////////////////////////
// returns length of a type_list
template <class TypeList>
struct length;

template <class... Types>
struct length<type_list<Types...>>
{
    static const std::size_t value = sizeof...(Types);
};

template <class TypeList>
constexpr std::size_t length_v = length<TypeList>::value;

////////////////////////////////////////////////////////////////////////////////
// returns type at index in a type_list
template <class TypeList, std::size_t Index>
struct type_at_index : type_at_index<tail_t<TypeList>, Index - 1>
{
    static_assert(length_v<TypeList>> Index, "out of bounds access");
};

template <class TypeList>
struct type_at_index<TypeList, 0>
{
    typedef head_t<TypeList> type;
};


template <class TypeList, std::size_t Index>
using type_at_index_t = typename type_at_index<TypeList, Index>::type;


////////////////////////////////////////////////////////////////////////////////
// return index of first type encountered that matches T
template <class TypeList, class T, std::size_t Index = 0>
struct index_of_type;

template <class First, class... Rest, class T, std::size_t Index>
struct index_of_type<type_list<First, Rest...>, T, Index>
    : index_of_type<type_list<Rest...>, T, Index + 1>
{
};

template <class... Rest, class T, std::size_t Index>
struct index_of_type<type_list<T, Rest...>, T, Index>
{
    static const std::size_t value = Index;
};

template <class TypeList, class T>
constexpr std::size_t index_of_type_v = index_of_type<TypeList, T>::value;


////////////////////////////////////////////////////////////////////////////////
// returns type list exluding types that don't satisfy UnaryPredicate, ie for a
// type T UnaryPredicate<T>::value == false.
template <class TypeList,
          template <class> class UnaryPredicate,
          class Accum = type_list<>>
struct filter : filter<tail_t<TypeList>,
                       UnaryPredicate,
                       append_if_t<Accum, head_t<TypeList>, UnaryPredicate>>
{
};

template <template <class> class UnaryPredicate, class Accum>
struct filter<type_list<>, UnaryPredicate, Accum>
{
    typedef Accum type;
};

template <class TypeList, template <class> class UnaryPredicate>
using filter_t = typename filter<TypeList, UnaryPredicate>::type;


////////////////////////////////////////////////////////////////////////////////
// returns type list elements reordered according to given index
// sequence
template <class TypeList, class IndexSequence>
struct reorder;

template <class TypeList, std::size_t... Indices>
struct reorder<TypeList, std::index_sequence<Indices...>>
{
    typedef type_list<type_at_index_t<TypeList, Indices>...> type;
};

template <class TypeList, class IndexSequence>
using reorder_t = typename reorder<TypeList, IndexSequence>::type;


////////////////////////////////////////////////////////////////////////////////
// returns index_sequence of order of TypeList1 according to TypeList2

template <class TypeList, class TypeListReference>
struct order;

template <class... Types, class TypeListReference>
struct order<type_list<Types...>, TypeListReference>
{
    typedef std::index_sequence<
        index_of_type<TypeListReference, Types>::value...>
        type;
};

template <class TypeList, class TypeListReference>
using order_t = typename order<TypeList, TypeListReference>::type;


////////////////////////////////////////////////////////////////////////////////
// convert type_list into index sequence of same length
template <class TypeList>
struct index_sequence_for;

template <class... Types>
struct index_sequence_for<type_list<Types...>>
{
    typedef std::index_sequence_for<Types...> type;
};

template <class TypeList>
using index_sequence_for_t = typename index_sequence_for<TypeList>::type;


////////////////////////////////////////////////////////////////////////////////
// return a type_list consisting of template instantiations of Template with the
// types in TypeList
template <template <class> class Template, class TypeList>
struct from_template_instantiations;

template <template <class> class Template, class... Types>
struct from_template_instantiations<Template, type_list<Types...>>
{
    typedef type_list<Template<Types>...> type;
};

template <template <class> class Template, class TypeList>
using from_template_instantiations_t =
    typename from_template_instantiations<Template, TypeList>::type;


////////////////////////////////////////////////////////////////////////////////
// return a type_list consisting of template instantiations of Template with the
// integers in IntSeq
template <class IntType, template <IntType> class Template, class IntSeq>
struct from_integer_template_instantiations;

template <class IntType, template <IntType> class Template, IntType... Seq>
struct from_integer_template_instantiations<
    IntType,
    Template,
    std::integer_sequence<IntType, Seq...>>
{
    typedef type_list<Template<Seq>...> type;
};

template <class IntType, template <IntType> class Template, class IntSeq>
using from_integer_template_instantiations_t =
    typename from_integer_template_instantiations<IntType, Template, IntSeq>::
        type;


////////////////////////////////////////////////////////////////////////////////
// instantiate BinaryTemplate with every combination of types in TypeList
template <class TypeList,
          template <class, class> class BinaryTemplate,
          class Remaining = TypeList>
struct for_each_combination
{
    template <class T>
    using BindBinaryTemplate = BinaryTemplate<head_t<Remaining>, T>;

    typedef type_transform_t<TypeList, BindBinaryTemplate> current_list;

    typedef concat_t<current_list,
                     typename for_each_combination<TypeList,
                                                   BinaryTemplate,
                                                   tail_t<Remaining>>::type>
        type;
};

template <class TypeList, template <class, class> class BinaryTemplate>
struct for_each_combination<TypeList, BinaryTemplate, type_list<>>
{
    typedef type_list<> type;
};

template <class TypeList, template <class, class> class BinaryTemplate>
using for_each_combination_t =
    typename for_each_combination<TypeList, BinaryTemplate>::type;


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


////////////////////////////////////////////////////////////////////////////////
// remove element if it satisfies UnaryPredicate
template <class TypeList, template <class> class UnaryPredicate>
struct remove_if
{
    typedef filter_t<TypeList, negate<UnaryPredicate>::template type> type;
};

template <class TypeList, template <class> class UnaryPredicate>
using remove_if_t = typename remove_if<TypeList, UnaryPredicate>::type;
}
}
