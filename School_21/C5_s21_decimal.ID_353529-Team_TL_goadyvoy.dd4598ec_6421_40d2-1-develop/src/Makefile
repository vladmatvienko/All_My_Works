CC = gcc
CFLAGS = -Wall -Wextra  -std=c11 -Werror
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

RED = \033[0;31m
DARKYELLOW = \033[0;33m
NC = \033[0m# No Color

HAVE_PKG_CONFIG := $(shell command -v pkg-config 2>/dev/null)

ifdef HAVE_PKG_CONFIG
CHECK_FLAGS := $(shell pkg-config --cflags --libs check 2>/dev/null)
else
CHECK_FLAGS := -I/usr/include/check -lcheck -lsubunit -lm -lpthread -lrt
endif

LIB_SRC = s21_arithmetic.c s21_comparison.c s21_convertor.c s21_other.c s21_support.c
LIB_OBJ = $(LIB_SRC:.c=.o)
LIB_NAME = s21_decimal.a

TEST_SRC = s21_decimal_test.c tests/support_test.c tests/arifmetic_tests.c tests/compare_tests.c tests/conversion_tests.c tests/other_tests.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_TARGET = test_decimal

GCOV_DIR = gcov_report
GCOV_INFO = coverage.info

.PHONY: all clean test gcov_report

all: clean $(LIB_NAME)

$(LIB_NAME): $(LIB_OBJ)
	@echo "${DARKYELLOW}Buiding $(LIB_NAME)...${NC}"
	ar rcs $@ $^
	ranlib $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

tests/%.o: tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_TARGET): $(TEST_OBJ) $(LIB_NAME)
	$(CC) $(CFLAGS) $^ -o $@ $(CHECK_FLAGS)

test: $(TEST_TARGET)
	@echo "${DARKYELLOW}Running tests:${NC}"
	./$(TEST_TARGET)

gcov_report: $(TEST_OBJ) $(LIB_OBJ)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(LIB_SRC) $(TEST_SRC) -o $(TEST_TARGET) $(CHECK_FLAGS)
	@echo "${DARKYELLOW}Running tests:${NC}"
	./$(TEST_TARGET)

	@mkdir -p $(GCOV_DIR)
	@echo "${DARKYELLOW}Text coverage:${NC}"
	@gcov *.gcda 2>/dev/null | \
		grep -E "^File '(.*)'" -A 1 | \
		grep -E "^Lines executed:|^File '" | \
		paste -d " " - -
	@mv *.gcov $(GCOV_DIR)/

	@if type lcov >/dev/null 2>&1; then \
		echo "${DARKYELLOW}Generating HTML report...${NC}"; \
		lcov -t "$(TEST_TARGET)" -o $(GCOV_INFO) -c -d .; \
		genhtml -o $(GCOV_DIR) $(GCOV_INFO); \
		rm -f $(GCOV_INFO); \
		echo "HTML report available at ${DARKYELLOW}$(GCOV_DIR)/index.html${NC}"; \
	else \
		echo "Please install '${RED}lcov${NC}' for view html file"; \
	fi
	
	rm -f *.gcda *.gcno *.info

clean:
	@echo "${DARKYELLOW}Cleaning...${NC}"
	rm -f $(LIB_NAME) $(TEST_TARGET) $(LIB_OBJ) $(TEST_OBJ)
	rm -rf $(GCOV_DIR)
	rm -f *.gcno *.gcda *.info *.gcov
	rm -f tests/*.o tests/*.gcno tests/*.gcda
