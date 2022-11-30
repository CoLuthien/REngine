
#pragma once

#include "Reflection/Object.hpp"
#include "GObject.hpp"

namespace ge
{
class GField : public GObject
{

private:
    refl::RField* m_info;
};

class GFunction : public GObject
{

private:
    refl::RFunction* m_info;
};

class GClass : public GObject
{
    GClass(refl::RClass*);

private:
    refl::RClass* m_info;
};

} // namespace  ge
