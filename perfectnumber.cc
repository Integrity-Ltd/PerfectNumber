#include <iostream>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>

#define number(size) boost::multiprecision::number<boost::multiprecision::backends::cpp_int_backend<size, size>>
using boost::multiprecision::miller_rabin_test;

#define TIME
// #define TIME_2

const unsigned mersenne_max = 16392; // 2 ^ x (2 ^ 12)
const unsigned perfect_max = 2 * mersenne_max;
const unsigned precision = 25;

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
#endif // TIME

inline number(mersenne_max)power_mersenne_max(uint64_t p) {
	number(mersenne_max) rtn = 1;
	for (; p > 0; p--) {
		rtn *= 2;
	}
	return rtn;
}

inline number(perfect_max)power_perfect_max(uint64_t p) {
	number(perfect_max) rtn = 1;
	for (; p > 0; p--) {
		rtn *= 2;
	}
	return rtn;
}

int main() {
#ifdef TIME
	steady_clock::time_point start = steady_clock::now();
#endif // TIME
	for (uint64_t p = 1; p < mersenne_max; p++) {
		if (miller_rabin_test(p, precision)) {
			number(mersenne_max)mersenne = power_mersenne_max(p) - 1;
			if (miller_rabin_test(mersenne, precision)) {
				number(perfect_max) perfent_number = (number(perfect_max)) mersenne * power_perfect_max(p - 1);
				std::cout << p << ":	" << perfent_number << std::endl;
#ifdef TIME_2
				printDuration(start, "Calculating took: ");
#endif // TIME_2
			}
		}
	}
#ifdef TIME
	printDuration(start, "Calculating took: ");
#endif // TIME
	return 0;
}
