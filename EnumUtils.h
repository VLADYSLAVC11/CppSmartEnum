#pragma once

#include <cstdint>
#include <string>
#include <cstring>
#include <vector>
#include <stdexcept>

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
    using underlying_type   = underlying_t; \
    using size_type         = ENUM_SIZE_TYPE; \
    using string_type       = ENUM_STRING_TYPE; \
    using string_view_type  = ENUM_STRING_VIEW_TYPE; \
    \
    enum class Enum : underlying_type {__VA_ARGS__}; \
    \
    static constexpr size_type getItemsCount() { \
        struct __SizeGetter{underlying_type __VA_ARGS__;}; \
        return sizeof(__SizeGetter) / sizeof(underlying_type); \
    } \
    static Enum getItem(size_type _idx) { \
        if(_idx >= getItemsCount()) \
            throw std::out_of_range("Enum index out of range"); \
        return *(getItems() + _idx); \
    } \
    \
    const Enum * begin() const { return getItems(); } \
    const Enum * end() const { return getItems() + getItemsCount(); } \
    \
    static string_view_type toString(Enum); \
    static bool fromString(Enum &, string_view_type); \
    \
private: \
    static const Enum * getItems(); \
    static string_view_type getItemString(size_type _idx); \
    enum __EnumPrivate : underlying_type {__VA_ARGS__}; \
}

// Macro to define enumerated class items order during iteration; syntax: declare_enum_items( EnumName, Item0, Item1, ... ItemN )
#define declare_enum_items(Type, ...) \
inline const Type::Enum * Type::getItems() { \
    thread_local const __EnumPrivate Items[] = { \
        __VA_ARGS__ \
    }; \
    return reinterpret_cast<const Type::Enum *>(Items);\
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
    } \
    return ItemString.at(_idx); \
}\
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

// Macro to define smart enumerated class; syntax: smart_enum( EnumName, underlying_type, Item0, Item1, ... ItemN )
// Item values are not alowed when using this macro
#define smart_enum(name, underlying_t, ...) \
class name enumerate(underlying_t, __VA_ARGS__); \
declare_enum_items(name, __VA_ARGS__); \
declare_enum_strings(name, __VA_ARGS__)

} // namespace EnumUtils


