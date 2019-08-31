#include <iostream>

class BigInteger {
public:
  /****************************************************************************/
  BigInteger(unsigned int n);
  BigInteger(BigInteger& bigInt);
  ~BigInteger();
  BigInteger& operator += (unsigned int n);
  BigInteger& operator += (BigInteger& bigInt);
  BigInteger& operator *= (unsigned int n);
  friend std::ostream& operator << (std::ostream& stream, BigInteger& bigInt) {
    unsigned int* arr = bigInt.getArray();
    for (int index = bigInt.getSize() - 1; index >= 0; --index) {
      stream << arr[index];
    }
    return stream;
  }
  /****************************************************************************/
private:
  /****************************************************************************/
  unsigned int * digits;
  std::size_t size;
  std::size_t capacity;
  /****************************************************************************/
  void initialize(std::size_t cap, std::size_t len);
  std::size_t getSize() const;
  std::size_t getCapacity() const;
  unsigned int* getArray();
  void checkCapacity(unsigned int i);
  void doubleCapacity();
  void setThisTo(unsigned int n);
  void releaseDigits();
  /****************************************************************************/
};
