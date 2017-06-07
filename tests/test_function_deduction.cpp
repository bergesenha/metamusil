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

struct class1
{
    void mfunc1(void);
    int mfunc2(void);
    int mfunc3(double);
    void mfunc4(double, char);
    const char* mfunc5(const char*, long long);

    void cmfunc1(void);
    int cmfunc2(void);
    int cmfunc3(double);
    void cmfunc4(double, char);
    const char* cmfunc5(const char*, long long);
};

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

TEST_CASE("test return type deduction for member functions",
          "[deduce_return_type]")
{
    typedef deduce_return_type_t<decltype(&class1::mfunc1)> ret_type1;
    typedef deduce_return_type_t<decltype(&class1::mfunc2)> ret_type2;
    typedef deduce_return_type_t<decltype(&class1::mfunc3)> ret_type3;
    typedef deduce_return_type_t<decltype(&class1::mfunc4)> ret_type4;
    typedef deduce_return_type_t<decltype(&class1::mfunc5)> ret_type5;

    typedef deduce_return_type_t<decltype(&class1::cmfunc1)> cret_type1;
    typedef deduce_return_type_t<decltype(&class1::cmfunc2)> cret_type2;
    typedef deduce_return_type_t<decltype(&class1::cmfunc3)> cret_type3;
    typedef deduce_return_type_t<decltype(&class1::cmfunc4)> cret_type4;
    typedef deduce_return_type_t<decltype(&class1::cmfunc5)> cret_type5;

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

    auto csame1 = std::is_same<cret_type1, void>::value;
    REQUIRE(csame1);
    auto csame2 = std::is_same<cret_type2, int>::value;
    REQUIRE(csame2);
    auto csame3 = std::is_same<cret_type3, int>::value;
    REQUIRE(csame3);
    auto csame4 = std::is_same<cret_type4, void>::value;
    REQUIRE(csame4);
    auto csame5 = std::is_same<cret_type5, const char*>::value;
    REQUIRE(csame5);
}
