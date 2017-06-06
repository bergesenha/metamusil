#include "catch.hpp"

#include <type_traits>

#include <type_list.hpp>


using namespace metamusil::t_list;

typedef type_list<int, char, double, long> mylist;

TEST_CASE("test head and tail metafunctions", "[type_list]")
{

    SECTION("take head of type_list")
    {
        typedef head_t<mylist> first;
        typedef tail_t<mylist> rest;

        auto same = std::is_same<first, int>::value;

        REQUIRE(same == true);

        SECTION("take head of tail")
        {
            typedef head_t<rest> first_of_rest;

            auto same2 = std::is_same<first_of_rest, char>::value;

            REQUIRE(same2 == true);
        }
    }
}


TEST_CASE("test prepend and append metafunctions", "[type_list]")
{
    SECTION("prepend a float")
    {
        typedef prepend_t<mylist, float> mylist2;

        auto same = std::is_same<head_t<mylist2>, float>::value;
        auto same2 = std::is_same<head_t<tail_t<mylist2>>, int>::value;

        REQUIRE(same == true);
        REQUIRE(same2 == true);
    }

    SECTION("append a float")
    {
        typedef append_t<mylist, float> mylist2;
        constexpr std::size_t sizeoflist = size<mylist>::value;

        auto same =
            std::is_same<float, type_at_index_t<mylist2, sizeoflist>>::value;

        REQUIRE(same == true);
    }

    SECTION("append float to empty type list")
    {
        typedef append_t<type_list<>, float> mylist2;

        auto same = std::is_same<head_t<mylist2>, float>::value;

        REQUIRE(same == true);
    }

    SECTION("prepend float to empty type list")
    {
        typedef prepend_t<type_list<>, float> mylist2;

        auto same = std::is_same<head_t<mylist2>, float>::value;

        REQUIRE(same == true);
    }
}


TEST_CASE("test append_if metafunction", "[type_list]")
{
    SECTION("successfully append float")
    {
        typedef append_if_t<type_list<>, float, std::is_floating_point>
            floatlist;

        auto same = std::is_same<head_t<floatlist>, float>::value;

        REQUIRE(same == true);
    }

    SECTION("unsuccessfully append float")
    {
        typedef append_if_t<type_list<>, float, std::is_integral> empty_list;

        auto same = std::is_same<empty_list, type_list<>>::value;

        REQUIRE(same == true);
    }
}


TEST_CASE("test reverse metafunction", "[type_list]")
{
    SECTION("reverse mylist")
    {
        typedef reverse_t<mylist> reversed;

        auto same =
            std::is_same<reversed, type_list<long, double, char, int>>::value;

        REQUIRE(same == true);
    }

    SECTION("reverse a type_list with one type")
    {
        typedef reverse_t<type_list<long>> reversed;

        auto same = std::is_same<reversed, type_list<long>>::value;

        REQUIRE(same == true);
    }

    SECTION("reverse an empty type_list")
    {
        typedef reverse_t<type_list<>> reversed;

        auto same = std::is_same<reversed, type_list<>>::value;

        REQUIRE(same == true);
    }
}


TEST_CASE("test concat metafunction", "[type_list]")
{
    SECTION("concat two type_lists")
    {
        typedef concat_t<mylist, type_list<float, int*>> concatenated;

        auto same = std::is_same<
            concatenated,
            type_list<int, char, double, long, float, int*>>::value;

        REQUIRE(same == true);
    }

    SECTION("concat two empty type_lists")
    {
        typedef concat_t<type_list<>, type_list<>> concatenated;

        auto same = std::is_same<concatenated, type_list<>>::value;

        REQUIRE(same == true);
    }

    SECTION("concat with empty list")
    {
        typedef concat_t<mylist, type_list<>> concatenated;

        auto same = std::is_same<concatenated, mylist>::value;

        REQUIRE(same == true);
    }

    SECTION("concat empty list with mylist")
    {
        typedef concat_t<type_list<>, mylist> concatenated;

        auto same = std::is_same<concatenated, mylist>::value;

        REQUIRE(same == true);
    }
}
