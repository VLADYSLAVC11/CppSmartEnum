
#include <cassert>
#include <type_traits>
#include "EnumUtils.h"

void test_enumeration_without_values()
{
    class TestEnum enumerate(int, Item0, Item1, Item2);
    assert(TestEnum::getItemsCount() == 3);
}

void test_enumeration_with_values()
{
    class TestEnum enumerate(int, Item0, Item1 = 5, Item2, Item4 = 99);
    assert(TestEnum::getItemsCount() == 4);
    assert(static_cast<int>(TestEnum::Enum::Item0) == 0);
    assert(static_cast<int>(TestEnum::Enum::Item1) == 5);
    assert(static_cast<int>(TestEnum::Enum::Item2) == 6);
    assert(static_cast<int>(TestEnum::Enum::Item4) == 99);
}

void test_enumeration_underlying_type()
{
    class TestEnum enumerate(std::uint8_t, Item0);
    assert(TestEnum::getItemsCount() == 1);
    assert(sizeof(TestEnum::Enum) == 1);
    const bool same_type = std::is_same<TestEnum::underlying_type, std::uint8_t>::value;
    assert(same_type);
}

class TestEnumRangeBased enumerate(std::uint8_t, Item0 = 10, Item1, Item2);
declare_enum_items(TestEnumRangeBased, Item0, Item1, Item2);
void test_enum_items_iteration_range_based()
{
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
}

class TestEnumToString enumerate(std::uint32_t, Item0, Item1, Item2);
declare_enum_items(TestEnumToString, Item0, Item1, Item2);
declare_enum_strings(TestEnumToString, Test0, Test1, Test2);
void test_enum_to_string()
{
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
    assert(TestEnumNonDeclaredItemString::getItemsCount() == 1);

    const auto non_declared_item = static_cast<TestEnumNonDeclaredItemString::Enum>(0);
    assert(TestEnumNonDeclaredItemString::toString(non_declared_item) == "");
}

class TestEnumFromString enumerate(int, Item0, Item1, Item2);
declare_enum_items(TestEnumFromString, Item0, Item1, Item2);
declare_enum_strings(TestEnumFromString, Item0, Item1, Item2);
void test_enum_from_string()
{
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
    assert(TestEnumFromUnknownString::getItemsCount() == 1);

    TestEnumFromString::Enum elem;
    assert(!TestEnumFromString::fromString(elem, "Unknown"));
}

smart_enum(EAnimal, long long, Cat, Dog, Chicken);
void test_smart_enum_macro()
{
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

int main()
{
    test_enumeration_without_values();
    test_enumeration_with_values();
    test_enumeration_underlying_type();
    test_enum_items_iteration_range_based();
    test_enum_items_iteration_range_based_reversed_order();
    test_enum_items_iterators();
    test_enum_items_iterators_reversed();
    test_enum_to_string();
    test_enum_without_some_strings();
    test_non_declared_enum_item_string();
    test_enum_from_string();
    test_enum_from_unknown_string();
    test_smart_enum_macro();
    return 0;
}
