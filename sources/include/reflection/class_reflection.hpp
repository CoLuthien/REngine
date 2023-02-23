
#pragma once

#include "reflection_helper.hpp"
namespace refl
{

class rclass_t
{
private:
    struct class_iface_t
    {
        virtual void* make_instance() const = 0;
    };

    template <class Target>
    struct class_info_t;

public:
    rclass_t() = delete;

    template <typename Target>
    static constexpr auto make_class()
    {
        using type = class_info_t<Target>;
        return rclass_t(type::reflected_info());
    }

private:
    class_iface_t const* m_info;

private:
    constexpr rclass_t(class_iface_t const* ptr) : m_info(ptr) {}

    template <class Target, typename... Args>
    Target* make_instance(Args... args) const
    {
        using type = class_info_t<Target>;
        return static_cast<type const*>(m_info)->make_instance(
            std::forward<Args>(args)...);
    }
};

template <class Target>
struct rclass_t::class_info_t : rclass_t::class_iface_t
{
public:
    static constinit class_info_t const class_info;
public:
    static constexpr auto reflected_info() { return &class_info; }
    virtual void* make_instance() const override { return new Target{}; }
    template <typename... Args>
    Target* make_instance(Args... args) const
    {
        return new Target{std::forward<Args>(args)...};
    }
};

template <class Target>
constinit rclass_t::class_info_t<Target> const
    rclass_t::class_info_t<Target>::class_info = {};

} // namespace refl
