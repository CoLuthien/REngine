
#pragma once

#include "utils/non_copyable.hpp"
#include "math/point.hpp"
#include "math/extent.hpp"
#include "plate_export.hpp"
#include "plate_render/drawable.hpp"

#include <memory>
#include <vector>

namespace ivd::plate
{
struct drawable_info;
using layer_id_t = std::uint32_t;

enum class drawable_type_e
{
    BOX,
    LINE,
};

class PLATE_API drawable_description : non_copyable
{
public:
    drawable_description();
    drawable_description(drawable_description&&);
    drawable_description& operator=(drawable_description&&) noexcept;
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

    auto get_type() const { return type; }
    auto get_size() const { return size; }
    auto get_location() const { return location; }
    auto get_layer_id() const { return layer_id; }

public:
    drawable make_drawable() const;
    void     initialize(drawable_type_e                in_type,
                        std::unique_ptr<drawable_info> in_info,
                        point2f                       in_location,
                        extent2_f                      in_size,
                        layer_id_t                     in_layer);

private:
    drawable_type_e                type;
    std::unique_ptr<drawable_info> info;

private:
    point2f   location;
    extent2_f  size;
    layer_id_t layer_id;
};

class PLATE_API drawable_description_list : non_copyable
{
    friend class drawable_batch;

public:
    void add_element_description(drawable_description&& description);

private:
    std::vector<drawable_description> descriptions;
};

} // namespace ivd::plate