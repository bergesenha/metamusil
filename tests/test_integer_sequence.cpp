#include "catch.hpp"

#include <integer_sequence.hpp>


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
