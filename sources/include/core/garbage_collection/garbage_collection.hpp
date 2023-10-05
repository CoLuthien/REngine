
#pragma once

#include "core_export.hpp"

#include <vector>
#include <unordered_set>

namespace ivd
{

class hobject;

class CORE_API garbage_collector
{
public:
    garbage_collector() = default;

public:
    void mark_objects();
    void sweep_objects();

    void add_to_root(hobject* obj);

public:
    static garbage_collector* instance()
    {
        static garbage_collector self;
        return &self;
    }

private:
    std::vector<std::size_t> m_rootset;
};
} // namespace ivd
