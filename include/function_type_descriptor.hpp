#pragma once

#include <cstddef>


namespace metamusil
{
namespace ft_descriptor
{

template <class ReturnType, bool Constness, class... ParamTypes>
struct function_type_descriptor
{
};

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

}
}
