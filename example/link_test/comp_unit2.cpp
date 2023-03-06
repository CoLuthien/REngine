
#include "comp_unit2.h"
#include "test.h"

#include <core/core.hpp>

ivd::hclass_t*
get_another()
{
    return Sample::static_class();
}