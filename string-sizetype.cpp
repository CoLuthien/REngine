
#include <string>
#include <iostream>
#include <type_traits>

template<typename T>
struct size_traits
{
    struct tag{};

};


void SerializeImpl(std::string const &ref, size_traits<int16_t>::tag)
{
    std::cout << "int16_t";
}

void SerializeImpl(std::string const &ref, size_traits<int8_t>::tag)
{
    std::cout << "int8_t";
}

void SerializeImpl(std::string const &ref, size_traits<unsigned int>::tag)
{
    std::cout << "unsigned int";
}

void SerializeImpl(std::string const &ref, size_traits<int64_t>::tag)
{
    std::cout << "int64_t";
}

void SerializeImpl(std::string const &ref, size_traits<uint64_t>::tag)
{
    std::cout << "uint64_t";
}

template <class T>
void Serialize(T const &ref)
{
}

template <>
void Serialize(std::string const &ref)
{

    SerializeImpl(ref, size_traits<std::string::size_type>::tag{});
}

int main()
{
    std::string test = "Hello World\n";

    Serialize<std::string>(test);
}
