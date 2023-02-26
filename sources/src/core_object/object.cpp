

#include "core_object/object.hpp"
#include "core_object/class.hpp"
#include "core_object/garbage_collection.hpp"

namespace ivd
{
hobject_t::hobject_t() = default;

hclass_t*
hobject_t::static_class()
{
    return nullptr; // todo
}

hclass_t const*
hobject_t::get_class() const
{
    return static_class();
}

bool
hobject_t::is_child_of(hclass_t const* this_class, hclass_t const* other_class)
{
    for (auto* next = this_class; next; next = next->get_super())
    {
        if (next == other_class)
        {
            return true;
        }
    }

    return false;
}

} // namespace ivd
