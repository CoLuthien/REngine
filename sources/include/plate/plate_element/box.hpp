
#pragma once

#include "plate/plate.hpp"
#include "plate_core/composite.hpp"

namespace ivd::plate
{

class PLATE_API box : public plate
{
public:
    box()          = default;
    virtual ~box() = default;

public:
    virtual void organize(layout_geometry const&        geometry,
                          std::vector<organized_plate>& plates) override;
    virtual void draw(drawable_description_list&          list,
                              std::size_t            layer_id,
                              layout_geometry const& geometry) override;

public:
    using plate::content;
    virtual void            content(std::initializer_list<plate_ptr> plates) override;
    virtual composite_base* get_composite() override { return &m_children; }

private:
    single_composite m_children;
};

} // namespace ivd::plate