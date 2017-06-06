#include "catch.hpp"

#include "function_deduction.hpp"


void
func1(void)
{
}

int
func2(void)
{
    return 4;
}

int
func3(double d)
{
    return d * 24;
}

void
func4(double, char)
{
}

const char*
func5(const char*, long long)
{
    return nullptr;
}

using namespace metamusil;

TEST_CASE("test return type deduction for free functions",
          "[deduce_return_type]")
{
    typedef deduce_return_type_t<decltype(func1)> ret_type1;
    typedef deduce_return_type_t<decltype(func2)> ret_type2;
    typedef deduce_return_type_t<decltype(func3)> ret_type3;
    typedef deduce_return_type_t<decltype(func4)> ret_type4;
    typedef deduce_return_type_t<decltype(func5)> ret_type5;

    auto same1 = std::is_same<ret_type1, void>::value;
    REQUIRE(same1);
    auto same2 = std::is_same<ret_type2, int>::value;
    REQUIRE(same2);
    auto same3 = std::is_same<ret_type3, int>::value;
    REQUIRE(same3);
    auto same4 = std::is_same<ret_type4, void>::value;
    REQUIRE(same4);
    auto same5 = std::is_same<ret_type5, const char*>::value;
    REQUIRE(same5);
}
