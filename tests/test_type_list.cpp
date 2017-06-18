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


template <class T>
struct test_template
{
};

template <std::size_t N>
struct static_square
{
    static const std::size_t value = N * N;
};

template <class T>
struct extract_square_value
{
    static const std::size_t value = T::value;
};


template <class A, class B>
struct binary_template
{
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
        constexpr std::size_t sizeoflist = length_v<mylist>;

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

    SECTION("value_transform on empty type_list")
    {
        typedef value_transform<type_list<>, get_size> holds_value;

        auto same = std::is_same<holds_value::type, std::nullptr_t>::value;
        auto same2 = holds_value::value == nullptr;

        REQUIRE(same);
        REQUIRE(same2);
    }
}


TEST_CASE("test length metafunction", "[type_list]")
{
    auto length0 = length_v<mylist>;
    auto length1 = length_v<type_list<int>>;
    auto length2 = length_v<type_list<>>;

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
    constexpr auto index0 = index_of_type_v<mylist, int>;
    constexpr auto index1 = index_of_type_v<mylist, char>;
    constexpr auto index2 = index_of_type_v<mylist, double>;
    constexpr auto index3 = index_of_type_v<mylist, long>;

    REQUIRE(index0 == 0);
    REQUIRE(index1 == 1);
    REQUIRE(index2 == 2);
    REQUIRE(index3 == 3);

    SECTION("should get index of first type matching")
    {
        typedef append_t<mylist, char> mylist2;

        constexpr auto charindex = index_of_type_v<mylist2, char>;

        REQUIRE(charindex == 1);
    }
}

TEST_CASE("test filter metaalgorithm", "[type_list]")
{
    SECTION("filter for floats")
    {
        typedef filter_t<mylist, std::is_floating_point> only_floats;

        auto length1 = length_v<only_floats>;

        auto same = std::is_same<only_floats, type_list<double>>::value;

        REQUIRE(length1 == 1);
        REQUIRE(same == true);
    }

    SECTION("filter for integrals")
    {
        typedef filter_t<mylist, std::is_integral> only_integrals;

        auto length1 = length_v<only_integrals>;

        auto same =
            std::is_same<only_integrals, type_list<int, char, long>>::value;

        REQUIRE(length1 == 3);
        REQUIRE(same == true);
    }

    SECTION("filter on empty list")
    {
        typedef filter_t<type_list<>, std::is_signed> empty;

        auto length1 = length_v<empty>;
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


TEST_CASE("test order/order_t", "[order]")
{
    typedef type_list<int, long, float, double> reference_list;

    SECTION("order of a type_list of one element")
    {
        typedef type_list<float> compare_list;

        typedef order_t<compare_list, reference_list> order_of_compare_list;

        auto same =
            std::is_same<order_of_compare_list, std::index_sequence<2>>::value;

        REQUIRE(same);
    }

    SECTION("order of a type_list of same number of elements as reference_list")
    {
        typedef type_list<double, float, long, int> reversed_list;

        typedef order_t<reversed_list, reference_list> reverse_order;

        auto same =
            std::is_same<reverse_order, std::index_sequence<3, 2, 1, 0>>::value;

        REQUIRE(same);
    }

    SECTION("order of a type_list of more elements than reference list")
    {
        typedef type_list<double, float, long, int, long, float, double>
            long_list;

        typedef order_t<long_list, reference_list> order_of_long_list;

        auto same =
            std::is_same<order_of_long_list,
                         std::index_sequence<3, 2, 1, 0, 1, 2, 3>>::value;

        REQUIRE(same);
    }

    SECTION("order of an empty type list should return empty index_sequence")
    {
        typedef type_list<> empty_list;

        typedef order_t<empty_list, reference_list> order_of_empty;

        auto same = std::is_same<order_of_empty, std::index_sequence<>>::value;

        REQUIRE(same);
    }
}

TEST_CASE("test from_template_instantiations", "[from_template_instantiations]")
{
    typedef type_list<int, long, double, char> the_types;

    typedef from_template_instantiations_t<test_template, the_types>
        instantiations;

    auto same = std::is_same<instantiations,
                             type_list<test_template<int>,
                                       test_template<long>,
                                       test_template<double>,
                                       test_template<char>>>::value;

    REQUIRE(same);
}


TEST_CASE("test from_integer_template_instantiations",
          "[from_integer_template_instantiations]")
{
    typedef std::make_index_sequence<3> the_sequence;

    typedef from_integer_template_instantiations_t<std::size_t,
                                                   static_square,
                                                   the_sequence>
        instantiations;

    auto same = std::is_same<
        instantiations,
        type_list<static_square<0>, static_square<1>, static_square<2>>>::value;

    REQUIRE(same);

    SECTION("extract values from type list of static_squares")
    {
        auto& array_ref =
            value_transform<instantiations, extract_square_value>::value;

        REQUIRE(array_ref[0] == 0);
        REQUIRE(array_ref[1] == 1);
        REQUIRE(array_ref[2] == 4);
    }
}


TEST_CASE("test variable template version of length metafunction", "[length_v]")
{
    typedef type_list<int, long, double, char> the_list;

    auto the_length = length_v<the_list>;

    REQUIRE(the_length == 4);
}


TEST_CASE("test for_each_combination with empty type_list",
          "[for_each_combination]")
{
    typedef type_list<> the_list;

    typedef for_each_combination_t<the_list, binary_template> result;

    auto same = std::is_same<result, type_list<>>::value;

    REQUIRE(same);
}


TEST_CASE("test for_each_combination with type_list of one element",
          "[for_each_combination]")
{
    typedef type_list<int> the_list;

    typedef for_each_combination_t<the_list, binary_template> result;

    auto same =
        std::is_same<result, type_list<binary_template<int, int>>>::value;

    REQUIRE(same);
}


TEST_CASE("test for_each_combination with type_list of two elements",
          "[for_each_combination]")
{
    typedef type_list<int, long> the_list;

    typedef for_each_combination_t<the_list, binary_template> result;

    auto same = std::is_same<result,
                             type_list<binary_template<int, int>,
                                       binary_template<int, long>,
                                       binary_template<long, int>,
                                       binary_template<long, long>>>::value;

    REQUIRE(same);
}


TEST_CASE("test for_each_combination with type_list of three elements",
          "[for_each_combination]")
{
    typedef type_list<int, long, double> the_list;

    typedef for_each_combination_t<the_list, binary_template> result;

    auto same = std::is_same<result,
                             type_list<binary_template<int, int>,
                                       binary_template<int, long>,
                                       binary_template<int, double>,
                                       binary_template<long, int>,
                                       binary_template<long, long>,
                                       binary_template<long, double>,
                                       binary_template<double, int>,
                                       binary_template<double, long>,
                                       binary_template<double, double>>>::value;

    REQUIRE(same);
}


TEST_CASE("test negate", "[negate]")
{
    auto isnt_integral =
        metamusil::negate<std::is_integral>::type<float>::value;

    REQUIRE(isnt_integral);
}


TEST_CASE("test negate in metaalgorithm", "[negate]")
{
    typedef type_list<int, float, double> the_list;

    typedef filter_t<the_list, metamusil::negate<std::is_integral>::type>
        filtered;

    auto same = std::is_same<filtered, type_list<float, double>>::value;

    REQUIRE(same);
}


TEST_CASE("test remove_if on type_list", "[remove_if]")
{
    typedef type_list<int, float, long, double> the_list;

    typedef remove_if_t<the_list, std::is_integral> floats_left_list;

    auto same = std::is_same<floats_left_list, type_list<float, double>>::value;

    REQUIRE(same);
}


TEST_CASE("test remove on type_list", "[remove]")
{
    typedef type_list<int, float, long, double> the_list;

    typedef remove_t<the_list, float> float_removed_list;

    auto same =
        std::is_same<float_removed_list, type_list<int, long, double>>::value;

    REQUIRE(same);
}
