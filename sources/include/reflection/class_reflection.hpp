
#pragma once

#include "reflection_helper.hpp"
namespace refl
{

class rclass
{
private:
    struct class_iface_t
    {
    };

    template <class Target>
    struct class_info_t;

public:
    rclass() = delete;

    template <typename Target>
    static constexpr auto make_class()
    {
        using type = class_info_t<Target>;
        return rclass(type::reflected_info());
    }

private:
    class_iface_t const* m_info;

private:
    constexpr rclass(class_iface_t const* ptr) : m_info(ptr) {}
};

template <class Target>
struct rclass::class_info_t : rclass::class_iface_t
{
public:
    static constinit class_info_t const class_info;

public:
    static constexpr auto reflected_info() { return &class_info; }
    template <typename... Args>
    Target* make_instance(Args... args) const
    {
        return new Target{std::forward<Args>(args)...};
    }
};

template <class Target>
constinit rclass::class_info_t<Target> const rclass::class_info_t<Target>::class_info = {};

} // namespace refl
