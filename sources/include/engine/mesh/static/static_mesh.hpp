
#pragma once

#include "engine_export.hpp"
#include "mesh/static/static_mesh_resources.hpp"

namespace ivd
{

class ENGINE_API static_mesh : public hobject
{
    GENERATE_BODY()
public:
private:
    REFLECT_FIELD(std::shared_ptr<static_mesh_description>, m_description, nullptr);
};

} // namespace ivd