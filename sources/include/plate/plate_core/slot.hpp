
#pragma once

#include "plate/plate.hpp"
#include "meta/concepts.hpp"

#include <vector>
#include <array>
#include <string_view>

namespace ivd::plate
{

class PLATE_API slot_base
{
public:
    virtual ~slot_base() = default;

public:
    virtual std::size_t size() const   = 0;
    virtual plate* at(std::size_t idx) = 0;
    bool empty() const { return size() == 0; }
};

template <class Container>
    requires requires { meta::is_shared_ptr<typename Container::value_type>; }
class plate_slot : public Container, public slot_base
{
public:
    using Container::Container;
    using Container::operator=;

    using Container::empty;

public:
    virtual std::size_t size() const override;
    virtual plate* at(std::size_t idx) override;
};

template <class Container>
    requires requires { meta::is_shared_ptr<typename Container::value_type>; }
inline std::size_t
plate_slot<Container>::size() const
{
    return Container::size();
}

template <class Container>
    requires requires { meta::is_shared_ptr<typename Container::value_type>; }
inline plate*
plate_slot<Container>::at(std::size_t idx)
{
    return (*this)[idx].get();
}

using vector_slot = plate_slot<std::vector<std::shared_ptr<plate>>>;
using one_slot    = plate_slot<std::array<std::shared_ptr<plate>, 1>>;

} // namespace ivd::plate
