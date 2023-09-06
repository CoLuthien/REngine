
#pragma once

#include "templates/concepts.hpp"
#include "object_macros.hpp"
#include "object_globals.hpp"
#include "core_object/definitions.hpp"
#include <cstddef>

namespace ivd
{
class hclass;
class hobject;

} // namespace ivd

namespace ivd
{

class COREOBJECT_API hobject
{
    friend class hobject_array;
    friend class garbage_collector;

public:
    GENERATE_HOBJECT_BODY();

public:
    hobject();
    virtual ~hobject();

public:
    void    init_property(hclass* in_class);
    hclass* get_class() const noexcept { return self_class; }

public:
    static bool is_valid(hobject* ptr);
    void        set_flags(object_flag const flag) { m_flag = m_flag | flag; }
    void        clear_flags(object_flag const flag) { m_flag = m_flag & ~flag; }
    object_flag get_flag() const { return m_flag; }

public: // safe fast runtime cast impl starts
    template <typename T>
    inline bool is_a()
    {
        return is_child_of(get_class(), T::static_class());
    }

    template <typename T>
    inline bool is_a(T* other)
    {
        if (other == nullptr)
        {
            return false;
        }

        auto const* this_class  = get_class();
        auto const* other_class = other->get_class();

        return is_child_of(this_class, other_class);
    }

private:
    bool is_child_of(hclass const* this_class, hclass const* other_class);

private:
    std::size_t m_idx;
    object_flag m_flag = eobject_flag::UNREACHABLE;
    hclass*     self_class;
};

} // namespace ivd
