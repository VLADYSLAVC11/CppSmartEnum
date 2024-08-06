# Cpp Smart Enum

Many times I faced situation when enums/enum classes requires additional functionality like (string convertion, iteration, etc). Most of the cases look like:
```cpp
enum Color {Red, Green, Blue};

//  Color to string convertion
std::string ColorToString(Color color) {
    switch(color) {
        case Color::Red: return "Red";
        case Color::Green: return "Green";
        case Color::Blue: return "Blue";
        default: break;
    }
    return std::string();
}

// For loop iteration over all Color elements
void ColorIteration()
{
    for(Color color = Color::Red; color <= Color::Blue; ++color) {
        ...
    }
}
```

Generaly the code for all the enums looks the same, and only in some rare cases it vary depending on item and it's string representation, or for example deprecation of some enum elements.
This inspired me to create utility for smart enum generation using C++ macro mechanism.

# Smart Enum Usage

Simple enums may be created using "smart_enum" macro:
```cpp
smart_enum(name, underlying_t, ...);
```
Such a macro requires enum name, it's underlying type and optional enum elements. This macro is general
and doesn't allow to use enum speciailized values. For specialized values another macro "enumerate" should be used.

Enum Color from previous example may be created using "smart_enum" macro next way:
```cpp
smart_enum(Color, char, Red, Green, Blue);
```
Where Color is enum name, char is underlying type, and Red, Green, Blue are enum elements. After this declaration we implicitly get class named Color and enum class Enum within that class. 

The list of methods available after "smart_enum" macro usage presented below:
```cpp
static constexpr size_type getEnumElementsCount () // returns number of enum elements
static size_type getItemsCount ()                  // returns number of active enum items
static Enum getItem (size_type _idx)               // returns enum element using index
const_iterator begin () const                      // returns enum begin iterator
const_iterator end() const                         // returns enum end iterator
const_reverse_iterator rbegin () const             // returns enum rbegin iterator
const_reverse_iterator rend() const                // returns enum rend iterator
static string_view_type toString(Enum);            // returns string representation of given element
static bool fromString(Enum &, string_view_type);  // returns true when possible to create enum from str
```

That methods give user possibility to work with enum strings and iterate over enum elements using for/while/do while and ranged based for loops.


# Extended Smart Enum Usage

It may be a situation when enum element becomes deprecated, requires some specific value, needs reverse order iteration or for example doesn't have string representation. Lets imagine such an enum using smart enums:

```cpp
class ComplexEnum enumerate(int, Item0, ItemDeprecated, Item2 = 4, Item3 = 99);
declare_enum_items(ComplexEnum, Item3, Item2, Item0);
declare_enum_strings(ComplexEnum, Item3Str, , Item0 String); // strings declaration
// or even better version
declare_enum_strings_ex(ComplexEnum, "Item3Str", "", "Item0 String"); // better strings declaration
```

From mentioned code we create enumerated class ComplexEnum with enum class Enum within it.
ItemDeprecated element became depracted, so exclude it from declare_enum_items macro, by the way items order is reversed within declare_enum_items which give us possibility to iterate over elements in reverse order excluding ItemDeprecated element. declare_enum_strings is macro that specifies string representation for already ordered elements. If string representation is not needed just keep blanc instead.

In some cases (for example big enums) linear strings comparison may affect application performance. For that case user can manualy implement toString method with switch or hash map implementation inside.
Signature of strings methods:
```cpp
EnumName::string_view_type EnumName::toString(Enum _item);
bool EnumName::fromString(Enum& _destItem, string_view_type _str);
```

# How to add to project
To use smart enums just include EnumUtils.h file to your code project. The utility is header-only.
For more examples of smart enum usage please check test.cpp file.


