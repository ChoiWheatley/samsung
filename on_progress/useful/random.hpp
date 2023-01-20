#ifndef MYRANDOM
#define MYRANDOM

#include <random>

using std::mt19937;
using std::random_device;
using std::uniform_int_distribution;

template <typename T> struct Random {
  random_device seeder;
  const long seed;
  mt19937 engine;
  uniform_int_distribution<T> dist;

  Random()
      : seed{seeder.entropy() != 0.0 ? seeder() : time(nullptr)},
        engine{static_cast<mt19937::result_type>(seed)} {}
  auto next() -> T { return dist(engine); }
};

#endif