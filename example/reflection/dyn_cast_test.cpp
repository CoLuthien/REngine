

#include "core/core.hpp"
#include <string_view>
#include <iostream>

#include <cstddef>

class T1 : public ivd::hobject_t
{
public:
    GENERATE_BODY()
};

class T2 : public ivd::hobject_t
{
public:
    GENERATE_BODY()
};

class Sample : public T2
{
public:
    GENERATE_BODY();

public:
    REFLECT_FUNCTION(add, int, int);
    int add(int a, int b)
    {
        std::cout << "add " << a << " and " << b << '\n';
        return a + b;
    }

private:
    REFLECT_FIELD(int const, x);
    REFLECT_FIELD(int const, y);
    REFLECT_FIELD(int const, z);
    REFLECT_FIELD(int, w);
};

class T3 : public Sample
{
    GENERATE_BODY();
};

int
main()
{
    auto* sample = new Sample{};

    auto* ptr = cast<T2>(sample);
    if (ptr == nullptr)
    {
        std::cout << "fuck";
    }

}