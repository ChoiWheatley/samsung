#include <cstdlib>
#include <cstring>
#include <functional>
#include <string>
#include <vector>

class BigInteger
{
    std::vector<int> digits;

    static std::vector<int> initialize(int init)
    {
        std::vector<int> pre_digits{};
        while (init > 0)
        {
            pre_digits.push_back(init % 10);
            init /= 10;
        }
        return pre_digits;
    }

public:
    BigInteger(int init)
        : digits{BigInteger::initialize(init)} {}

    BigInteger(const std::vector<int> &vec)
        : digits{vec} {}

    BigInteger(const BigInteger &other) = default;

    BigInteger &operator=(const BigInteger &other)
    {
        digits = other.as_vector();
        return *this;
    }

    auto as_vector() const -> const std::vector<int> &
    {
        return digits;
    }

    static auto to_string(const BigInteger &bi) -> std::string
    {
        std::string ret = "";
        for (auto iter = bi.as_vector().crbegin(); iter != bi.as_vector().crend(); iter++)
        {
            ret += std::to_string(*iter);
        }
        return ret;
    }

    auto to_string() const -> std::string
    {
        return BigInteger::to_string(*this);
    }

    auto mult(int n) const -> BigInteger
    {
        std::vector<int> answer{};
        int over = 0;
        for (int i = 0; i < digits.size(); ++i)
        {
            int tmp = digits[i] * n + over;
            over = tmp / 10;
            answer.push_back(tmp % 10);
        }
        if (over > 0)
        {
            answer.push_back(over);
        }
        return BigInteger{answer};
    }

    auto add(const BigInteger &other) const -> BigInteger
    {
        using std::size_t;
        using std::vector;

        const vector<int> &a = as_vector().size() < other.as_vector().size() ? this->digits : other.as_vector();
        const vector<int> &b = as_vector().size() < other.as_vector().size() ? other.as_vector() : this->as_vector();

        size_t smaller_size = a.size();
        size_t bigger_size = b.size();

        std::vector<int> answer{};

        int over = 0;
        for (size_t idx = 0; idx < bigger_size; ++idx)
        {
            if (idx < smaller_size)
            {
                int tmp = a.at(idx) + b.at(idx) + over;
                over = tmp / 10;
                answer.push_back(tmp % 10);
            }
            else
            {
                int tmp = b.at(idx) + over;
                over = tmp / 10;
                answer.push_back(tmp % 10);
            }
        }
        if (over > 0)
        {
            answer.push_back(over);
        }
        return BigInteger{answer};
    }

    auto operator*(int n) const -> BigInteger
    {
        return mult(n);
    }

    auto operator*=(int n) -> void
    {
        digits = this->mult(n).as_vector();
    }

    auto operator+(const BigInteger &other) const -> BigInteger
    {
        return add(other);
    }

    auto operator+=(const BigInteger &other) -> void
    {
        digits = this->add(other).as_vector();
    }
};

auto solve(int n) -> std::string
{
    int bits = 0b0;
    BigInteger bigInteger{n};
    const BigInteger add_by{bigInteger};

    for (int digit : bigInteger.as_vector())
    {
        bits |= (1 << digit);
    }
    while ((bits & 0b1111111111) != 0b1111111111)
    {
        bigInteger = bigInteger + add_by;
        for (int digit : bigInteger.as_vector())
        {
            bits |= (1 << digit);
        }
    }

    return bigInteger.to_string();
}
