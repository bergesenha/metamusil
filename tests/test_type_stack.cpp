#include "catch.hpp"

#include <type_stack.hpp>

TEST_CASE("decompose types into type_stacks","[type_stack]")
{
    using namespace metamusil::t_stack;

    typedef decompose_t<int> int_stack;



    constexpr auto int_stack_check = std::is_same<int_stack, type_stack<int>>::value;

    CHECK(int_stack_check);
}
