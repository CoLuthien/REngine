
#pragma once
#include "HAL/attributes.hpp"

#include "object.hpp"
#include "class.hpp"
#include <vector>
#include <unordered_set>
#include <atomic>

namespace ivd
{

class IVDAPI hobject_array
{
    friend class hobject;

public:
    hobject_array();
    static hobject_array* instance()
    {
        static hobject_array self;
        return &self;
    }

public:
    void insert_object(hobject* object);
    void delete_object(hobject* object);

    auto const& get_idxs() { return idx_used; }

public:
    void return_index(std::size_t idx);
    [[nodiscard]] bool is_valid_idx(std::size_t idx);
    std::size_t object_to_idx(hobject* object);
    hobject* idx_to_object(std::size_t idx);

private:
    [[nodiscard]] std::size_t get_index();

private:
    std::vector<hobject*> m_objects;

    std::unordered_set<std::size_t> idx_pool;
    std::unordered_set<std::size_t> idx_used;
    std::atomic<std::size_t> idx_end;
};

} // namespace ivd
