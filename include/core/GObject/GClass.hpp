
#pragma once

#include "Reflection/Reflection.hpp"
#include "GObject.hpp"
#include <unordered_map>

namespace ge
{
class GField
{
    GField(refl::RField* Field);

private:
    refl::RField* m_info;
};

class GFunction
{
    GFunction(refl::RFunction*);

private:
    refl::RFunction* m_info;
};

class GClass
{
    using function_container = std::unordered_map<std::string_view, GFunction*>;

public:
    GClass(refl::RClass*);
    class GFunction* find_function(std::string_view const name) { return nullptr; }

private:
    refl::RClass* m_info;
};

} // namespace  ge
#define REFLECT_CLASS()                                                                  \
    DECLARE_TYPE();                                                                      \
                                                                                         \
private:                                                                                 \
    static refl::RClass* reflected_class()                                               \
    {                                                                                    \
        static constexpr auto type = refl::RClass::make_reflection<this_type>();         \
        return const_cast<refl::RClass*>(&type);                                         \
    }                                                                                    \
    static ge::GClass* static_class()                                                    \
    {                                                                                    \
        static auto const Instance = ge::GClass(reflected_class());                      \
        return const_cast<ge::GClass*>(&Instance);                                       \
    }
