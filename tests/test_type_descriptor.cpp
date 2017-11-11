#include "catch.hpp"

#include <type_descriptor.hpp>


TEST_CASE("apply type tags to types")
{
    using namespace metamusil::t_descriptor;

    typedef apply_t<int,
                    std::integral_constant<type_tag, type_tag::pointer_tag>>
        ptr_int_type;
    typedef apply_t<int, Array> arr_int_type;
    typedef apply_t<int,
                    std::integral_constant<type_tag, static_cast<type_tag>(10)>>
        arr_10_int_type;

    constexpr auto is_ptr_int = std::is_same<ptr_int_type, int*>::value;
    constexpr auto is_arr_int = std::is_same<arr_int_type, int[]>::value;
    constexpr auto is_arr_10_int =
        std::is_same<arr_10_int_type, int[10]>::value;

    CHECK(is_ptr_int);
    CHECK(is_arr_int);
    CHECK(is_arr_10_int);
}


TEST_CASE("decompose types to type_descriptors", "[type_descriptor]")
{
    using namespace metamusil::t_descriptor;


    typedef decompose_t<int> int_desc;
    typedef decompose_t<const int*> ptr_const_int_desc;

    typedef decompose_t<int*&> lref_ptr_int_desc;
    typedef decompose_t<const int* const&> lref_const_ptr_const_int_desc;

    typedef decompose_t<int[]> arr_int_desc;
    typedef decompose_t<int[20]> arr_20_int_desc;
    typedef decompose_t<int(&)[20]> lref_arr_20_int_desc;
    typedef decompose_t<int const[10]> arr_10_const_int_desc;

    constexpr auto int_check =
        std::is_same<int_desc, type_descriptor<int>>::value;
    constexpr auto ptr_const_int_check =
        std::is_same<ptr_const_int_desc,
                     type_descriptor<int, Const, Pointer>>::value;
    constexpr auto lref_ptr_int_check =
        std::is_same<lref_ptr_int_desc,
                     type_descriptor<int, Pointer, LReference>>::value;
    constexpr auto lref_const_ptr_const_int_check = std::is_same<
        lref_const_ptr_const_int_desc,
        type_descriptor<int, Const, Pointer, Const, LReference>>::value;
    constexpr auto arr_int_check =
        std::is_same<arr_int_desc, type_descriptor<int, Array>>::value;
    constexpr auto arr_20_int_check = std::is_same<
        arr_20_int_desc,
        type_descriptor<
            int,
            std::integral_constant<type_tag, static_cast<type_tag>(20)>>>::
        value;
    constexpr auto lref_arr_20_int_check = std::is_same<
        lref_arr_20_int_desc,
        type_descriptor<
            int,
            std::integral_constant<type_tag, static_cast<type_tag>(20)>,
            LReference>>::value;
    constexpr auto arr_10_const_int_check = std::is_same<
        arr_10_const_int_desc,
        type_descriptor<
            int,
            Const,
            std::integral_constant<type_tag, static_cast<type_tag>(10)>>>::
        value;


    CHECK(int_check);
    CHECK(ptr_const_int_check);
    CHECK(lref_ptr_int_check);
    CHECK(lref_const_ptr_const_int_check);
    CHECK(arr_int_check);
    CHECK(arr_20_int_check);
    CHECK(lref_arr_20_int_check);
    CHECK(arr_10_const_int_check);

    SECTION("generate arrays of type_tags from descriptors")
    {
        typedef array_from_descriptor<int_desc> int_arr_holder;
        typedef array_from_descriptor<ptr_const_int_desc>
            ptr_const_int_arr_holder;
        typedef array_from_descriptor<arr_10_const_int_desc>
            arr_10_const_int_arr_holder;

        auto i = array_from_descriptor_v<arr_10_const_int_desc>[0];

        CHECK(int_arr_holder::value == nullptr);
        REQUIRE(std::extent<decltype(ptr_const_int_arr_holder::value)>::value ==
                2);
        CHECK(ptr_const_int_arr_holder::value[0] == type_tag::const_tag);
        CHECK(ptr_const_int_arr_holder::value[1] == type_tag::pointer_tag);
        REQUIRE(
            std::extent<decltype(arr_10_const_int_arr_holder::value)>::value ==
            2);
        CHECK(arr_10_const_int_arr_holder::value[0] == type_tag::const_tag);
        CHECK(i == type_tag::const_tag);
        CHECK(arr_10_const_int_arr_holder::value[1] ==
              static_cast<type_tag>(10));
    }

    SECTION("replace base types")
    {
        typedef replace_base_type_t<ptr_const_int_desc, double>
            ptr_const_double_desc;

        constexpr auto ptr_const_double_check =
            std::is_same<ptr_const_double_desc,
                         type_descriptor<double, Const, Pointer>>::value;

        CHECK(ptr_const_double_check);
    }

    SECTION("remove const from whole type")
    {
        typedef remove_all_const_t<lref_const_ptr_const_int_desc>
            lref_ptr_int_desc2;

        constexpr auto lref_ptr_int_check2 =
            std::is_same<lref_ptr_int_desc2,
                         type_descriptor<int, Pointer, LReference>>::value;

        CHECK(lref_ptr_int_check2);
    }

    SECTION("remove pointer modifiers from types")
    {
        typedef remove_all_pointers_t<lref_ptr_int_desc> lref_int_desc;

        constexpr auto lref_int_check =
            std::is_same<lref_int_desc,
                         type_descriptor<int, LReference>>::value;

        CHECK(lref_int_check);
    }
}
