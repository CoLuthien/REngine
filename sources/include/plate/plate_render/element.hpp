
#pragma once

#include "utils/non_copyable.hpp"
#include "math/point.hpp"
#include "math/extent.hpp"
#include "plate/definitions.hpp"

#include <memory>
#include <vector>

namespace ivd::plate
{
class element_info;

enum class drawable_type_e
{
    BOX,
    LINE,
};

class element : non_copyable
{
public:
    element();
    virtual ~element();

public:
    template <typename InfoType>
    inline InfoType const* get_info() const
    {
        return static_cast<InfoType const*>(info.get());
    }

    template <typename InfoType>
    inline InfoType* get_info()
    {
        return static_cast<InfoType*>(info.get());
    }

private:
    std::unique_ptr<element_info> info;
    drawable_type_e               type;

private:
    point2_f    location;
    extent2_f   size;
    std::size_t layer_id;
};

class element_list : non_copyable
{
public:
    void add_drawble(element&& element);

private:
    std::vector<element> drawables;
};

} // namespace ivd::plate