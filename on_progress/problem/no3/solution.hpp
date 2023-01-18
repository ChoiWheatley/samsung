#ifndef SOLUTION
#define SOLUTION

#include <cinttypes>
#include <exception>
#include <functional>
#include <set>
#include <string>
#include <type_traits>
#include <vector>

using std::enable_if_t;
using std::function;
using std::set;
using std::string;
using std::vector;

constexpr uint64_t MOD = 1000000007;

/** predicate에 일치하는 4bit 경우들만을 리턴한다.*/
template <class Pred_t>
set<char> case_generator(Pred_t predicate)
{
    set<char> ret{};
    for (char bit = 0b0000; bit <= 0b1111; bit++)
    {
        if (predicate(bit))
        {
            ret.insert(bit);
        }
    }
    return ret;
}

class wrong_char_exception
{
};

enum class ID : char
{
    D = 0b0001,
    C = 0b0010,
    B = 0b0100,
    A = 0b1000
};

auto to_char_vec(const string &str) -> vector<char>
{
    vector<char> ret{};
    for (char c : str)
    {
        switch (c)
        {
        case 'A':
            ret.push_back(static_cast<char>(ID::A));
            break;
        case 'B':
            ret.push_back(static_cast<char>(ID::B));
            break;
        case 'C':
            ret.push_back(static_cast<char>(ID::C));
            break;
        case 'D':
            ret.push_back(static_cast<char>(ID::D));
            break;
        default:
            throw wrong_char_exception{};
        }
    }
    return ret;
}

/**
 * yesterday 비트와 오늘 당번을 포함한 조합의 Cartesian Product를 수행한다.
 * Product 수행 시 필터를 거는데, 반드시 두 비트의 AND 연산이 0이 아니어야 한다.
 *
 * 모든 Product*filter의 조합에 대하여 DFS 탐색을 진행한다.
 *
 * 문제에서 추가된 조건에 따라서 ${MOD} 만큼 나눈 나머지를 리턴하라고 했다. 이때 모듈러 덧셈연산을
 * 활용할 수 있다.
 *      (A + B) mod C = ((A mod C) + (B mod C)) mod C
 */
auto recur(const vector<char> &bits, char yesterday, size_t day) -> uint64_t
{
    if (day >= bits.size())
    {
        return 1UL;
    }
    uint64_t count = 0;

    const char today = bits.at(day);
    auto pred = [yesterday, today](char a)
    {
        return ((a & today) == today) &&    // 오늘 당번은 무조건 와야 하고
               ((a & yesterday) != 0b0000); // 어제 적어도 한 명은 오늘 다시 와야한다.
    };
    set<char> possible_cases = case_generator(pred);

    for (char elem : possible_cases)
    {
        count += (recur(bits, elem, day + 1)) % MOD;
    }
    return count % MOD;
}

/**
 * 동아리활동은 적어도 한 명의 인원이 참여해야 하며, 열쇠를 자신이 들고 가거나 다른
 * 부원에게 넘겨주어야 한다. => 전날에 참여한 인원 중 적어도 한 명은 참석해야 한다.
 *
 * bits의 각 원소는 해당 날짜에 반드시 참여해야 하는 사람을 의미한다.
 */
auto solution(const vector<char> &bits) -> uint64_t
{
    // 첫째날은 A가 열쇠를 가지고 있다.
    char first_day = (bits.at(0) | static_cast<char>(ID::A));
    auto pred = [first_day](char a)
    {
        return ((a & first_day) == first_day); // A와 당번은 첫날 무조건 등교해야 한다.
    };
    uint64_t count = 0UL;
    set<char> possible_cases = case_generator(pred);

    for (char elem : possible_cases)
    {
        count += (recur(bits, elem, 1)) % MOD;
    }
    return count % MOD;
}

/**
 * str.size()일 동안의 동아리 활동을 할 수 있는 경우의 수를 출력.
 */
auto solution(const string &str) -> uint64_t
{
    return solution(to_char_vec(str));
}

#endif