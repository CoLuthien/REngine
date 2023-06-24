
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
    using plate::content;
    virtual void content(std::initializer_list<plate_ptr> plates) override;

    virtual composite_base* get_composite() override { return &m_children; }

private:
    single_composite m_children;
};

} // namespace ivd::plate