#ifndef BIG_INTEGER_H_
#define BIG_INTEGER_H_

#include <string>
#include <vector>

namespace big_num_arithmetic {

struct DivisionByZeroError {};

class BigInteger {
  friend class Tester;
 public:
  static int internal_base;

  explicit BigInteger(int64_t number);
  BigInteger();

  int Sign() const;
  void Negate();
  void Abs();

  static BigInteger FromString(std::string number_str, int base);
  std::string ToString(int base) const;

  bool operator==(const BigInteger& rhs) const;
  bool operator!=(const BigInteger& rhs) const;
  bool operator<(const BigInteger& rhs) const;
  bool operator>(const BigInteger& rhs) const;
  bool operator<=(const BigInteger& rhs) const;
  bool operator>=(const BigInteger& rhs) const;

  bool operator==(int64_t rhs) const;
  bool operator!=(int64_t rhs) const;
  bool operator<(int64_t rhs) const;
  bool operator>(int64_t rhs) const;
  bool operator<=(int64_t rhs) const;
  bool operator>=(int64_t rhs) const;

  friend bool operator==(int64_t lhs, const BigInteger& rhs);
  friend bool operator!=(int64_t lhs, const BigInteger& rhs);
  friend bool operator<(int64_t lhs, const BigInteger& rhs);
  friend bool operator>(int64_t lhs, const BigInteger& rhs);
  friend bool operator<=(int64_t lhs, const BigInteger& rhs);
  friend bool operator>=(int64_t lhs, const BigInteger& rhs);

  BigInteger operator-() const;
  BigInteger operator+() const;

  BigInteger operator+(const BigInteger& rhs) const;
  BigInteger operator-(const BigInteger& rhs) const;
  BigInteger operator*(const BigInteger& rhs) const;
  BigInteger operator/(const BigInteger& rhs) const;

  BigInteger operator+(int64_t rhs) const;
  BigInteger operator-(int64_t rhs) const;
  BigInteger operator*(int64_t rhs) const;
  BigInteger operator/(int64_t rhs) const;

  uint32_t operator%(uint32_t rhs) const;

  friend BigInteger operator+(int64_t lhs, const BigInteger& rhs);
  friend BigInteger operator-(int64_t lhs, const BigInteger& rhs);
  friend BigInteger operator*(int64_t lhs, const BigInteger& rhs);
  friend BigInteger operator/(int64_t lhs, const BigInteger& rhs);

  BigInteger& operator+=(const BigInteger& rhs);
  BigInteger& operator-=(const BigInteger& rhs);
  BigInteger& operator*=(const BigInteger& rhs);
  BigInteger& operator/=(const BigInteger& rhs);

  BigInteger& operator+=(int64_t rhs);
  BigInteger& operator-=(int64_t rhs);
  BigInteger& operator*=(int64_t rhs);
  BigInteger& operator/=(int64_t rhs);

  BigInteger& operator++();
  BigInteger& operator--();

  BigInteger operator++(int);
  BigInteger operator--(int);

  explicit operator int64_t() const;

 private:
  int sign_;
  class UnsignedBig {
    friend class Tester;
   public:
    void Init(int64_t number);
    void FromString(const std::string& number_str, int base);

    std::string ToString(int base) const;
    static int Compare(const UnsignedBig& lhs, const UnsignedBig& rhs);

    bool IsZero() const;

    bool operator==(const UnsignedBig& rhs) const;
    bool operator<(const UnsignedBig& rhs) const;
    bool operator<=(const UnsignedBig& rhs) const;
    bool operator>(const UnsignedBig& rhs) const;

    UnsignedBig operator+(const UnsignedBig& rhs) const;
    UnsignedBig operator-(const UnsignedBig& rhs) const;
    UnsignedBig& operator-=(const UnsignedBig& rhs);
    UnsignedBig operator*(const UnsignedBig& rhs) const;
    UnsignedBig operator/(const UnsignedBig& rhs) const;

   private:
    std::vector<int> digits_;

    void DeleteLeadingZeros();
    size_t Size() const;
    void Clear();

    static void DeleteLeadingZeros(std::vector<int>* number);

    static void CheckBase(int base);
    static bool IsZero(const std::vector<int>& number);
    static int CharToInt(char digit_char, int base);
    static char IntToChar(int digit);
    static int DivideAndGetRemainder(std::vector<int>* value_vec,
                                     int cur_base, int final_base);
    static std::vector<int> ToAnotherNumberBase(std::vector<int> number,
                                                int cur_base, int final_base);

    static std::vector<int> StringToVector(const std::string& value_str,
                                           int base);
    static std::string VectorToString(const std::vector<int>& value_vec);

    void AddLowestDigit(int digit);
  };

  UnsignedBig unsigned_big_;

  bool IsZero() const;
};

}  // namespace big_num_arithmetic

std::ostream& operator<<(std::ostream& output_stream,
                         const big_num_arithmetic::BigInteger& big_integer);
std::istream& operator>>(std::istream& input_stream,
                         big_num_arithmetic::BigInteger& big_integer);

#endif  // BIG_INTEGER_H_
