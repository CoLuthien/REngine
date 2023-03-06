
#pragma once
#include <iostream>

#include "templates/concepts.hpp"
#include "object_macros.hpp"

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
class hobject_t;

} // namespace ivd

namespace ivd
{

class DLLEXPORT hobject_t
{
public:
    GENERATE_HOBJECT_BODY();

public:
    hobject_t()          = default;
    virtual ~hobject_t() = default;

    void init_property(hclass_t* in_class);
    hclass_t const* get_class() const noexcept { return self_class; }

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
    bool is_child_of(hclass_t const* this_class, hclass_t const* other_class);

private:
    eobject_flag m_flag;
    hclass_t* self_class;
};

} // namespace ivd
