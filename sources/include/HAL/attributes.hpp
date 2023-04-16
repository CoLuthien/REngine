#pragma once

#if defined(_WIN64)

#include "windows/attributes.hpp"

#elif defined(__linux__)

#include "linux/attributes.hpp"

#endif

#ifndef IVDAPI

#define IVDAPI

#endif
