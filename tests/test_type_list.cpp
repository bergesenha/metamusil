#include "catch.hpp"

#include <type_traits>

#include <type_list.hpp>


using namespace metamusil::t_list;

typedef type_list<int, char, double, long> mylist;

template <class T>
using constify = const T;

template <class T>
struct get_size
{
    static const std::size_t value = sizeof(T);
};

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
        constexpr std::size_t sizeoflist = length<mylist>::value;

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


TEST_CASE("test type type_transform metafunction", "[type_list]")
{
    SECTION("constify mylist")
    {
        typedef type_transform_t<mylist, constify> constlist;

        auto same = std::is_same<
            constlist,
            type_list<const int, const char, const double, const long>>::value;

        REQUIRE(same == true);
    }

    SECTION("constify empty list")
    {
        typedef type_transform_t<type_list<>, constify> constlist;

        auto same = std::is_same<constlist, type_list<>>::value;

        REQUIRE(same == true);
    }

    SECTION("constify list of one element")
    {
        typedef type_transform_t<type_list<int>, constify> constlist;

        auto same = std::is_same<constlist, type_list<const int>>::value;

        REQUIRE(same == true);
    }
}


TEST_CASE("test value_transform metafunction", "[type_list]")
{
    SECTION("generate array of sizes of type in list")
    {
        auto& array_ref = value_transform<mylist, get_size>::value;

        const auto length = std::extent<decltype(
            value_transform<mylist, get_size>::value)>::value;

        REQUIRE(length == 4);
        REQUIRE(array_ref[0] == sizeof(int));
        REQUIRE(array_ref[1] == sizeof(char));
        REQUIRE(array_ref[2] == sizeof(double));
        REQUIRE(array_ref[3] == sizeof(long));
    }

    SECTION("value_transform on list of one type")
    {
        auto& array_ref = value_transform<type_list<int>, get_size>::value;

        const auto length = std::extent<decltype(
            value_transform<type_list<int>, get_size>::value)>::value;

        REQUIRE(length == 1);
        REQUIRE(array_ref[0] == sizeof(int));
    }
}


TEST_CASE("test length metafunction", "[type_list]")
{
    auto length0 = length<mylist>::value;
    auto length1 = length<type_list<int>>::value;
    auto length2 = length<type_list<>>::value;

    REQUIRE(length0 == 4);
    REQUIRE(length1 == 1);
    REQUIRE(length2 == 0);
}


TEST_CASE("test type_at_index", "[type_list]")
{
    typedef type_at_index_t<mylist, 0> type0;
    typedef type_at_index_t<mylist, 1> type1;
    typedef type_at_index_t<mylist, 2> type2;
    typedef type_at_index_t<mylist, 3> type3;

    auto same0 = std::is_same<type0, int>::value;
    auto same1 = std::is_same<type1, char>::value;
    auto same2 = std::is_same<type2, double>::value;
    auto same3 = std::is_same<type3, long>::value;

    REQUIRE(same0 == true);
    REQUIRE(same1 == true);
    REQUIRE(same2 == true);
    REQUIRE(same3 == true);
}

TEST_CASE("test index_of_type", "[type_list]")
{
    auto index0 = index_of_type<mylist, int>::value;
    auto index1 = index_of_type<mylist, char>::value;
    auto index2 = index_of_type<mylist, double>::value;
    auto index3 = index_of_type<mylist, long>::value;

    REQUIRE(index0 == 0);
    REQUIRE(index1 == 1);
    REQUIRE(index2 == 2);
    REQUIRE(index3 == 3);

    SECTION("should get index of first type matching")
    {
        typedef append_t<mylist, char> mylist2;

        auto charindex = index_of_type<mylist2, char>::value;

        REQUIRE(charindex == 1);
    }
}

TEST_CASE("test filter metaalgorithm", "[type_list]")
{
    SECTION("filter for floats")
    {
        typedef filter_t<mylist, std::is_floating_point> only_floats;

        auto length1 = length<only_floats>::value;

        auto same = std::is_same<only_floats, type_list<double>>::value;

        REQUIRE(length1 == 1);
        REQUIRE(same == true);
    }

    SECTION("filter for integrals")
    {
        typedef filter_t<mylist, std::is_integral> only_integrals;

        auto length1 = length<only_integrals>::value;

        auto same =
            std::is_same<only_integrals, type_list<int, char, long>>::value;

        REQUIRE(length1 == 3);
        REQUIRE(same == true);
    }

    SECTION("filter on empty list")
    {
        typedef filter_t<type_list<>, std::is_signed> empty;

        auto length1 = length<empty>::value;
        auto same = std::is_same<empty, type_list<>>::value;

        REQUIRE(length1 == 0);
        REQUIRE(same == true);
    }
}


TEST_CASE("test reorder and order metaalgorithm", "[type_list]")
{
    SECTION("reorder all elements in type_list")
    {
        typedef std::index_sequence<2, 1, 3, 0> the_order;

        typedef reorder_t<mylist, the_order> reordered;

        auto same =
            std::is_same<reordered, type_list<double, char, long, int>>::value;

        REQUIRE(same);

        SECTION("order of new type list according to old should be the order "
                "used to reorder")
        {
            typedef order_t<reordered, mylist> the_order_2;

            auto same_order = std::is_same<the_order_2, the_order>::value;

            REQUIRE(same_order);
        }
    }

    SECTION("reorder subset of elements in type_list")
    {
        typedef std::index_sequence<2, 1, 3> the_order;

        typedef reorder_t<mylist, the_order> reordered;

        auto same =
            std::is_same<reordered, type_list<double, char, long>>::value;

        REQUIRE(same);

        SECTION("order of new type list according to old should be the order "
                "used to reorder")
        {
            typedef order_t<reordered, mylist> the_order_2;

            auto same_order = std::is_same<the_order_2, the_order>::value;

            REQUIRE(same_order);
        }
    }
}
