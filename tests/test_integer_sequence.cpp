#include "catch.hpp"

#include <type_traits>

#include <integer_sequence.hpp>

template <std::size_t N>
struct is4 : std::false_type
{
};

template <>
struct is4<4> : std::true_type
{
};

template <std::size_t N>
struct is_odd
{
    static const bool value = N % 2;
};

TEST_CASE("test int_seq::append", "[int_seq::append]")
{
    typedef std::integer_sequence<long> empty_sequence;
    typedef std::integer_sequence<int, 0, 1, 2> start_sequence;
    typedef std::index_sequence<2, 3, 4> start_index_sequence;

    SECTION("append 10 to start_sequence")
    {
        typedef metamusil::int_seq::append_t<start_sequence, 10> appended;

        auto same =
            std::is_same<appended,
                         std::integer_sequence<int, 0, 1, 2, 10>>::value;

        REQUIRE(same);
    }

    SECTION("append 100 to empty_sequence")
    {
        typedef metamusil::int_seq::append_t<empty_sequence, 100> appended;

        auto same =
            std::is_same<appended, std::integer_sequence<long, 100>>::value;

        REQUIRE(same);
    }

    SECTION("append 5 to a std::index_sequence")
    {
        typedef metamusil::int_seq::append_t<start_index_sequence, 5> appended;

        auto same =
            std::is_same<appended, std::index_sequence<2, 3, 4, 5>>::value;

        REQUIRE(same);
    }
}


TEST_CASE("test integer_sequence_from_range", "[integer_sequence_from_range]")
{
    typedef metamusil::int_seq::integer_sequence_from_range_t<std::size_t, 2, 5>
        from2until5;

    typedef metamusil::int_seq::integer_sequence_from_range_t<int, 3, 3>
        from3until3;

    typedef metamusil::int_seq::integer_sequence_from_range_t<int, -2, 3>
        from_minus2until2;

    typedef metamusil::int_seq::integer_sequence_from_range_t<std::size_t, 4, 5>
        from4until5;

    auto same = std::is_same<from2until5, std::index_sequence<2, 3, 4>>::value;
    auto same2 = std::is_same<from3until3, std::integer_sequence<int>>::value;
    auto same3 =
        std::is_same<from_minus2until2,
                     std::integer_sequence<int, -2, -1, 0, 1, 2>>::value;
    auto same4 = std::is_same<from4until5, std::index_sequence<4>>::value;

    REQUIRE(same);
    REQUIRE(same2);
    REQUIRE(same3);
    REQUIRE(same4);
}


TEST_CASE("test append_if on integer_sequence", "[append_if]")
{
    typedef std::index_sequence<0, 1, 2, 3> start_sequence;

    SECTION("attempt to append 5")
    {
        typedef metamusil::int_seq::append_if_t<start_sequence, 5, is4> result;

        auto same = std::is_same<result, start_sequence>::value;

        REQUIRE(same);
    }

    SECTION("attempt to append 4")
    {
        typedef metamusil::int_seq::append_if_t<start_sequence, 4, is4> result;

        auto same =
            std::is_same<result, std::index_sequence<0, 1, 2, 3, 4>>::value;

        REQUIRE(same);
    }
}


TEST_CASE("test filter on integer_sequence", "[filter]")
{
    typedef std::make_index_sequence<6> start_sequence;

    typedef metamusil::int_seq::filter_t<start_sequence, is_odd> result;

    auto isodd = is_odd<1>::value;
    auto isodd2 = is_odd<2>::value;

    auto same = std::is_same<result, std::index_sequence<1, 3, 5>>::value;

    REQUIRE(isodd);
    REQUIRE(isodd2 == false);
    REQUIRE(same);
}
