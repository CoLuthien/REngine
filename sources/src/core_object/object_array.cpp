
#include "object_array.hpp"
#include <iostream>
namespace ivd
{
hobject_array::hobject_array()
{
}

void
hobject_array::delete_object(hobject* object)
{
    std::size_t idx = object_to_idx(object);
    if (is_valid_idx(idx))
    {
        m_objects.at(idx) = nullptr;
        delete object;
    }
}

hobject*
hobject_array::idx_to_object(std::size_t idx)
{
    if (is_valid_idx(idx))
    {
        return m_objects.at(idx);
    }

    return nullptr;
}

std::size_t
hobject_array::object_to_idx(hobject* object)
{
    if (is_valid_idx(object->m_idx))
    {
        return object->m_idx;
    }

    return std::numeric_limits<std::size_t>::max();
}
void
hobject_array::insert_object(hobject* object)
{
    object->m_idx  = get_index();
    auto const idx = object->m_idx;

    if (m_objects.size() == idx || m_objects.empty())
    {
        m_objects.emplace_back(object);
    }
    else
    {
        assert(m_objects.at(idx) == nullptr);
        m_objects.at(idx) = object;
    }

    return;
}

std::size_t
hobject_array::get_index()
{
    std::size_t result;
    if (idx_pool.empty())
    {
        result = idx_end;
        idx_end++;
    }
    else
    {
        result = idx_pool.extract(idx_pool.begin()).value();
    }
    idx_used.emplace(result);
    return result;
}

void
hobject_array::return_index(std::size_t idx)
{
    if (idx_used.contains(idx))
    {
        idx_used.extract(idx);
        idx_pool.emplace(idx);
    }
}
bool
hobject_array::is_valid_idx(std::size_t idx)
{
    if (idx_used.contains(idx) == false || idx > m_objects.size())
    {
        std::cout << idx << '\t' << m_objects.size() << '\n';
        return false;
    }

    return true;
}
} // namespace ivd
