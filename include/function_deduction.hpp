#pragma once


namespace metamusil
{
template <class FunctionType>
struct deduce_return_type;

template <class RetType, class... ArgTypes>
struct deduce_return_type<RetType(ArgTypes...)>
{
    typedef RetType type;
};

template <class RetType, class... ArgTypes>
struct deduce_return_type<RetType (*)(ArgTypes...)>
{
    typedef RetType type;
};

template <class RetType, class ObjectType, class... ArgTypes>
struct deduce_return_type<RetType (ObjectType::*)(ArgTypes...)>
{
    typedef RetType type;
};


template <class RetType, class ObjectType, class... ArgTypes>
struct deduce_return_type<RetType (ObjectType::*)(ArgTypes...) const>
{
    typedef RetType type;
};

template <class FunctionType>
using deduce_return_type_t = typename deduce_return_type<FunctionType>::type;
}
