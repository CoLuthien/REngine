
#pragma once

#include "plate_core/layout/margin.hpp"
#include "plate_core/composite.hpp"
#include "plate/plate.hpp"

namespace ivd::plate
{

class PLATE_API filled_box : public plate
{
public:
    filled_box();
    virtual ~filled_box();

public:
    virtual void draw(drawable_description_list& list,
                      std::size_t                layer_id,
                      layout_geometry const&     geometry) override;

private:
    extent2_f size;
    margin    m_margin;
};

} // namespace ivd::plate
