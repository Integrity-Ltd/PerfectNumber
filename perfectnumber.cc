#include <iostream>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>

constexpr unsigned long long mersenne_max = 16392;  // 2 ^ x (2 ^ 12)
constexpr unsigned long long perfect_max = 2 * mersenne_max;
constexpr unsigned precision = 25;

namespace boost {
namespace multiprecision {
using boost::multiprecision::backends::cpp_int_backend;
typedef number<cpp_int_backend<mersenne_max, mersenne_max, unsigned_magnitude, unchecked, void> > uint_mersenne_t;
typedef number<cpp_int_backend<perfect_max, perfect_max, unsigned_magnitude, unchecked, void> > uint_perfect_t;
}
}
using boost::multiprecision::uint_mersenne_t;
using boost::multiprecision::uint_perfect_t;
using boost::multiprecision::miller_rabin_test;

#define TIME
// #define TIME_2

#ifdef TIME
#include <chrono>
#include <string>
using std::chrono::steady_clock;
using std::chrono::duration_cast;
#define TIME_CAST std::chrono::seconds
#define TIME_CAST_NAME " seconds"
void printDuration(const steady_clock::time_point &start,
                   const std::string &msg) {
  steady_clock::time_point end = steady_clock::now();
  std::cout << msg << duration_cast<TIME_CAST>(end - start).count()
            << TIME_CAST_NAME << std::endl;
}
#endif  // TIME

template <typename Tp_>
inline Tp_ power(uint64_t p) {
  Tp_ rtn = 1;
  for (; p > 0; p--) {
    rtn *= 2;
  }
  return rtn;
}

int main() {
#ifdef TIME
  steady_clock::time_point start = steady_clock::now();
#endif  // TIME
  for (uint64_t p = 1; p < mersenne_max; p++) {
    if (miller_rabin_test(p, precision)) {
      uint_mersenne_t mersenne = power<uint_mersenne_t>(p) - 1;
      if (miller_rabin_test(mersenne, precision)) {
        uint_perfect_t perfent_number = static_cast<uint_perfect_t>(mersenne) * power<uint_perfect_t>(p - 1);
        std::cout << p << ":	" << perfent_number << std::endl;
#ifdef TIME_2
        printDuration(start, "Calculating took: ");
#endif  // TIME_2
      }
    }
  }
#ifdef TIME
  printDuration(start, "Calculating took: ");
#endif  // TIME
  return 0;
}
