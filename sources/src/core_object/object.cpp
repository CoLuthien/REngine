

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


} // namespace ivd
