
#pragma once

namespace ge
{
class GObject;

} // namespace ge

namespace refl
{
template <class Target>
concept HasOperatorNew = requires() { new Target{}; };

template <class Target>
concept HasReflectedFunction =
    requires { typename Target::template detail_function_reflection<0, Target>; };
template <class Target>
concept HasReflectedField =
    requires { typename Target::template detail_property_reflection<0, Target>; };

template <class Target>
concept FullyReflected =
    HasReflectedField<Target> && HasReflectedFunction<Target> && HasOperatorNew<Target>;

} // namespace refl
