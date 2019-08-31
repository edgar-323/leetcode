#include <iostream>
#include "BigInteger.h"

void extraLongFactorials(unsigned int n) {
    BigInteger bigInt(1);
    while (n > 0) {
        bigInt *= n;
        --n;
    }
    std::cout << bigInt << std::endl;
}

int main() {
  return 0;
}
