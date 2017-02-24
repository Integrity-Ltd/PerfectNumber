#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

_Bool isPrime(uint64_t testNumber) {
  if (testNumber < 2 || testNumber > 3 && (testNumber % 2 == 0 || testNumber % 3 == 0)) {
    return false;
  }
  for (uint64_t i = 5;i < sqrt(testNumber); i += 6) {
    if ((testNumber % i == 0 || testNumber % (i + 2) == 0)) {
      return false;
    }
  }
  return true;
}

int main() {
  for (uint64_t p = 2; p < 32; p++) {
    if (isPrime(p)) {
      uint64_t mersenne = ((uint64_t) 1 << p) - 1;
      if (isPrime(mersenne)) {
        printf("%d: %llu\n", p, mersenne * (((uint64_t) 1 << (p - 1)));
      }
    }
  }
}
