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
        std::string str;
        std::cin >> str;
        uint64_t submit = solution(str);
        std::cout << "#" << test_case << " " << submit << "\n";
    }
    return 0;
}