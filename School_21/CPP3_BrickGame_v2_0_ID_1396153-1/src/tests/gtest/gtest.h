#ifndef SRC_TESTS_GTEST_GTEST_H
#define SRC_TESTS_GTEST_GTEST_H

#ifndef S21_USE_GTEST_FALLBACK
#error "This fallback header must be used only when S21_USE_GTEST_FALLBACK is defined."
#endif

#include <cstdlib>
#include <exception>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace testing {

struct TestInfo {
  std::string name;
  std::function<void()> function;
};

inline std::vector<TestInfo> &Registry() {
  static std::vector<TestInfo> tests;
  return tests;
}

class RegisterTest {
 public:
  RegisterTest(const std::string &name, std::function<void()> function) {
    Registry().push_back(TestInfo{name, function});
  }
};

inline void InitGoogleTest(int *, char **) {}

inline int RUN_ALL_TESTS() {
  int failed = 0;
  for (const auto &test : Registry()) {
    try {
      test.function();
      std::cout << "[  OK  ] " << test.name << '\n';
    } catch (const std::exception &error) {
      ++failed;
      std::cerr << "[ FAIL ] " << test.name << ": " << error.what() << '\n';
    }
  }
  std::cout << Registry().size() - failed << " tests passed, " << failed
            << " failed.\n";
  return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

}  // namespace testing

#define RUN_ALL_TESTS() ::testing::RUN_ALL_TESTS()

#define TEST(SuiteName, TestName)                                           \
  static void SuiteName##_##TestName##_Body();                              \
  static ::testing::RegisterTest SuiteName##_##TestName##_Register(         \
      #SuiteName "." #TestName, &SuiteName##_##TestName##_Body);            \
  static void SuiteName##_##TestName##_Body()

#define S21_GTEST_EXPECT_BINARY(left, right, op, op_text)                    \
  do {                                                                       \
    auto s21_left_value = (left);                                             \
    auto s21_right_value = (right);                                           \
    if (!(s21_left_value op s21_right_value)) {                               \
      std::ostringstream s21_stream;                                          \
      s21_stream << __FILE__ << ':' << __LINE__ << " expected " #left " "    \
                 << op_text << " " #right << ", got " << s21_left_value      \
                 << " and " << s21_right_value;                              \
      throw std::runtime_error(s21_stream.str());                             \
    }                                                                        \
  } while (false)

#define EXPECT_EQ(left, right) S21_GTEST_EXPECT_BINARY(left, right, ==, "==")
#define ASSERT_EQ(left, right) EXPECT_EQ(left, right)
#define EXPECT_NE(left, right) S21_GTEST_EXPECT_BINARY(left, right, !=, "!=")
#define EXPECT_GT(left, right) S21_GTEST_EXPECT_BINARY(left, right, >, ">")
#define EXPECT_GE(left, right) S21_GTEST_EXPECT_BINARY(left, right, >=, ">=")
#define EXPECT_LT(left, right) S21_GTEST_EXPECT_BINARY(left, right, <, "<")
#define EXPECT_LE(left, right) S21_GTEST_EXPECT_BINARY(left, right, <=, "<=")

#define EXPECT_TRUE(value) EXPECT_NE((value), false)
#define EXPECT_FALSE(value) EXPECT_EQ((value), false)
#define ASSERT_TRUE(value) EXPECT_TRUE(value)
#define ASSERT_FALSE(value) EXPECT_FALSE(value)
#define ASSERT_NE(left, right) EXPECT_NE(left, right)

#endif  // SRC_TESTS_GTEST_GTEST_H
