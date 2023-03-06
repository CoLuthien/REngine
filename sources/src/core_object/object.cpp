

#include "core_object/object.hpp"
#include "core_object/class.hpp"
#include "core_object/garbage_collection.hpp"

namespace ivd
{
hclass_t*
hobject_t::static_class()
{
    return nullptr; // todo
}

void 
hobject_t::init_property(hclass_t* in_class)
{
    self_class = in_class;
}

bool
hobject_t::is_child_of(hclass_t const* this_class, hclass_t const* other_class)
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
