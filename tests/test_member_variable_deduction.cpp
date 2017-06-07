#include "catch.hpp"

#include <member_variable_deduction.hpp>


class hasmemvars
{
public:
    int var1;
    double var2;
    const char* var3;
};

using namespace metamusil;

TEST_CASE("test member variable deduction", "[deduce_member_variable_*]")
{
    typedef deduce_member_variable_type_t<decltype(&hasmemvars::var1)> type1;
    typedef deduce_member_variable_type_t<decltype(&hasmemvars::var2)> type2;
    typedef deduce_member_variable_type_t<decltype(&hasmemvars::var3)> type3;

    typedef deduce_member_variable_object_type_t<decltype(&hasmemvars::var1)>
        obj_type1;
    typedef deduce_member_variable_object_type_t<decltype(&hasmemvars::var2)>
        obj_type2;
    typedef deduce_member_variable_object_type_t<decltype(&hasmemvars::var3)>
        obj_type3;

    auto same1 = std::is_same<type1, int>::value;
    auto same2 = std::is_same<type2, double>::value;
    auto same3 = std::is_same<type3, const char*>::value;

    auto objsame1 = std::is_same<obj_type1, hasmemvars>::value;
    auto objsame2 = std::is_same<obj_type2, hasmemvars>::value;
    auto objsame3 = std::is_same<obj_type3, hasmemvars>::value;

    REQUIRE(same1);
    REQUIRE(same2);
    REQUIRE(same3);

    REQUIRE(objsame1);
    REQUIRE(objsame2);
    REQUIRE(objsame3);
}
