
#include "core/core.hpp"
#include "core_object/core_object.hpp"
#include "asset/static_mesh_asset.hpp"
#include "math/vector.hpp"
#include "math/point.hpp"
#include "math/quaternion.hpp"
#include <string_view>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <meta/utils.hpp>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

static constexpr auto pointer_v = &ivd::asset::static_mesh_asset::get_metadata;

class Sample : public ivd::hobject
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

public:
    REFLECT_FIELD(int, x);
    REFLECT_FIELD(int, w);
};

class Test : public Sample
{
public:
    GENERATE_BODY();
};

template <typename T>
class Test2 : public Test
{
public:
    GENERATE_BODY();

public:
    REFLECT_FIELD(std::vector<T>, Type);
    REFLECT_FIELD(std::queue<T>, queue);
    REFLECT_FIELD(std::unordered_map<DECLARE_TEMPLATE_PARAMS(std::string, T)>, map);
};

struct StructTest
{
    GENERATE_STRUCT()

public:
    REFLECT_FIELD(std::string, name);
    REFLECT_FIELD(std::string, job);
    REFLECT_FIELD(std::unordered_map<DECLARE_TEMPLATE_PARAMS(std::string, int)>, map);
};

int
main()
{
    {
        auto* mesh = new ivd::asset::static_mesh_asset{};
        mesh->get_num_meshes();
    }
    using TType = ivd::hobject*;
    auto* ptr   = new_object<Test2<TType>>(nullptr);
    auto* clazz = Test2<TType>::static_class();

    auto func_add = clazz->find_func("add");

    if (func_add != nullptr)
    {
        int x = func_add->invoke<int>(ptr, 1, 2);
        std::cout << x << '\n';
    }

    auto prop_w = clazz->find_field("Type");
    if (prop_w != nullptr)
    {
        auto& value = prop_w->get<std::vector<TType>>(ptr); // 0
    }
    std::cout << meta::to_underlying(prop_w->get_type());

    return 0;
}