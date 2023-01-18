#include "solution.hpp"
#include <iostream>

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    for (int test_case = 1; test_case <= t; ++test_case)
    {
        int n;
        std::cin >> n;
        std::cout << "#" << test_case << " " << solve(n) << "\n";
    }
    return 0;
}