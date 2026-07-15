CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -pedantic
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
AR = ar
ARFLAGS = rcs
TARGET = s21_matrix_oop.a
TEST_TARGET = test
LIB_SRC = s21_matrix_oop.cc
LIB_OBJ = $(LIB_SRC:.cc=.o)
TEST_SRC = s21_matrix_oop_tests.cc

OS := $(shell uname -s)
ifeq ($(OS),Darwin)
  TEST_LIBS = -lgtest -lgtest_main -pthread
else
  TEST_LIBS = -lgtest -lgtest_main -pthread
endif

.PHONY: all clean test gcov_report style clang format rebuild

all: $(TARGET)

$(TARGET): $(LIB_OBJ)
	$(AR) $(ARFLAGS) $@ $^
	-ranlib $@

%.o: %.cc s21_matrix_oop.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TARGET)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) $(TARGET) $(TEST_LIBS) -o $(TEST_TARGET)
	./$(TEST_TARGET)

gcov_report: clean
	$(CXX) $(CXXFLAGS) $(GCOV_FLAGS) -c s21_matrix_oop.cc -o s21_matrix_oop_gcov.o
	$(CXX) $(CXXFLAGS) -c s21_matrix_oop_tests.cc -o s21_matrix_oop_tests.o
	$(CXX) $(CXXFLAGS) $(GCOV_FLAGS) s21_matrix_oop_gcov.o s21_matrix_oop_tests.o $(TEST_LIBS) -o $(TEST_TARGET)
	./$(TEST_TARGET)
	lcov --ignore-errors mismatch --ignore-errors empty -t "s21_matrix_oop" -o coverage.info -c -d .
	lcov --ignore-errors mismatch --ignore-errors empty -e coverage.info "*/s21_matrix_oop.cc" -o coverage.info
	genhtml --ignore-errors mismatch --ignore-errors empty -o report coverage.info

style: clang

clang:
	clang-format -n *.cc *.h

format:
	clang-format -i *.cc *.h

rebuild: clean all

clean:
	rm -rf *.o *.a $(TEST_TARGET) *.gcno *.gcda *.gcov coverage.info report
