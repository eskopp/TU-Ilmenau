#ifndef __FIBONACCI_H_INCLUDED__
#define __FIBONACCI_H_INCLUDED__

#include <cstdint>

std::int64_t fib(int i) {
    std::int64_t f_0 = 0;
    std::int64_t f_1 = 1;
    for (int z = 0; z < i; ++z) {
        std::int64_t tmp = f_1;
        f_1 = f_0 + f_1;
        f_0 = tmp;
    }
    return f_0;
}

#endif // __FIBONACCI_H_INCLUDED__