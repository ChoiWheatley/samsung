#ifndef SOLUTION
#define SOLUTION

#include <cassert>
#include <cinttypes>
#include <cmath>
#include <ctype.h>
#include <typeinfo>

bool solution(int n, uint32_t m)
{
    const auto len = static_cast<int>(log2(m)); // log(4) = log(0b10) = 2

    if (n > len + 1)
    {
        return false;
    }

    int mask = 0b0;
    for (int idx = 0; idx < n; ++idx)
    {
        mask |= (1 << idx);
    }
    return (m & mask) == mask;
}

#endif