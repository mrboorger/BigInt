#include "big_integer.h"

#include <gmock/gmock.h>

namespace big_num_arithmetic {

#define EXPECT_EXCEPTION(function, exception_type, exception_message) {\
  bool __has_except = false;                                        \
  try {                                                             \
    function;                                                       \
  } catch (exception_type& exception) {                             \
    EXPECT_STREQ(exception.what(), exception_message);              \
    __has_except = true;                                            \
  } catch (...) {                                                   \
    EXPECT_TRUE(false) << "Wrong exception type";                   \
    __has_except = true;                                            \
  }                                                                 \
  EXPECT_TRUE(__has_except) << "Expected an exception";             \
}

#define EXPECT_EXCEPTION_TYPE(function, exception_type) {\
  bool __has_except = false;                                        \
  try {                                                             \
    function;                                                       \
  } catch (exception_type& exception) {                             \
    __has_except = true;                                            \
  } catch (...) {                                                   \
    EXPECT_TRUE(false) << "Wrong exception type";                   \
    __has_except = true;                                            \
  }                                                                 \
  EXPECT_TRUE(__has_except) << "Expected an exception";             \
}

class Tester {

 public:
// TEST(BigInteger, Sign) {
//
// }
//
// TEST(BigInteger, Negate) {
//
// }
//
// TEST(BigInteger, Abs) {
//
// }

  static void ConstructorTest() {
    {
      BigInteger big(9347433);
      std::vector<int> expect = {33, 66, 115, 2};
      EXPECT_TRUE(big.unsigned_big_.digits_ == expect);
      EXPECT_EQ(big.sign_, 1);
    }
    {
      BigInteger big(-9347433);
      std::vector<int> expect = {33, 66, 115, 2};
      EXPECT_EQ(big.unsigned_big_.digits_, expect);
      EXPECT_EQ(big.sign_, -1);
    }
    {
      BigInteger big(0);
      std::vector<int> expect = {0};
      EXPECT_EQ(big.unsigned_big_.digits_, expect);
      EXPECT_EQ(big.sign_, 0);
    }
  }

  static void FromStringTest() {
    {
      BigInteger big;
      big.unsigned_big_.digits_ = {23, 4, 44};
      big = BigInteger::FromString("9347433", 10);
      std::vector<int> expect = {33, 66, 115, 2};
      EXPECT_EQ(big.unsigned_big_.digits_, expect);
      EXPECT_EQ(big.sign_, 1);
    }
    {
      BigInteger big;
      big = BigInteger::FromString("-0000", 10);
      std::vector<int> expect = {0};
      EXPECT_EQ(big.unsigned_big_.digits_, expect);
      EXPECT_EQ(big.sign_, 0);
    }
  }
  static void ToStringTest() {
    BigInteger big;
    big = BigInteger::FromString("9347433", 10);
    EXPECT_EQ(big.ToString(10), "9347433");
  }

  template<class T1, class T2>
  static void ExpectGreater(const T1& lhs, const T2& rhs) {
    EXPECT_FALSE(lhs == rhs);
    EXPECT_FALSE(rhs == lhs);
    EXPECT_TRUE(lhs != rhs);
    EXPECT_TRUE(rhs != lhs);
    EXPECT_FALSE(lhs < rhs);
    EXPECT_TRUE(rhs < lhs);
    EXPECT_TRUE(lhs > rhs);
    EXPECT_FALSE(rhs > lhs);
    EXPECT_FALSE(lhs <= rhs);
    EXPECT_TRUE(rhs <= lhs);
    EXPECT_TRUE(lhs >= rhs);
    EXPECT_FALSE(rhs >= lhs);
  }
  template<class T1, class T2>
  static void ExpectLess(const T1& lhs, const T2& rhs) {
    ExpectGreater(rhs, lhs);
  }
  template<class T1, class T2>
  static void ExpectEqual(const T1& lhs, const T2& rhs) {
    EXPECT_TRUE(lhs == rhs);
    EXPECT_TRUE(rhs == lhs);
    EXPECT_FALSE(lhs != rhs);
    EXPECT_FALSE(rhs != lhs);
    EXPECT_FALSE(lhs < rhs);
    EXPECT_FALSE(rhs < lhs);
    EXPECT_FALSE(lhs > rhs);
    EXPECT_FALSE(rhs > lhs);
    EXPECT_TRUE(lhs <= rhs);
    EXPECT_TRUE(rhs <= lhs);
    EXPECT_TRUE(lhs >= rhs);
    EXPECT_TRUE(rhs >= lhs);
  }

  static void ComparisonOperatorsTest() {
    {
      BigInteger lhs;
      BigInteger rhs;
      lhs = BigInteger::FromString("-8934987598374857938598347598283464834344",
                                   10);
      rhs = BigInteger::FromString("-8934987598374857938598347598283464834344",
                                   10);
      ExpectEqual(lhs, rhs);
    }
    {
      BigInteger lhs;
      BigInteger rhs;
      lhs = BigInteger::FromString("8934987598374857938598347598283464834344",
                                   10);
      rhs = BigInteger::FromString("8934987598374857938598347598283464834344",
                                   10);
      ExpectEqual(lhs, rhs);
    }
    {
      BigInteger lhs(0);
      BigInteger rhs(0);
      ExpectEqual(lhs, rhs);
    }
    {
      BigInteger lhs(0);
      BigInteger rhs(-9);
      ExpectGreater(lhs, rhs);
    }
    {
      BigInteger lhs(9);
      BigInteger rhs(0);
      ExpectGreater(lhs, rhs);
    }
    {
      BigInteger lhs;
      lhs = BigInteger::FromString("8934987598374857938598347598283464834344",
                                   10);
      BigInteger rhs(0);
      ExpectGreater(lhs, rhs);
    }
    {
      BigInteger lhs(0);
      BigInteger rhs;
      rhs = BigInteger::FromString("-8934987598374857938598347598283464834344",
                                   10);
      ExpectGreater(lhs, rhs);
    }
    {
      BigInteger lhs;
      BigInteger rhs;
      lhs = BigInteger::FromString("-8934289998374857938598347598283464834344",
                                   10);
      rhs = BigInteger::FromString("-8934487998374857938598347598283464834344",
                                   10);
      ExpectGreater(lhs, rhs);
    }
    {
      BigInteger lhs;
      BigInteger rhs;
      lhs = BigInteger::FromString("-993428999837485793859834759828346483434",
                                   10);
      rhs = BigInteger::FromString("-8934289998374857938598347598283464834344",
                                   10);
      ExpectGreater(lhs, rhs);
    }
    {
      BigInteger lhs;
      BigInteger rhs;
      lhs = BigInteger::FromString("8934598734987563476987983747349348533498",
                                   10);
      rhs = BigInteger::FromString("-8934598734987563476987983747349348533498",
                                   10);
      ExpectGreater(lhs, rhs);
    }
    {
      BigInteger lhs;
      BigInteger rhs;
      lhs =
          BigInteger::FromString("893459873498756347698798374734934853349", 10);
      rhs = BigInteger::FromString("-8934598734987563476987983747349348533498",
                                   10);
      ExpectGreater(lhs, rhs);
    }
    {
      BigInteger lhs;
      BigInteger rhs;
      lhs = BigInteger::FromString("8934598734987593476987943747349348533498",
                                   10);
      rhs = BigInteger::FromString("8934598734987563476987983747349348533498",
                                   10);
      ExpectGreater(lhs, rhs);
    }
    {
      BigInteger lhs;
      BigInteger rhs;
      lhs = BigInteger::FromString("19345987349875934769879437473493485334980",
                                   10);
      rhs = BigInteger::FromString("8934598734987563476987983747349348533498",
                                   10);
      ExpectGreater(lhs, rhs);
    }

    {
      BigInteger lhs(0);
      int64_t rhs = 0;
      ExpectEqual(lhs, rhs);
      ExpectEqual(rhs, lhs);
    }
    {
      int64_t lhs = 435344;
      BigInteger rhs;
      rhs = BigInteger::FromString("-8934987598374857938598347598283464834344",
                                   10);
      ExpectGreater(lhs, rhs);
      ExpectLess(rhs, lhs);
    }
    {
      BigInteger lhs;
      int64_t rhs = 0;
      lhs = BigInteger::FromString("8934987598374857938598347598283464834344",
                                   10);
      ExpectGreater(lhs, rhs);
      ExpectLess(rhs, lhs);
    }
    {
      int64_t lhs = 73487583;
      BigInteger rhs(0);
      ExpectGreater(lhs, rhs);
      ExpectLess(rhs, lhs);
    }
    {
      BigInteger lhs(0);
      int64_t rhs = -73487583;
      ExpectGreater(lhs, rhs);
      ExpectLess(rhs, lhs);
    }
    {
      BigInteger lhs(785738444);
      int64_t rhs = 785738444;
      ExpectEqual(lhs, rhs);
      ExpectEqual(rhs, lhs);
    }
    {
      BigInteger lhs(-785738444);
      int64_t rhs = -785738444;
      ExpectEqual(lhs, rhs);
      ExpectEqual(rhs, lhs);
    }
    {
      int64_t lhs = 3454464;
      BigInteger rhs;
      rhs = BigInteger::FromString("-8934987598374857938598347598283464834344",
                                   10);
      ExpectGreater(lhs, rhs);
      ExpectLess(rhs, lhs);
    }
    {
      BigInteger lhs;
      int64_t rhs = 3457484;
      lhs = BigInteger::FromString("8934987598374857938598347598283464834344",
                                   10);
      ExpectGreater(lhs, rhs);
      ExpectLess(rhs, lhs);
    }
    {
      int64_t lhs = 73487583;
      BigInteger rhs(343454);
      ExpectGreater(lhs, rhs);
      ExpectLess(rhs, lhs);
    }
    {
      BigInteger lhs;
      lhs = BigInteger::FromString(
          "4857348568734658736487563478568374344344544566",
          10);
      int64_t rhs = -73487583;
      ExpectGreater(lhs, rhs);
      ExpectLess(rhs, lhs);
    }
  }

  static void ArithmeticOperatorsTest() {
    {
      BigInteger num(0);
      BigInteger res = num + num;
      std::vector<int> digits = {0};
      EXPECT_EQ(res.sign_, 0);
      //
      EXPECT_EQ(res.unsigned_big_.digits_, digits);
      res = num - num;
      EXPECT_EQ(res.sign_, 0);
      EXPECT_EQ(res.unsigned_big_.digits_, digits);
      res = num * num;
      EXPECT_EQ(res.sign_, 0);
      EXPECT_EQ(res.unsigned_big_.digits_, digits);
      EXPECT_EXCEPTION_TYPE(num / num, big_num_arithmetic::DivisionByZeroError);
    }
    {
      BigInteger lhs(0);
      BigInteger rhs;
      rhs = BigInteger::FromString(
          "38457938475893749868534568358236589345346709791403",
          10);
      std::vector<int> digits = rhs.unsigned_big_.digits_;
      BigInteger res = lhs + rhs;
      EXPECT_EQ(res.sign_, 1);
      EXPECT_EQ(res.unsigned_big_.digits_, digits);
      res = rhs + lhs;
      EXPECT_EQ(res.sign_, 1);
      EXPECT_EQ(res.unsigned_big_.digits_, digits);

      res = lhs - rhs;
      EXPECT_EQ(res.sign_, -1);
      EXPECT_EQ(res.unsigned_big_.digits_, digits);
      res = rhs - lhs;
      EXPECT_EQ(res.sign_, 1);
      EXPECT_EQ(res.unsigned_big_.digits_, digits);

      res = lhs * rhs;
      digits = {0};
      EXPECT_EQ(res.sign_, 0);
      EXPECT_EQ(res.unsigned_big_.digits_, digits);
      res = rhs * lhs;
      EXPECT_EQ(res.sign_, 0);
      EXPECT_EQ(res.unsigned_big_.digits_, digits);

      res = lhs / rhs;
      digits = {0};
      EXPECT_EQ(res.sign_, 0);
      EXPECT_EQ(res.unsigned_big_.digits_, digits);
      EXPECT_EXCEPTION_TYPE(rhs / lhs,
                            big_num_arithmetic::DivisionByZeroError);
    }
    {
      BigInteger lhs(0);
      BigInteger rhs;
      rhs = BigInteger::FromString(
          "-38457938475893749868534568358236589345346709791403",
          10);
      std::vector<int> digits = rhs.unsigned_big_.digits_;
      BigInteger res = lhs + rhs;
      EXPECT_EQ(res.sign_, -1);
      EXPECT_EQ(res.unsigned_big_.digits_, digits);
      res = rhs + lhs;
      EXPECT_EQ(res.sign_, -1);
      EXPECT_EQ(res.unsigned_big_.digits_, digits);

      res = lhs - rhs;
      EXPECT_EQ(res.sign_, 1);
      EXPECT_EQ(res.unsigned_big_.digits_, digits);
      res = rhs - lhs;
      EXPECT_EQ(res.sign_, -1);
      EXPECT_EQ(res.unsigned_big_.digits_, digits);

      res = lhs * rhs;
      digits = {0};
      EXPECT_EQ(res.sign_, 0);
      EXPECT_EQ(res.unsigned_big_.digits_, digits);
      res = rhs * lhs;
      EXPECT_EQ(res.sign_, 0);
      EXPECT_EQ(res.unsigned_big_.digits_, digits);

      res = lhs / rhs;
      digits = {0};
      EXPECT_EQ(res.sign_, 0);
      EXPECT_EQ(res.unsigned_big_.digits_, digits);
      EXPECT_EXCEPTION_TYPE(rhs / lhs,
                            big_num_arithmetic::DivisionByZeroError);
    }
    {
      BigInteger lhs;
      lhs = BigInteger::FromString(
          "7438573984298347562875298635824683784568263847627983567283468", 10);
      BigInteger rhs;
      rhs = BigInteger::FromString("364576347856253656324767753643224452", 10);
      BigInteger expect;

      expect = BigInteger::FromString(
          "7438573984298347562875299000401031640821920172395737210507920",
          10);
      BigInteger res = lhs + rhs;
      EXPECT_EQ(res.sign_, 1);
      EXPECT_EQ(res.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      res = rhs + lhs;
      EXPECT_EQ(res.sign_, 1);
      EXPECT_EQ(res.unsigned_big_.digits_, expect.unsigned_big_.digits_);

      expect = BigInteger::FromString(
          "7438573984298347562875298271248335928314607522860229924059016",
          10);
      res = lhs - rhs;
      EXPECT_EQ(res.sign_, 1);
      EXPECT_EQ(res.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      res = rhs - lhs;
      EXPECT_EQ(res.sign_, -1);
      EXPECT_EQ(res.unsigned_big_.digits_, expect.unsigned_big_.digits_);

      res = lhs * rhs;
      std::string str = "27119281364540330845071848518432151699";
      str += "44528844077614529054774254633269636408505446338317832959536";
      expect = BigInteger::FromString(str, 10);
      EXPECT_EQ(res.sign_, 1);
      EXPECT_EQ(res.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      res = rhs * lhs;
      EXPECT_EQ(res.sign_, 1);
      EXPECT_EQ(res.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      //
      res = lhs / rhs;
      expect = BigInteger::FromString("20403336716816452982551356", 10);
      EXPECT_EQ(res.sign_, 1);
      EXPECT_EQ(res.unsigned_big_.digits_, expect.unsigned_big_.digits_);

      res = rhs / lhs;
      expect = BigInteger::FromString("0", 10);
      EXPECT_EQ(res.sign_, 0);
      EXPECT_EQ(res.unsigned_big_.digits_, expect.unsigned_big_.digits_);
    }
    {
      BigInteger lhs;
      lhs = BigInteger::FromString(
          "-7438573984298347562875298635824683784568263847627983567283468", 10);
      BigInteger rhs;
      rhs = BigInteger::FromString("-364576347856253656324767753643224452", 10);
      BigInteger expect;

      expect = BigInteger::FromString(
          "-7438573984298347562875299000401031640821920172395737210507920",
          10);
      BigInteger res = lhs + rhs;
      EXPECT_EQ(res.sign_, -1);
      EXPECT_EQ(res.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      res = rhs + lhs;
      EXPECT_EQ(res.sign_, -1);
      EXPECT_EQ(res.unsigned_big_.digits_, expect.unsigned_big_.digits_);

      expect = BigInteger::FromString(
          "-7438573984298347562875298271248335928314607522860229924059016",
          10);
      res = lhs - rhs;
      EXPECT_EQ(res.sign_, -1);
      EXPECT_EQ(res.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      res = rhs - lhs;
      EXPECT_EQ(res.sign_, 1);
      EXPECT_EQ(res.unsigned_big_.digits_, expect.unsigned_big_.digits_);

      res = lhs * rhs;
      std::string str = "27119281364540330845071848518432151699";
      str += "44528844077614529054774254633269636408505446338317832959536";
      expect = BigInteger::FromString(str, 10);
      EXPECT_EQ(res.sign_, 1);
      EXPECT_EQ(res.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      res = rhs * lhs;
      EXPECT_EQ(res.sign_, 1);
      EXPECT_EQ(res.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      //
      res = lhs / rhs;
      expect = BigInteger::FromString("20403336716816452982551356", 10);
      EXPECT_EQ(res.sign_, 1);
      EXPECT_EQ(res.unsigned_big_.digits_, expect.unsigned_big_.digits_);

      res = rhs / lhs;
      expect = BigInteger::FromString("0", 10);
      EXPECT_EQ(res.sign_, 0);
      EXPECT_EQ(res.unsigned_big_.digits_, expect.unsigned_big_.digits_);
    }
  }

  static void UnaryOperatorsTest() {
    {
      BigInteger num;
      num = BigInteger::FromString(
          "899999999994565549999235339929999999999999999",
          10);
      EXPECT_EQ((+num).unsigned_big_.digits_, num.unsigned_big_.digits_);
      EXPECT_EQ((+num).sign_, 1);

      num = BigInteger::FromString(
          "-899999999994565549999235339929999999999999999",
          10);
      EXPECT_EQ((+num).unsigned_big_.digits_, num.unsigned_big_.digits_);
      EXPECT_EQ((+num).sign_, -1);

      num = BigInteger::FromString("0", 10);
      EXPECT_EQ((+num).unsigned_big_.digits_, num.unsigned_big_.digits_);
      EXPECT_EQ((+num).sign_, 0);
    }
    {
      BigInteger num;
      num = BigInteger::FromString(
          "899999999994565549999235339929999999999999999",
          10);
      EXPECT_EQ((-num).unsigned_big_.digits_, num.unsigned_big_.digits_);
      EXPECT_EQ((-num).sign_, -1);
      EXPECT_EQ((-(-num)).unsigned_big_.digits_, num.unsigned_big_.digits_);
      EXPECT_EQ((-(-num)).sign_, 1);

      num = BigInteger::FromString(
          "-899999999994565549999235339929999999999999999",
          10);
      EXPECT_EQ((-num).unsigned_big_.digits_, num.unsigned_big_.digits_);
      EXPECT_EQ((-num).sign_, 1);

      num = BigInteger::FromString("0", 10);
      EXPECT_EQ((-num).unsigned_big_.digits_, num.unsigned_big_.digits_);
      EXPECT_EQ((-num).sign_, 0);
    }
    {
      BigInteger num;
      num = BigInteger::FromString(
          "89999999999999456554999923534239929999999999999999",
          10);
      BigInteger expect_1;
      expect_1 = BigInteger::FromString(
          "89999999999999456554999923534239929999999999999999",
          10);
      BigInteger expect_2;
      expect_2 = BigInteger::FromString(
          "89999999999999456554999923534239930000000000000000",
          10);
      EXPECT_EQ((++num).unsigned_big_.digits_, expect_2.unsigned_big_.digits_);
      EXPECT_EQ(num.unsigned_big_.digits_, expect_2.unsigned_big_.digits_);
      EXPECT_EQ(num.sign_, 1);
      num = expect_1;
      EXPECT_EQ((++num).sign_, 1);

      num = expect_1;
      EXPECT_EQ((num++).unsigned_big_.digits_, expect_1.unsigned_big_.digits_);
      EXPECT_EQ(num.unsigned_big_.digits_, expect_2.unsigned_big_.digits_);
      EXPECT_EQ(num.sign_, 1);
      num = expect_1;
      EXPECT_EQ((num++).sign_, 1);

    }
    {
      BigInteger num;
      num = BigInteger::FromString(
          "89999999999999456554999923534239929999999999999999",
          10);
      BigInteger expect_1;
      expect_1 = BigInteger::FromString(
          "89999999999999456554999923534239929999999999999999",
          10);
      BigInteger expect_2;
      expect_2 = BigInteger::FromString(
          "89999999999999456554999923534239929999999999999998",
          10);
      EXPECT_EQ((--num).unsigned_big_.digits_, expect_2.unsigned_big_.digits_);
      EXPECT_EQ(num.unsigned_big_.digits_, expect_2.unsigned_big_.digits_);
      EXPECT_EQ(num.sign_, 1);
      num = expect_1;
      EXPECT_EQ((--num).sign_, 1);

      num = expect_1;
      EXPECT_EQ((num--).unsigned_big_.digits_, expect_1.unsigned_big_.digits_);
      EXPECT_EQ(num.unsigned_big_.digits_, expect_2.unsigned_big_.digits_);
      EXPECT_EQ(num.sign_, 1);
      num = expect_1;
      EXPECT_EQ((num--).sign_, 1);
    }
    {
      BigInteger num;
      num = BigInteger::FromString("9223372036854775808", 10);
      EXPECT_EXCEPTION(static_cast<int64_t>(num),
                       std::runtime_error,
                       "int64_t overflow");
      num.Negate();
      EXPECT_EXCEPTION(static_cast<int64_t>(num),
                       std::runtime_error,
                       "int64_t overflow");

      num = BigInteger::FromString("-220364745807", 10);
      EXPECT_EQ(static_cast<int64_t>(num), -220364745807);
    }
  }
  static void IOOperatorsTest() {
    {
      std::istringstream
          input("0 -0 723482399823497346283849299 -8798237856378282333250033 "
                "00 -00 07234062523463024671003233 -07234062523463024671003233 "
                "0x0 -0x0 0x89a90154d8ef23430 -0x89a90154d8ef23430");
      BigInteger number;
      input >> number;
      BigInteger expect = BigInteger::FromString("0", 10);
      EXPECT_EQ(number.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      EXPECT_EQ(number.sign_, 0);


      input >> number;
      EXPECT_EQ(number.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      EXPECT_EQ(number.sign_, 0);

      input >> number;
      expect = BigInteger::FromString("723482399823497346283849299", 10);
      EXPECT_EQ(number.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      EXPECT_EQ(number.sign_, 1);

      input >> number;
      expect = BigInteger::FromString("-8798237856378282333250033", 10);
      EXPECT_EQ(number.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      EXPECT_EQ(number.sign_, -1);

      input.setf(std::ios::oct);
      input >> number;
      expect = BigInteger::FromString("0", 8);
      EXPECT_EQ(number.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      EXPECT_EQ(number.sign_, 0);


      input >> number;
      EXPECT_EQ(number.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      EXPECT_EQ(number.sign_, 0);

      input >> number;
      expect = BigInteger::FromString("07234062523463024671003233", 8);
      EXPECT_EQ(number.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      EXPECT_EQ(number.sign_, 1);

      input >> number;
      expect = BigInteger::FromString("-07234062523463024671003233", 8);
      EXPECT_EQ(number.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      EXPECT_EQ(number.sign_, -1);

      input.unsetf(std::ios::oct);
      input.setf(std::ios::hex);
      input >> number;
      expect = BigInteger::FromString("0", 16);
      EXPECT_EQ(number.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      EXPECT_EQ(number.sign_, 0);

      input >> number;
      EXPECT_EQ(number.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      EXPECT_EQ(number.sign_, 0);

      input >> number;
      expect = BigInteger::FromString("89a90154d8ef23430", 16);
      EXPECT_EQ(number.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      EXPECT_EQ(number.sign_, 1);

      input >> number;
      expect = BigInteger::FromString("-89a90154d8ef23430", 16);
      EXPECT_EQ(number.unsigned_big_.digits_, expect.unsigned_big_.digits_);
      EXPECT_EQ(number.sign_, -1);
    }
    {
      std::ostringstream output;
      BigInteger number =
          BigInteger::FromString("9879878234993055723947593275024833", 10);
      output << number;
      std::string expect = "9879878234993055723947593275024833";
      std::string current;
      EXPECT_EQ(output.str(), expect);
    }
  }
};

TEST(BigInteger, Constructor) {
  Tester::ConstructorTest();
}

TEST(BigInteger, FromString) {
  Tester::FromStringTest();
}

TEST(BigInteger, ToString) {
  Tester::ToStringTest();
}

TEST(BigInteger, ComparisonOperators) {
  Tester::ComparisonOperatorsTest();
}

TEST(BigInteger, ArithmeticOperators) {
  Tester::ArithmeticOperatorsTest();
}

TEST(BigInteger, UnaryOperators) {
  Tester::UnaryOperatorsTest();
}

TEST(BigInteger, IOOperators) {
  Tester::IOOperatorsTest();
}

}