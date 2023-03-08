
#include "garbage_collection/garbage_collection.hpp"

#include "core_object/object.hpp"
#include "core_object/object_array.hpp"
#include <iostream>

namespace ivd
{
static hobject_array* object_array = hobject_array::instance();

static void
mark(hobject* object)
{
    using efield_type = refl::efield_type;

    if (hobject::is_valid(object) == false)
    {
        return;
    }
    auto* cls          = object->get_class();
    auto const& fields = cls->get_fields();

    object->clear_flags(eobject_flag::UNREACHABLE);

    for (auto& [name, field] : fields)
    {
        auto const type = field.get_type();
        if (type == efield_type::REFLECTED_PTR)
        {
            auto obj_ptr = field.get<hobject*>(object);
            mark(obj_ptr);
        }
        else
        {
            // do nothing
        }
    }
}

void
garbage_collector::mark_objects()
{
    for (auto const idx : m_rootset)
    {
        hobject* cur = object_array->idx_to_object(idx);
        if (cur && hobject::is_valid(cur))
        {
            mark(cur);
        }
    }
}

void
garbage_collector::sweep_objects()
{
    auto const& idxs = object_array->get_objects();
    std::vector<std::size_t> idx_to_remove{};

    for (auto idx : idxs)
    {
        auto object = object_array->idx_to_object(idx);

        bool is_reachable = (object->get_flag() & eobject_flag::UNREACHABLE) == 0;

        if (is_reachable)
        {
            object->set_flags(eobject_flag::UNREACHABLE);
            continue;
        }
        else
        {
            object_array->delete_object(object);
            idx_to_remove.emplace_back(idx);
        }
    }

    for (auto idx : idx_to_remove)
    {
        object_array->return_index(idx);
    }
}

void
garbage_collector::add_to_root(hobject* obj)
{
    std::size_t idx = object_array->object_to_idx(obj);
    if (object_array->is_valid_idx(idx))
    {
        m_rootset.emplace_back(idx);
    }
}

} // namespace ivd