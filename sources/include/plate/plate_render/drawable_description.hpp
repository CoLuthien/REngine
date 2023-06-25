
#pragma once

#include "utils/non_copyable.hpp"
#include "math/point.hpp"
#include "math/extent.hpp"
#include "plate/definitions.hpp"

#include <memory>
#include <vector>

namespace ivd::plate
{
class drawable_info;

enum class drawable_type_e
{
    BOX,
    LINE,
};

class drawable_description : non_copyable
{
public:
    drawable_description();
    virtual ~drawable_description();

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
    std::unique_ptr<drawable_info> info;
    drawable_type_e               type;

private:
    point2_f    location;
    extent2_f   size;
    std::size_t layer_id;
};

class drawable_description_list : non_copyable
{
public:
    void add_element_description(drawable_description&& description);

private:
    std::vector<drawable_description> drawables;
};

} // namespace ivd::plate