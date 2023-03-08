
#pragma once

#include "HAL/attributes.hpp"

#include <vector>
#include <unordered_set>

namespace ivd
{

class hobject;

class DLLEXPORT garbage_collector
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
