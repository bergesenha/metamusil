#include "catch.hpp"
#include <function_type_descriptor.hpp>

struct tftd
{
};

TEST_CASE("decompose function types", "[decompose]")
{
    using namespace metamusil;

    typedef ft_descriptor::decompose_t<int(int, double)> int_int_double_desc;
    typedef ft_descriptor::decompose_t<int(*)(int, double)> int_int_double_desc2;
    typedef ft_descriptor::decompose_t<int(int, double) const> int_int_double_const_desc;
    typedef ft_descriptor::decompose_t<int (tftd::*) (int, double) const> int_int_double_mem_desc;

    constexpr bool int_int_double_check = std::is_same<
        int_int_double_desc,
        ft_descriptor::function_type_descriptor<int, false, int, double>>::
        value;

    constexpr bool int_int_double_check2 = std::is_same<
        int_int_double_desc2,
        ft_descriptor::function_type_descriptor<int, false, int, double>>::
        value;

    constexpr bool int_int_double_const_check = std::is_same<
        int_int_double_const_desc,
        ft_descriptor::function_type_descriptor<int, true, int, double>>::
        value;

    constexpr bool int_int_double_mem_check = std::is_same<
        int_int_double_mem_desc,
        ft_descriptor::function_type_descriptor<int, true, int, double>>::
        value;

    CHECK(int_int_double_check);
    CHECK(int_int_double_check2);
    CHECK(int_int_double_const_check);
    CHECK(int_int_double_mem_check);


    SECTION("compose back to function types")
    {
        typedef ft_descriptor::compose_t<int_int_double_desc> funtype1;
        typedef ft_descriptor::compose_t<int_int_double_desc2> funtype2;
        typedef ft_descriptor::compose_t<int_int_double_const_desc> funtype3;
        typedef ft_descriptor::compose_t<int_int_double_mem_desc> funtype4;

        typedef ft_descriptor::compose_member_function_pointer_t<int_int_double_desc, tftd> funtype5;

        constexpr bool same1 = std::is_same<funtype1, int(int, double)>::value;
        constexpr bool same2 = std::is_same<funtype2, int(int, double)>::value;
        constexpr bool same3 = std::is_same<funtype3, int(int, double) const>::value;
        constexpr bool same4 = std::is_same<funtype4, int(int, double) const>::value;
        constexpr bool same5 = std::is_same<funtype5, int tftd::*(int, double)>::value;


        CHECK(same1);
        CHECK(same2);
        CHECK(same3);
        CHECK(same4);
        CHECK(same5);
    }
}
