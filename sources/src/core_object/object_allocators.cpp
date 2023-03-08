
#include "object_array.hpp"
#include "object_allocators.hpp"

static ivd::hobject_array* object_array = ivd::hobject_array::instance();

void DLLEXPORT
new_object_internal(ivd::hobject* obj)
{
    object_array->insert_object(obj);
}