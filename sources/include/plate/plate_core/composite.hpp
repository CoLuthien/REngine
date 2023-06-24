
#pragma once

#include "plate/plate.hpp"
#include "meta/concepts.hpp"

#include <vector>
#include <array>
#include <string_view>

namespace ivd::plate
{

class PLATE_API composite_base
{
public:
    virtual ~composite_base() = default;

public:
    virtual void        initialize(std::initializer_list<plate_ptr> plates) = 0;
    virtual std::size_t size() const                                        = 0;
    virtual plate*      at(std::size_t idx)                                 = 0;
    bool                empty() const { return size() == 0; }

public: // deleted
        // prevent composite's allocation
    void* operator new(std::size_t)   = delete;
    void* operator new[](std::size_t) = delete;
};

template <class Container>
    requires meta::is_shared_ptr<typename Container::value_type>
class composite : public Container, public composite_base
{
public:
    using Container::Container;
    using Container::operator=;

    using Container::empty;

public:
    virtual void        initialize(std::initializer_list<plate_ptr> plates) override;
    virtual std::size_t size() const override;
    virtual plate*      at(std::size_t idx) override;
};

template <class Container>
    requires meta::is_shared_ptr<typename Container::value_type>
void
composite<Container>::initialize(std::initializer_list<plate_ptr> plates)
{
    std::copy(plates.begin(), plates.end(), this->begin());
}

template <class Container>
    requires meta::is_shared_ptr<typename Container::value_type>
inline std::size_t
composite<Container>::size() const
{
    return Container::size();
}

template <class Container>
    requires meta::is_shared_ptr<typename Container::value_type>
inline plate*
composite<Container>::at(std::size_t idx)
{
    return (*this)[idx].get();
}

using vector_composite = composite<std::vector<plate_ptr>>;

template <std::size_t N>
using array_composite = composite<std::array<plate_ptr, N>>;

using single_composite = array_composite<1>;

} // namespace ivd::plate
