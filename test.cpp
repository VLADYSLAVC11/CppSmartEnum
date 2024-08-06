
#include <cassert>
#include <type_traits>
#include "EnumUtils.h"

class TestEnumWithoutValues enumerate(int, Item0, Item1, Item2);
declare_enum_items(TestEnumWithoutValues, Item0, Item1, Item2);
void test_enumeration_without_values()
{
    assert(TestEnumWithoutValues::getEnumElementsCount() == 3);
    assert(TestEnumWithoutValues::getItemsCount() == 3);
}

class TestEnumWithValues enumerate(int, Item0, Item1 = 5, Item2, Item4 = 99);
declare_enum_items(TestEnumWithValues, Item0, Item1, Item2, Item4);
void test_enumeration_with_values()
{
    assert(TestEnumWithValues::getEnumElementsCount() == 4);
    assert(TestEnumWithValues::getItemsCount() == 4);

    assert(static_cast<int>(TestEnumWithValues::Enum::Item0) == 0);
    assert(static_cast<int>(TestEnumWithValues::Enum::Item1) == 5);
    assert(static_cast<int>(TestEnumWithValues::Enum::Item2) == 6);
    assert(static_cast<int>(TestEnumWithValues::Enum::Item4) == 99);
}

class TestEnumUnderlyingType enumerate(std::uint8_t, Item0);
declare_enum_items(TestEnumUnderlyingType, Item0);
void test_enumeration_underlying_type()
{
    assert(TestEnumUnderlyingType::getEnumElementsCount() == 1);
    assert(TestEnumUnderlyingType::getItemsCount() == 1);

    assert(sizeof(TestEnumUnderlyingType::Enum) == 1);
    const bool same_type = std::is_same<TestEnumUnderlyingType::underlying_type, std::uint8_t>::value;
    assert(same_type && "Type is not std::uint8_t");
}

class TestEnumGetItems enumerate(int, Item0, Item1, Item2, Item3);
declare_enum_items(TestEnumGetItems, Item0, Item1, Item2, Item3);
void test_enumeration_get_items()
{
    assert(TestEnumGetItems::getEnumElementsCount() == 4);
    assert(TestEnumGetItems::getItemsCount() == 4);

    for(size_t idx = 0; idx < TestEnumGetItems::getItemsCount(); ++idx)
    {
        if(idx == 0) {assert(TestEnumGetItems::getItem(idx) == TestEnumGetItems::Enum::Item0);}
        if(idx == 1) {assert(TestEnumGetItems::getItem(idx) == TestEnumGetItems::Enum::Item1);}
        if(idx == 2) {assert(TestEnumGetItems::getItem(idx) == TestEnumGetItems::Enum::Item2);}
        if(idx == 3) {assert(TestEnumGetItems::getItem(idx) == TestEnumGetItems::Enum::Item3);}
    }
}

class TestEnumItemsDeprecated enumerate(int, Item0, Item1, Item2, Item3);
declare_enum_items(TestEnumItemsDeprecated, Item0, Item3); // Items 1 and 2 are deprecated
void test_enumeration_deprecated_items()
{
    assert(TestEnumItemsDeprecated::getEnumElementsCount() == 4);
    assert(TestEnumItemsDeprecated::getItemsCount() == 2);

    for(size_t idx = 0; idx < TestEnumItemsDeprecated::getItemsCount(); ++idx)
    {
        if(idx == 0) {assert(TestEnumItemsDeprecated::getItem(idx) == TestEnumItemsDeprecated::Enum::Item0);}
        if(idx == 1) {assert(TestEnumItemsDeprecated::getItem(idx) == TestEnumItemsDeprecated::Enum::Item3);}
    }
}

class TestEnumRangeBased enumerate(std::uint8_t, Item0 = 10, Item1, Item2);
declare_enum_items(TestEnumRangeBased, Item0, Item1, Item2);
void test_enum_items_iteration_range_based()
{
    assert(TestEnumRangeBased::getEnumElementsCount() == 3);
    assert(TestEnumRangeBased::getItemsCount() == 3);

    int i = 0;
    for(auto item : TestEnumRangeBased())
    {
        if(i == 0) {assert(item == TestEnumRangeBased::Enum::Item0);}
        if(i == 1) {assert(item == TestEnumRangeBased::Enum::Item1);}
        if(i == 2) {assert(item == TestEnumRangeBased::Enum::Item2);}
        ++i;
    }
}

class TestEnumRangeBasedReversed enumerate(std::uint8_t, Item0, Item1, Item2);
declare_enum_items(TestEnumRangeBasedReversed, Item2, Item1, Item0);
void test_enum_items_iteration_range_based_reversed_order()
{
    assert(TestEnumRangeBasedReversed::getEnumElementsCount() == 3);
    assert(TestEnumRangeBasedReversed::getItemsCount() == 3);

    int i = 0;
    for(auto item : TestEnumRangeBasedReversed())
    {
        if(i == 0) {assert(item == TestEnumRangeBasedReversed::Enum::Item2);}
        if(i == 1) {assert(item == TestEnumRangeBasedReversed::Enum::Item1);}
        if(i == 2) {assert(item == TestEnumRangeBasedReversed::Enum::Item0);}
        ++i;
    }
}

class TestEnumIterators enumerate(std::uint8_t, Item0, Item1, Item2, Item3, Item4);
declare_enum_items(TestEnumIterators, Item0, Item1, Item2, Item3, Item4);
void test_enum_items_iterators()
{
    assert(TestEnumIterators::getEnumElementsCount() == 5);
    assert(TestEnumIterators::getItemsCount() == 5);

    int i = 0;
    for(auto it = TestEnumIterators().begin(); it != TestEnumIterators().end(); ++it)
    {
        if(i == 0) {assert(*it == TestEnumIterators::Enum::Item0);}
        if(i == 1) {assert(*it == TestEnumIterators::Enum::Item1);}
        if(i == 2) {assert(*it == TestEnumIterators::Enum::Item2);}
        if(i == 3) {assert(*it == TestEnumIterators::Enum::Item3);}
        if(i == 4) {assert(*it == TestEnumIterators::Enum::Item4);}
        ++i;
    }
}

void test_enum_items_iterators_reversed()
{
    int i = 0;
    for(auto it = TestEnumIterators().end() - 1; it >= TestEnumIterators().begin(); --it)
    {
        if(i == 0) {assert(*it == TestEnumIterators::Enum::Item4);}
        if(i == 1) {assert(*it == TestEnumIterators::Enum::Item3);}
        if(i == 2) {assert(*it == TestEnumIterators::Enum::Item2);}
        if(i == 3) {assert(*it == TestEnumIterators::Enum::Item1);}
        if(i == 4) {assert(*it == TestEnumIterators::Enum::Item0);}
        ++i;
    }

    i = 0;
    for(auto rit = TestEnumIterators().rbegin(); rit != TestEnumIterators().rend(); ++rit)
    {
        if(i == 0) {assert(*rit == TestEnumIterators::Enum::Item4);}
        if(i == 1) {assert(*rit == TestEnumIterators::Enum::Item3);}
        if(i == 2) {assert(*rit == TestEnumIterators::Enum::Item2);}
        if(i == 3) {assert(*rit == TestEnumIterators::Enum::Item1);}
        if(i == 4) {assert(*rit == TestEnumIterators::Enum::Item0);}
        ++i;
    }
}

class TestEnumToString enumerate(std::uint32_t, Item0, Item1, Item2);
declare_enum_items(TestEnumToString, Item0, Item1, Item2);
declare_enum_strings(TestEnumToString, Test0, Test1, Test2);
void test_enum_to_string()
{
    assert(TestEnumToString::getEnumElementsCount() == 3);
    assert(TestEnumToString::getItemsCount() == 3);

    assert(TestEnumToString::toString(TestEnumToString::Enum::Item0) == "Test0");
    assert(TestEnumToString::toString(TestEnumToString::Enum::Item1) == "Test1");
    assert(TestEnumToString::toString(TestEnumToString::Enum::Item2) == "Test2");
}

class TestEnumWithoutSomeStrings enumerate(std::uint32_t, Item0, Item1, Item2, Item3);
declare_enum_items(TestEnumWithoutSomeStrings, Item0, Item1, Item2, Item3);
declare_enum_strings(TestEnumWithoutSomeStrings, Str0, , , Str3);
void test_enum_without_some_strings()
{
    assert(TestEnumWithoutSomeStrings::getEnumElementsCount() == 4);
    assert(TestEnumWithoutSomeStrings::getItemsCount() == 4);

    assert(TestEnumWithoutSomeStrings::toString(TestEnumWithoutSomeStrings::Enum::Item0) == "Str0");
    assert(TestEnumWithoutSomeStrings::toString(TestEnumWithoutSomeStrings::Enum::Item1) == "");
    assert(TestEnumWithoutSomeStrings::toString(TestEnumWithoutSomeStrings::Enum::Item2) == "");
    assert(TestEnumWithoutSomeStrings::toString(TestEnumWithoutSomeStrings::Enum::Item3) == "Str3");
}

class TestEnumNonDeclaredItemString enumerate(int, Item = 4);
declare_enum_items(TestEnumNonDeclaredItemString, Item);
declare_enum_strings(TestEnumNonDeclaredItemString, Item);
void test_non_declared_enum_item_string()
{
    assert(TestEnumNonDeclaredItemString::getEnumElementsCount() == 1);
    assert(TestEnumNonDeclaredItemString::getItemsCount() == 1);

    const auto non_declared_item = static_cast<TestEnumNonDeclaredItemString::Enum>(0);
    assert(TestEnumNonDeclaredItemString::toString(non_declared_item) == "");
}

class TestEnumFromString enumerate(int, Item0, Item1, Item2);
declare_enum_items(TestEnumFromString, Item0, Item1, Item2);
declare_enum_strings(TestEnumFromString, Item0, Item1, Item2);
void test_enum_from_string()
{
    assert(TestEnumFromString::getEnumElementsCount() == 3);
    assert(TestEnumFromString::getItemsCount() == 3);

    TestEnumFromString::Enum elem0, elem1, elem2;
    assert(TestEnumFromString::fromString(elem0, "Item0"));
    assert(TestEnumFromString::fromString(elem1, "Item1"));
    assert(TestEnumFromString::fromString(elem2, "Item2"));
    assert(elem0 == TestEnumFromString::Enum::Item0);
    assert(elem1 == TestEnumFromString::Enum::Item1);
    assert(elem2 == TestEnumFromString::Enum::Item2);
}

class TestEnumFromUnknownString enumerate(int, Item);
declare_enum_items(TestEnumFromUnknownString, Item);
declare_enum_strings(TestEnumFromUnknownString, Item);
void test_enum_from_unknown_string()
{
    assert(TestEnumFromUnknownString::getEnumElementsCount() == 1);
    assert(TestEnumFromUnknownString::getItemsCount() == 1);

    TestEnumFromString::Enum elem;
    assert(!TestEnumFromString::fromString(elem, "Unknown"));
}

class TestEnumStringEx enumerate(int, Item0, Item1, Item2, Item3);
declare_enum_items(TestEnumStringEx, Item0, Item1, Item2);
declare_enum_strings_ex(TestEnumStringEx, "Item0", "Item1");
void test_enum_strings_ex()
{
    assert(TestEnumStringEx::getEnumElementsCount() == 4);
    assert(TestEnumStringEx::getItemsCount() == 3);

    assert(TestEnumStringEx::toString(TestEnumStringEx::Enum::Item0) == "Item0");
    assert(TestEnumStringEx::toString(TestEnumStringEx::Enum::Item1) == "Item1");
    assert(TestEnumStringEx::toString(TestEnumStringEx::Enum::Item2) == "");
}

smart_enum(EAnimal, long long, Cat, Dog, Chicken);
void test_smart_enum_macro()
{
    assert(EAnimal::getEnumElementsCount() == 3);
    assert(EAnimal::getItemsCount() == 3);

    bool is_same_underlying_type = std::is_same<EAnimal::underlying_type, long long>::value;
    assert(is_same_underlying_type);
    assert(sizeof(EAnimal::Enum) == sizeof(long long));

    assert(static_cast<long long>(EAnimal::Enum::Cat) == 0);
    assert(static_cast<long long>(EAnimal::Enum::Dog) == 1);
    assert(static_cast<long long>(EAnimal::Enum::Chicken) == 2);

    int i = 0;
    for(auto item : EAnimal())
    {
        if(i == 0) {assert(item == EAnimal::Enum::Cat);}
        if(i == 1) {assert(item == EAnimal::Enum::Dog);}
        if(i == 2) {assert(item == EAnimal::Enum::Chicken);}
        ++i;
    }

    assert(EAnimal::toString(EAnimal::Enum::Cat) == "Cat");
    assert(EAnimal::toString(EAnimal::Enum::Dog) == "Dog");
    assert(EAnimal::toString(EAnimal::Enum::Chicken) == "Chicken");

    EAnimal::Enum cat, dog, chicken;
    assert(EAnimal::fromString(cat, "Cat"));
    assert(EAnimal::fromString(dog, "Dog"));
    assert(EAnimal::fromString(chicken, "Chicken"));

    assert(cat == EAnimal::Enum::Cat);
    assert(dog == EAnimal::Enum::Dog);
    assert(chicken == EAnimal::Enum::Chicken);
}

class TestEnumWithFastStringsImpl enumerate(int, Item0, Item1, Item2, Item3);
declare_enum_items(TestEnumWithFastStringsImpl, Item0, Item1, Item2, Item3);

// For enums where element to string function should work constantly
std::string_view TestEnumWithFastStringsImpl::toString(Enum val)
{
    switch(val)
    {
        case Enum::Item0: return "Item0";
        case Enum::Item1: return "Item1";
        case Enum::Item2: return "Item2";
        case Enum::Item3: return "Item3";
        default: break;
    }

    return std::string_view();
}

void test_enum_with_fast_to_string_impl()
{
    assert(TestEnumWithFastStringsImpl::getEnumElementsCount() == 4);
    assert(TestEnumWithFastStringsImpl::getItemsCount() == 4);

    assert(TestEnumWithFastStringsImpl::toString(TestEnumWithFastStringsImpl::Enum::Item0) == "Item0");
    assert(TestEnumWithFastStringsImpl::toString(TestEnumWithFastStringsImpl::Enum::Item1) == "Item1");
    assert(TestEnumWithFastStringsImpl::toString(TestEnumWithFastStringsImpl::Enum::Item2) == "Item2");
    assert(TestEnumWithFastStringsImpl::toString(TestEnumWithFastStringsImpl::Enum::Item3) == "Item3");
}

int main()
{
    test_enumeration_without_values();
    test_enumeration_with_values();
    test_enumeration_underlying_type();
    test_enumeration_get_items();
    test_enumeration_deprecated_items();
    test_enum_items_iteration_range_based();
    test_enum_items_iteration_range_based_reversed_order();
    test_enum_items_iterators();
    test_enum_items_iterators_reversed();
    test_enum_to_string();
    test_enum_without_some_strings();
    test_non_declared_enum_item_string();
    test_enum_from_string();
    test_enum_strings_ex();
    test_enum_from_unknown_string();
    test_smart_enum_macro();
    test_enum_with_fast_to_string_impl();
    return 0;
}
