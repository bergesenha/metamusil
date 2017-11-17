#pragma once

#include <cstddef>


namespace metamusil
{
namespace ft_descriptor
{

// holds function type information at compile time
template <class ReturnType, bool Constness, class... ParamTypes>
struct function_type_descriptor
{
};


// compose a function type from a function_type_descriptor
template <class FuncTypeDesc>
struct compose;

template <class ReturnType, bool Constness, class... ParamTypes>
struct compose<function_type_descriptor<ReturnType, Constness, ParamTypes...>>
{
    typedef ReturnType type(ParamTypes...);
};

template <class ReturnType, class... ParamTypes>
struct compose<function_type_descriptor<ReturnType, true, ParamTypes...>>
{
    typedef ReturnType type(ParamTypes...) const;
};

template <class FuncTypeDesc>
using compose_t = typename compose<FuncTypeDesc>::type;

// decompose a function type to a function_type_descriptor
template <class FunctionType>
struct decompose;


template <class ReturnType, class... ParamTypes>
struct decompose<ReturnType(ParamTypes...)>
{
    typedef function_type_descriptor<ReturnType, false, ParamTypes...> type;
};

template <class ReturnType, class... ParamTypes>
struct decompose<ReturnType(ParamTypes...) const>
{
    typedef function_type_descriptor<ReturnType, true, ParamTypes...> type;
};

template <class FunctionType>
using decompose_t = typename decompose<FunctionType>::type;
}
}
