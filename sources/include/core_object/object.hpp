
#pragma once

#include "concepts.hpp"
#include "reflection/reflection.hpp"

#include "meta/type_list.hpp"
#include "HAL/platforms.hpp"
#include <cstddef>

enum eobject_flag
{
    REFL_TYPE    = 1 << 0,
    UNREACHABLE  = 1 << 1,
    PENDING_KILL = 1 << 2,
    ROOT_OBJECT  = 1 << 3,
};
namespace ivd
{

class hclass_t;
class DLLEXPORT hobject_t
{
public:
    GENERATE_HOBJECT_BODY();
public:
    hobject_t();

public:
    hclass_t* get_class();


private:
    eobject_flag m_flag;

private:
    std::size_t m_gcidx;
};

} // namespace ivd
