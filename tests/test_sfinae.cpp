#include "catch.hpp"

#include <sfinae.hpp>


template <class T>
struct spec_mock;

template <>
struct spec_mock<int>
{
};

template <>
struct spec_mock<void>
{
};

TEST_CASE("test specialization_exists", "[specialization_exists]")
{
    auto int_spec_exists =
        metamusil::specialization_exists<spec_mock, int>::value;
    auto double_spec_exists =
        metamusil::specialization_exists<spec_mock, double>::value;
    auto void_spec_exists =
        metamusil::specialization_exists<spec_mock, void>::value;

    REQUIRE(int_spec_exists);
    REQUIRE(double_spec_exists == false);
    REQUIRE(void_spec_exists);
}
