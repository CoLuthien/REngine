
#pragma once

#include "plate/definitions.hpp"
#include "plate_types.hpp"

#include "plate_core/reply.hpp"

#include <memory>

namespace ivd::plate
{
class composite_base;

PLATE_API void initialize();

class PLATE_API plate : std::enable_shared_from_this<plate>
{
public:
    virtual reply click(/*todo*/) { return {}; }
    virtual reply key(/*todo*/) { return {}; }

    virtual void arrange(/*todo*/) {}
    virtual void draw(/*todo*/) {}

    template <typename... Es>
    constexpr void      content(Es&&... elements);
    inline virtual void content(std::initializer_list<std::shared_ptr<plate>> list) = 0;

public:
    virtual composite_base* get_composite() = 0;

private:
};

template <typename... Es>
constexpr void
plate::content(Es&&... elements)
{
    content(std::forward<Es>(elements)...);
}

} // namespace ivd::plate

namespace ivd
{
using plate_ptr = std::shared_ptr<plate::plate>;
}