
#pragma once

#include "rdi_export.hpp"

#include <memory>

namespace ivd
{

namespace rdi
{
class vertex_buffer;
class index_buffer;

class RDI_API rdi_cmd
{
public:
};

class RDI_API rdi_cmd_mesh_draw : public rdi_cmd
{
public:
private:
    std::shared_ptr<vertex_buffer> vertices;
    std::shared_ptr<index_buffer>  indices;
};

} // namespace rdi

} // namespace ivd
