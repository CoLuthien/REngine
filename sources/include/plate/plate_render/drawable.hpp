
#pragma once

#include "plate/definitions.hpp"
#include "math/point.hpp"
#include "plate_render/drawable_vertex.hpp"

#include <vector>

namespace ivd::plate
{

class PLATE_API drawable
{
public:
    drawable();

public:
    void add_index(drawable_index idx) { indices.emplace_back(idx); }
    void add_vertex(drawable_vertex&& vertex) { vertices.emplace_back(std::move(vertex)); }

private:
    std::vector<drawable_vertex> vertices;
    std::vector<drawable_index>  indices;
};

class PLATE_API drawable_factory
{
};

} // namespace ivd::plate