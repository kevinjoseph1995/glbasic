#pragma once

#include <cstdio>
#define unlikely(x) __builtin_expect(!!(x), 0)

// TODO: Kevin Don't use clang intrinsic here
#define GL_ASSERT(expr, ...)                                                                                           \
    do                                                                                                                 \
    {                                                                                                                  \
        if (unlikely(!(expr)))                                                                                         \
        {                                                                                                              \
            printf("FILE: %s, LINE %d, FUNC: %s, ASSERT_FAILED:  " #expr "\n", __FILE__, __LINE__, __func__);          \
            __builtin_debugtrap();                                                                                     \
        }                                                                                                              \
    } while (0)
