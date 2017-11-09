#include "catch.hpp"

#include <type_descriptor.hpp>


TEST_CASE("decompose types to type_descriptors", "[type_descriptor]")
{
    using namespace metamusil::t_descriptor;


    typedef decompose_t<int> int_desc;
    typedef decompose_t<const int*> ptr_const_int_desc;

    typedef decompose_t<int*&> lref_ptr_int_desc;
    typedef decompose_t<const int* const&> lref_const_ptr_const_int_desc;

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


    CHECK(int_check);
    CHECK(ptr_const_int_check);
    CHECK(lref_ptr_int_check);
    CHECK(lref_const_ptr_const_int_check);
}
