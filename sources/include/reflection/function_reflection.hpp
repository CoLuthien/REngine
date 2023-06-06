
#pragma once

#include "reflection_utils.hpp"
#include "reflection_concepts.hpp"
#include "reflection_helper.hpp"
#include "meta/func_traits.hpp"

namespace refl
{

class rfunction
{
public:
    template <class Target, std::size_t I>
    static consteval auto reflect_field()
    {
        using trait     = func_traits<func_pointer_t<Target, I>>;
        using info_type = typename strip_tuple<Target,
                                               I,
                                               typename trait::result_type,
                                               typename trait::args_type>::type;
        return rfunction(info_type::reflected_info());
    }

    template <typename R, typename... Args>
    R invoke(void* obj, Args... args)
    {
        using type = field_iface_t<R, Args...>;
        auto ptr   = static_cast<type const*>(m_info);

        return ptr->invoke_impl(obj, args...);
    }

private:
    struct handle_t;
    template <typename R, typename... Args>
    struct field_iface_t;
    template <class Target, std::size_t I, typename R, typename... Args>
    struct field_info_t;

    handle_t const* m_info;

private:
    constexpr rfunction(handle_t const* handle) : m_info(handle) {}
    template <typename Target, std::size_t I, typename R, typename Tuple>
    struct strip_tuple;

    template <typename Target, std::size_t I, typename R, typename... Ts>
    struct strip_tuple<Target, I, R, std::tuple<Ts...>>
    {
        using type = field_info_t<Target, I, R, Ts...>;
    };
};

struct rfunction::handle_t
{
    virtual ~handle_t() = default;
};

template <typename R, typename... Args>
struct rfunction::field_iface_t : public rfunction::handle_t
{
    virtual ~field_iface_t()                                = default;
    virtual R invoke_impl(void* object, Args... args) const = 0;
};

template <class Target, std::size_t I, typename R, typename... Args>
struct rfunction::field_info_t : public rfunction::field_iface_t<R, Args...>
{
    using owner_type   = Target;
    using pointer_type = func_pointer_t<Target, I>;
    using result_type  = R;

    static constexpr auto pointer = func_pointer_v<Target, I>;
    static constexpr auto name    = func_name_v<Target, I>;
    static constinit field_info_t const field_info;

    static constexpr auto reflected_info() { return &field_info; }

    virtual R invoke_impl(void* object, Args... args) const
    {
        return std::invoke(
            pointer, reinterpret_cast<owner_type*>(object), std::forward<Args>(args)...);
    }
};

template <class Target, std::size_t I, typename R, typename... Args>
constinit rfunction::field_info_t<Target, I, R, Args...> const
    rfunction::field_info_t<Target, I, R, Args...>::field_info = {};

template <class Target, std::size_t Index>
struct gather_functions
{
    static constexpr auto instance = refl::rfunction::reflect_field<Target, Index>();
    static constexpr auto name     = func_name_v<Target, Index>;
    static consteval std::pair<std::string_view, refl::rfunction*> get_entry()
    {
        return std::make_pair(name, const_cast<rfunction*>(&instance));
    }
};

template <class Target>
struct gather_functions<Target, std::numeric_limits<std::size_t>::max()>
{
    static consteval std::pair<std::string_view, refl::rfunction*> get_entry()
    {
        return std::pair<std::string_view, refl::rfunction*>{};
    }
};
} // namespace refl

#define INFER_FUNC_TYPE(NAME)                                                            \
    template <class C, typename... Args>                                                 \
    using inferred_type =                                                                \
        decltype(std::declval<C>().NAME(std::declval<Args>()...)) (C::*)(Args...);

#define REFLECT_FUNCTION(NAME, ...)                                                      \
    static constexpr size_t detail_##NAME##_function_index =                             \
        refl::detail::index<struct detail_##NAME##_function_tag,                         \
                            detail_function_reflection>::value;                          \
    template <>                                                                          \
    struct detail_function_reflection<detail_##NAME##_function_index>                    \
    {                                                                                    \
        INFER_FUNC_TYPE(NAME);                                                           \
        static constexpr std::string_view name = #NAME;                                  \
        template <class Target>                                                          \
        using type = inferred_type<Target, __VA_ARGS__>;                                 \
        template <class Target>                                                          \
        static constexpr type<Target> pointer_v = &Target::NAME;                         \
    };
