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

void
func6(const int& i)
{
}

void
func7(int& i)
{
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


TEST_CASE("test parameter type deduction for free functions",
          "[deduce_parameter_types]")
{
    typedef deduce_parameter_types_t<decltype(func1)> param_list1;
    typedef deduce_parameter_types_t<decltype(func2)> param_list2;
    typedef deduce_parameter_types_t<decltype(func3)> param_list3;
    typedef deduce_parameter_types_t<decltype(func4)> param_list4;
    typedef deduce_parameter_types_t<decltype(func5)> param_list5;
    typedef deduce_parameter_types_t<decltype(func6)> param_list6;
    typedef deduce_parameter_types_t<decltype(func7)> param_list7;

    auto same1 = std::is_same<param_list1, t_list::type_list<>>::value;
    REQUIRE(same1);
    auto same2 = std::is_same<param_list2, t_list::type_list<>>::value;
    REQUIRE(same2);
    auto same3 = std::is_same<param_list3, t_list::type_list<double>>::value;
    REQUIRE(same3);
    auto same4 =
        std::is_same<param_list4, t_list::type_list<double, char>>::value;
    REQUIRE(same4);
    auto same5 = std::is_same<param_list5,
                              t_list::type_list<const char*, long long>>::value;
    REQUIRE(same5);
    auto same6 =
        std::is_same<param_list6, t_list::type_list<const int&>>::value;
    REQUIRE(same6);
    auto same7 = std::is_same<param_list7, t_list::type_list<int&>>::value;
    REQUIRE(same7);
}


TEST_CASE("test parameter type deduction for member functions",
          "[deduce_parameter_types]")
{
    typedef deduce_parameter_types_t<decltype(&class1::mfunc1)> param_list1;
    typedef deduce_parameter_types_t<decltype(&class1::mfunc2)> param_list2;
    typedef deduce_parameter_types_t<decltype(&class1::mfunc3)> param_list3;
    typedef deduce_parameter_types_t<decltype(&class1::mfunc4)> param_list4;
    typedef deduce_parameter_types_t<decltype(&class1::mfunc5)> param_list5;

    auto same1 = std::is_same<param_list1, t_list::type_list<>>::value;
    REQUIRE(same1);
    auto same2 = std::is_same<param_list2, t_list::type_list<>>::value;
    REQUIRE(same2);
    auto same3 = std::is_same<param_list3, t_list::type_list<double>>::value;
    REQUIRE(same3);
    auto same4 =
        std::is_same<param_list4, t_list::type_list<double, char>>::value;
    REQUIRE(same4);
    auto same5 = std::is_same<param_list5,
                              t_list::type_list<const char*, long long>>::value;
    REQUIRE(same5);


    typedef deduce_parameter_types_t<decltype(&class1::cmfunc1)> cparam_list1;
    typedef deduce_parameter_types_t<decltype(&class1::cmfunc2)> cparam_list2;
    typedef deduce_parameter_types_t<decltype(&class1::cmfunc3)> cparam_list3;
    typedef deduce_parameter_types_t<decltype(&class1::cmfunc4)> cparam_list4;
    typedef deduce_parameter_types_t<decltype(&class1::cmfunc5)> cparam_list5;

    auto csame1 = std::is_same<cparam_list1, t_list::type_list<>>::value;
    REQUIRE(csame1);
    auto csame2 = std::is_same<cparam_list2, t_list::type_list<>>::value;
    REQUIRE(csame2);
    auto csame3 = std::is_same<cparam_list3, t_list::type_list<double>>::value;
    REQUIRE(csame3);
    auto csame4 =
        std::is_same<cparam_list4, t_list::type_list<double, char>>::value;
    REQUIRE(csame4);
    auto csame5 =
        std::is_same<cparam_list5,
                     t_list::type_list<const char*, long long>>::value;
    REQUIRE(csame5);
}


TEST_CASE("test deduce_object_type for member functions",
          "[deduce_object_type]")
{
    typedef deduce_object_type_t<decltype(&class1::mfunc1)> object_type1;
    typedef deduce_object_type_t<decltype(&class1::mfunc2)> object_type2;
    typedef deduce_object_type_t<decltype(&class1::mfunc3)> object_type3;
    typedef deduce_object_type_t<decltype(&class1::mfunc4)> object_type4;
    typedef deduce_object_type_t<decltype(&class1::mfunc5)> object_type5;

    auto same1 = std::is_same<object_type1, class1>::value;
    auto same2 = std::is_same<object_type2, class1>::value;
    auto same3 = std::is_same<object_type3, class1>::value;
    auto same4 = std::is_same<object_type4, class1>::value;
    auto same5 = std::is_same<object_type5, class1>::value;

    REQUIRE(same1);
    REQUIRE(same2);
    REQUIRE(same3);
    REQUIRE(same4);
    REQUIRE(same5);


    typedef deduce_object_type_t<decltype(&class1::cmfunc1)> object_type1;
    typedef deduce_object_type_t<decltype(&class1::cmfunc2)> object_type2;
    typedef deduce_object_type_t<decltype(&class1::cmfunc3)> object_type3;
    typedef deduce_object_type_t<decltype(&class1::cmfunc4)> object_type4;
    typedef deduce_object_type_t<decltype(&class1::cmfunc5)> object_type5;

    auto csame1 = std::is_same<object_type1, class1>::value;
    auto csame2 = std::is_same<object_type2, class1>::value;
    auto csame3 = std::is_same<object_type3, class1>::value;
    auto csame4 = std::is_same<object_type4, class1>::value;
    auto csame5 = std::is_same<object_type5, class1>::value;

    REQUIRE(csame1);
    REQUIRE(csame2);
    REQUIRE(csame3);
    REQUIRE(csame4);
    REQUIRE(csame5);
}
