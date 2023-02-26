
#pragma once

#include "templates/concepts.hpp"
#include "reflection/reflection.hpp"

#include "meta/type_list.hpp"
#include "HAL/platforms.hpp"
#include <cstddef>

enum eobject_flag
{
    REFL_TYPE    = 1 << 0,
    UNREACHABLE  = 1 << 1,
    PENDING_KILL = 1 << 2,
    ROOT_OBJECT  = 1 << 3,
};
namespace ivd
{

class hclass_t;

class DLLEXPORT hobject_t
{
public:
    GENERATE_HOBJECT_BODY();

public:
    hobject_t();

    virtual hclass_t const* get_class() const;

public: // safe fast runtime cast impl starts
    template <hobject_type T>
    inline bool is_a()
    {
        return is_child_of(get_class(), T::static_class());
    }

    inline bool is_a(hclass_t* other) { return get_class() == other; }

    template <hobject_type T>
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
    bool is_child_of(hclass_t const* this_class, hclass_t const* other_class);

private:
    eobject_flag m_flag;

private:
    std::size_t m_gcidx;
};

} // namespace ivd
