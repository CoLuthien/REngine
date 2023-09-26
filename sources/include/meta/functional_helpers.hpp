
#pragma once

#include "meta/utils.hpp"

#include <algorithm>
#include <type_traits>

namespace meta
{

template <template <typename...> typename ReturnType,
          meta::is_iterable_type InputType,
          class Lambda>
inline auto
map(InputType const& domain, Lambda&& F)
{
    using lambda_result_t = std::invoke_result_t<Lambda, typename InputType::value_type>;
    ReturnType<lambda_result_t> result;
    result.reserve(domain.size());
    std::transform(domain.begin(), domain.end(), std::inserter(result, result.end()), F);

    return result;
}
template <meta::is_iterable_type InputType, class Lambda>
inline auto
map(InputType const& domain, Lambda&& F)
{
    using lambda_result_t = std::invoke_result_t<Lambda, typename InputType::value_type>;
    std::vector<lambda_result_t> result;
    result.reserve(domain.size());
    std::transform(domain.begin(), domain.end(), std::inserter(result, result.end()), F);

    return result;
}

} // namespace meta