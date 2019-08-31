#include <iostream>
#include "BigInteger.h"

/******************************************************************************/
/******************************************************************************/
BigInteger::BigInteger(unsigned int n) {
  initialize(16, 0);
  setThisTo(n);
}
/******************************************************************************/
BigInteger::BigInteger(BigInteger& bigInt) {
  initialize(bigInt.getCapacity(), bigInt.getSize());
  unsigned int* otherArr = bigInt.getArray();
  for (std::size_t i = 0; i < size; ++i) {
    digits[i] = otherArr[i];
  }
}
/******************************************************************************/
BigInteger::~BigInteger() {
  releaseDigits();
}
/******************************************************************************/
BigInteger& BigInteger::operator += (unsigned int n) {
  std::size_t index = 0;
  unsigned int carry = 0;
  unsigned int sum = 0;
  while (n > 0 || carry > 0) {
    if (index >= size) {
      checkCapacity(index);
      ++size;
      digits[index] = 0;
    }
    sum = digits[index] + (n % 10) + carry;
    digits[index] = sum % 10;
    carry = sum / 10;
    n /= 10;
    ++index;
  }

  return *this;
}
/******************************************************************************/
BigInteger& BigInteger::operator *= (unsigned int n) {
  unsigned int mult = 0;
  unsigned int carry = 0;
  for (std::size_t index = 0; index < size; ++index) {
    mult = digits[index] * n + carry;
    digits[index] = mult % 10;
    carry = mult / 10;
  }

  while (carry > 0) {
    checkCapacity(size);
    digits[size] = carry % 10;
    carry /= 10;
    ++size;
  }

  return *this;
}
/******************************************************************************/
/******************************************************************************/
void BigInteger::releaseDigits() {
  delete[] digits;
}
/******************************************************************************/
void BigInteger::initialize(std::size_t cap, std::size_t len) {
  capacity = cap;
  size = len;
  digits = new unsigned int[capacity];
}
/******************************************************************************/
std::size_t BigInteger::getSize() const {
  return size;
}
/******************************************************************************/
std::size_t BigInteger::getCapacity() const {
  return capacity;
}
/******************************************************************************/
unsigned int* BigInteger::getArray() {
  return digits;
}
/******************************************************************************/
void BigInteger::checkCapacity(unsigned int i) {
  if (i >= capacity) {
    doubleCapacity();
  }
}
/******************************************************************************/
void BigInteger::doubleCapacity() {
  capacity *= 2;
  unsigned int * newArray = new unsigned int[capacity];
  for (std::size_t i = 0; i < size; ++i) {
    newArray[i] = digits[i];
  }
  releaseDigits();
  digits = newArray;
}
/******************************************************************************/
void BigInteger::setThisTo(unsigned int n) {
  for (std::size_t i = 0; n > 0; ++i, n /= 10, ++size) {
    checkCapacity(i);
    unsigned int digit = n % 10;
    digits[i] = digit;
  }
}
/******************************************************************************/
/******************************************************************************/
