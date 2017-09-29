#include "catch.hpp"

#include <type_traits>
#include <misc.hpp>


TEST_CASE("test base on different types", "[base]")
{
    constexpr auto is_same1 = std::is_same<metamusil::base_t<int*>, int>::value;
    constexpr auto is_same2 =
        std::is_same<metamusil::base_t<int**>, int>::value;
    constexpr auto is_same3 =
        std::is_same<metamusil::base_t<int*******>, int>::value;

    constexpr auto is_same4 =
        std::is_same<metamusil::base_t<const int>, int>::value;

    constexpr auto is_same5 =
        std::is_same<metamusil::base_t<const int*>, int>::value;

    constexpr auto is_same6 =
        std::is_same<metamusil::base_t<const int* const>, int>::value;

    constexpr auto is_same7 = std::is_same<metamusil::base_t<int&>, int>::value;
    constexpr auto is_same8 =
        std::is_same<metamusil::base_t<int&&>, int>::value;

    constexpr auto is_same9 =
        std::is_same<metamusil::base_t<const int&>, int>::value;

    constexpr auto is_same10 =
        std::is_same<metamusil::base_t<int*&>, int>::value;

    constexpr auto is_same11 =
        std::is_same<metamusil::base_t<const int* const&>, int>::value;

    REQUIRE(is_same1);
    REQUIRE(is_same2);
    REQUIRE(is_same3);
    REQUIRE(is_same4);
    REQUIRE(is_same5);
    REQUIRE(is_same6);
    REQUIRE(is_same7);
    REQUIRE(is_same8);
    REQUIRE(is_same9);
    REQUIRE(is_same10);
    REQUIRE(is_same11);
}

