
#pragma once

#include "plate/definitions.hpp"
#include "plate_types.hpp"

#include "utils/non_copyable.hpp"

#include <memory>

namespace ivd::plate
{
class window_host;

class PLATE_API window : non_copyable
{
public:
private:
    std::unique_ptr<window_host> m_host;
};
} // namespace ivd::plate