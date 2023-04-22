

#include "core_object/object.hpp"
#include "core_object/class.hpp"
#include "core_object/object_array.hpp"

#include <iostream>

namespace ivd
{
hobject_array* object_array = hobject_array::instance();

hclass*
hobject::static_class()
{
    return nullptr; // todo
}

bool
hobject::is_valid(hobject* ptr)
{
    if (ptr == nullptr)
    {
        return false;
    }
    return object_array->is_valid_idx(ptr->m_idx);
}

hobject::hobject()
{
}
hobject::~hobject() = default;

void
hobject::init_property(hclass* in_class)
{
    self_class = in_class;
}

COREOBJECT_API bool
hobject::is_child_of(hclass const* this_class, hclass const* other_class)
{
    for (auto const* next = this_class; next; next = next->get_super())
    {
        if (next == other_class)
        {
            return true;
        }
    }

    return false;
}

} // namespace ivd
