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


template <std::size_t N>
struct int_spec_mock;

template <>
struct int_spec_mock<10>
{
};

template <>
struct int_spec_mock<32>
{
};

TEST_CASE("test specialization_exists", "[specialization_exists]")
{
    const auto int_spec_exists =
        metamusil::specialization_exists<spec_mock, int>::value;
    const auto double_spec_exists =
        metamusil::specialization_exists<spec_mock, double>::value;
    const auto void_spec_exists =
        metamusil::specialization_exists<spec_mock, void>::value;

    REQUIRE(int_spec_exists);
    REQUIRE(double_spec_exists == false);
    REQUIRE(void_spec_exists);
}


TEST_CASE("test integral_specialization_exists",
          "[integral_specialization_exists]")
{
    const auto spec_10_exists = metamusil::
        integral_specialization_exists<std::size_t, int_spec_mock, 10ll>::value;
    const auto spec_20_exists = metamusil::
        integral_specialization_exists<std::size_t, int_spec_mock, 20ll>::value;
    const auto spec_32_exists = metamusil::
        integral_specialization_exists<std::size_t, int_spec_mock, 32ll>::value;

    REQUIRE(spec_10_exists);
    REQUIRE(spec_20_exists == false);
    REQUIRE(spec_32_exists);
}
