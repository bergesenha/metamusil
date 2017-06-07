#pragma once


namespace metamusil
{
template <class MemberVariableType>
struct deduce_member_variable_type;

template <class VariableType, class ObjectType>
struct deduce_member_variable_type<VariableType ObjectType::*>
{
    typedef VariableType type;
};


template <class MemberVariableType>
struct deduce_member_variable_object_type;

template <class VariableType, class ObjectType>
struct deduce_member_variable_object_type<VariableType ObjectType::*>
{
    typedef ObjectType type;
};
}
