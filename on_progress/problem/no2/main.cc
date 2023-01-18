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
        int m;
        std::cin >> n >> m;
        bool submit = solution(n, m);
        std::cout << "#" << test_case << " " << (submit ? "ON" : "OFF") << "\n";
    }

    return 0;
}