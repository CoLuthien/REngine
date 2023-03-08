
#pragma once

#include "object.hpp"
#include "class.hpp"
#include "templates/concepts.hpp"
#include "templates/casts.hpp"

#include <iostream>

void DLLEXPORT new_object_internal(ivd::hobject* self);

template <ivd::hobject_type T, typename... Args>
T*
new_object(ivd::hobject* outer, Args... args)
{
    auto result = new T{args...};
    result->init_property(T::static_class());
    new_object_internal(result);
    return result;
}
