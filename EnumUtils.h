#pragma once

#include <cstdint>
#include <string>
#include <cstring>
#include <vector>

// These types may be chaged according to user needs

#ifndef ENUM_SIZE_TYPE
#define ENUM_SIZE_TYPE          std::size_t
#endif

#ifndef ENUM_STRING_TYPE
#define ENUM_STRING_TYPE        std::string
#endif

#ifndef ENUM_STRING_VIEW_TYPE
#define ENUM_STRING_VIEW_TYPE   std::string_view
#endif

namespace EnumUtils {

// Enumerated class base type
class EnumBase
{
public:
    // Enable default construction for enumerated classes
    EnumBase() noexcept = default;
    ~EnumBase() noexcept = default;

    // Disable copying for enumerated classes
    EnumBase(const EnumBase&) = delete;
    EnumBase& operator = (const EnumBase&) = delete;
};

// Macro to create enumerated class; syntax: class EnumName enumerate( underlying_type, Item0, Item1, ... ItemN )
#define enumerate(underlying_t, ...) final : public ::EnumUtils::EnumBase { \
public: \
    \
    enum class Enum : underlying_t {__VA_ARGS__}; \
    \
    using underlying_type        = underlying_t; \
    using size_type              = ENUM_SIZE_TYPE; \
    using string_type            = ENUM_STRING_TYPE; \
    using string_view_type       = ENUM_STRING_VIEW_TYPE; \
    using const_iterator         = std::vector<Enum>::const_iterator; \
    using const_reverse_iterator = std::vector<Enum>::const_reverse_iterator; \
    \
    static constexpr size_type getEnumElementsCount() { \
        struct __SizeGetter{underlying_type __VA_ARGS__;}; \
        return static_cast<size_type>(sizeof(__SizeGetter) / sizeof(underlying_type)); \
    } \
    static size_type getItemsCount() { \
        return static_cast<size_type>(getItems().size()); \
    } \
    static Enum getItem(size_type _idx) { \
        return getItems().at(_idx); \
    } \
    \
    const_iterator begin() const { return getItems().cbegin(); } \
    const_iterator end() const { return getItems().cend(); } \
    const_reverse_iterator rbegin() const { return getItems().crbegin(); } \
    const_reverse_iterator rend() const { return getItems().crend(); } \
    \
    static string_view_type toString(Enum); \
    static bool fromString(Enum &, string_view_type); \
    \
private: \
    static const std::vector<Enum> & getItems(); \
    static string_view_type getItemString(size_type _idx); \
    enum __EnumPrivate : underlying_type {__VA_ARGS__}; \
}

// Macro to define enumerated class items order during iteration; syntax: declare_enum_items( EnumName, Item0, Item1, ... ItemN )
#define declare_enum_items(Type, ...) \
inline const std::vector<Type::Enum> & Type::getItems() { \
    thread_local const std::vector<__EnumPrivate> Items = { \
        __VA_ARGS__ \
    }; \
    return reinterpret_cast<const std::vector<Enum> &>(Items);\
}

#define declare_enum_string_linear_methods(Type) \
inline Type::string_view_type Type::toString(Enum _val) { \
    for(size_type i = 0; i < getItemsCount(); ++i) { \
        if(getItem(i) == _val) \
            return getItemString(i); \
    } \
    return string_view_type(); \
} \
inline bool Type::fromString(Enum & _dest, string_view_type _valStr) { \
    for(size_type i = 0; i < getItemsCount(); ++i) { \
        if(getItemString(i) == _valStr) { \
            _dest = getItem(i); \
            return true; \
        } \
    } \
    return false; \
}

// Macro to define enumerated class items string representation; syntax: declare_enum_strings( EnumName, Item0, Item1, ... ItemN )
#define declare_enum_strings(Type, ...) \
inline Type::string_view_type Type::getItemString(size_type _idx) { \
    thread_local std::vector<string_type> ItemString; \
    if(ItemString.empty()) { \
        string_type token; \
        string_type values = #__VA_ARGS__; \
        string_type::value_type prev = 0; \
        constexpr string_type::value_type delim = ','; \
        ItemString.reserve(getItemsCount()); \
        for(auto it = values.begin(); it != values.end(); ++it) { \
            if(*it == delim) { \
                ItemString.emplace_back(std::move(token)); \
                prev = delim; \
                continue; \
            } \
            else if(isblank(*it) && prev == delim) { \
                continue; \
            } \
            else if(*it != delim) { \
                token.push_back(*it); \
                prev = *it; \
            } \
        } \
        ItemString.emplace_back(std::move(token)); \
        ItemString.resize(getItemsCount()); \
    } \
    return ItemString.at(_idx); \
} \
declare_enum_string_linear_methods(Type)

#define declare_enum_strings_ex(Type, ...) \
inline Type::string_view_type Type::getItemString(size_type _idx) { \
    thread_local std::vector<string_type> ItemString; \
    if(ItemString.empty()) { \
        ItemString = {__VA_ARGS__}; \
        ItemString.resize(getItemsCount()); \
    } \
    return ItemString.at(_idx); \
} \
declare_enum_string_linear_methods(Type)

// Macro to define smart enumerated class; syntax: smart_enum( EnumName, underlying_type, Item0, Item1, ... ItemN )
// Item values are not alowed when using this macro
#define smart_enum(name, underlying_t, ...) \
class name enumerate(underlying_t, __VA_ARGS__); \
declare_enum_items(name, __VA_ARGS__); \
declare_enum_strings(name, __VA_ARGS__)

} // namespace EnumUtils


