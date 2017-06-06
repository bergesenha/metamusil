#include "catch.hpp"

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
