CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Werror -pedantic -I.
TEST_FLAGS := -lgtest -lgtest_main -pthread
TEST_SOURCES := $(wildcard tests/*.cc)
TEST_TARGET := s21_containers_tests

PLUS_TEST_SOURCES := tests/test_array.cc tests/test_multiset.cc

.PHONY: all clean test test_plus

all: test

test: $(TEST_TARGET)
	./$(TEST_TARGET)

test_plus: $(TEST_TARGET)
	./$(TEST_TARGET) --gtest_filter=S21ArrayTest*:S21MultisetTest*

$(TEST_TARGET): $(TEST_SOURCES) s21_*.h
	$(CXX) $(CXXFLAGS) $(TEST_SOURCES) -o $(TEST_TARGET) $(TEST_FLAGS)

clean:
	rm -f $(TEST_TARGET) *.o *.a *.gcno *.gcda *.info
	rm -rf report
