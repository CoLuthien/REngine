

#include "comp_unit2.h"
#include "test.h"
#include "core/core.hpp"
#include <string_view>
#include <iostream>
#include <chrono>

#include <cstddef>

#include <frozen/set.h>

int
main()
{
    ivd::hobject* test[10000] = {};

    for (int i = 0; i < 10000; i++)
    {
        if (i % 3 == 0)
        {
            test[i] = new_object<Sample>(nullptr);
        }
        else {
            test[i] = new_object<T1>(nullptr);
        }
    }

    auto begin2 = std::chrono::steady_clock::now();
    int cnt = 0;
    for (int i = 0; i < 10000; i++)
    {
        if (auto ptr = dynamic_cast<Sample*>(test[i]))
        {
            cnt++;
        }
    }

    auto end2 = std::chrono::steady_clock::now();
    std::cout
        << "Time difference = "
        << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count()
        << "[µs]" << cnt << std::endl;

    cnt = 0;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 10000; i++)
    {
        if (auto ptr = cast<Sample>(test[i]))
        {
            cnt++;
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout
        << "My Time difference = "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
        << "[µs]" << cnt << std::endl;

}