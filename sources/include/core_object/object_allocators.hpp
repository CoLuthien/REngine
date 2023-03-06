
#pragma once

#include "object.hpp"
#include "class.hpp"
#include "templates/concepts.hpp"
#include "templates/casts.hpp"

template <ivd::hobject_type T, typename... Args>
T*
new_object(ivd::hobject_t* outer, Args... args)
{
    auto result = new T{args...};

    result->init_property(T::static_class());

    return result;
}

