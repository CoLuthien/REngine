
#include "core_object/class.hpp"

class Sample : public hln::hobject_t
{
public:
    GENERATE_BODY();
public:
    REFLECT_FUNCTION(add, int, int);
    int add(int a, int b) 
    {
        return a + b;
    }
public:
    REFLECT_FIELD(int const, x);
    REFLECT_FIELD(int const, y);
    REFLECT_FIELD(int const, z);
    
};

int main()
{

    Sample::detail_x_field_index;

    auto clazz = Sample::static_class();
    return 0;
}