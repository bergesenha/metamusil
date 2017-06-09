#pragma once

#include <utility>


namespace metamusil
{
namespace int_seq
{


template <class IntSeq, typename IntSeq::value_type Num>
struct append;

template <class IntType, IntType... Nums, IntType Num>
struct append<std::integer_sequence<IntType, Nums...>, Num>
{
    typedef std::integer_sequence<IntType, Nums..., Num> type;
};

template <class IntSeq, typename IntSeq::value_type Num>
using append_t = typename append<IntSeq, Num>::type;

}
}
