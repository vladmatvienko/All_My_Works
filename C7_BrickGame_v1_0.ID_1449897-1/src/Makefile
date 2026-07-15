CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c11 -I.
TEST_CFLAGS = $(CFLAGS) -DS21_TETRIS_TEST
GCOVFLAGS = --coverage

BUILD_DIR = build
INSTALL_DIR = brickgame_install
DIST_NAME = brickgame_tetris

TETRIS_DIR = brick_game/tetris
CLI_DIR = gui/cli
TEST_DIR = tests

APP = $(BUILD_DIR)/brick_game_tetris
TEST_BIN = $(BUILD_DIR)/test_tetris

TETRIS_SRC = $(TETRIS_DIR)/tetris.c
CLI_SRC = $(CLI_DIR)/main.c $(CLI_DIR)/frontend.c
TEST_SRC = $(TEST_DIR)/test_tetris.c

TETRIS_OBJ = $(BUILD_DIR)/tetris.o
CLI_OBJ = $(BUILD_DIR)/main.o $(BUILD_DIR)/frontend.o

NCURSES_LIBS = -lncurses

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	CHECK_CFLAGS := $(shell pkg-config --cflags check 2>/dev/null)
	CHECK_LIBS := $(shell pkg-config --libs check 2>/dev/null || echo -lcheck)
else
	CHECK_CFLAGS := $(shell pkg-config --cflags check 2>/dev/null)
	CHECK_LIBS := $(shell pkg-config --libs check 2>/dev/null || echo -lcheck -lm -lpthread -lrt -lsubunit)
endif

.PHONY: all install uninstall clean dvi dist test gcov_report clang format cppcheck rebuild

all: $(APP)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(APP): $(TETRIS_OBJ) $(CLI_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(NCURSES_LIBS)

$(BUILD_DIR)/tetris.o: $(TETRIS_DIR)/tetris.c $(TETRIS_DIR)/tetris.h $(TETRIS_DIR)/tetris_backend.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: $(CLI_DIR)/main.c $(CLI_DIR)/frontend.h $(TETRIS_DIR)/tetris.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/frontend.o: $(CLI_DIR)/frontend.c $(CLI_DIR)/frontend.h $(TETRIS_DIR)/tetris.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

install: all
	mkdir -p $(INSTALL_DIR)/bin
	cp $(APP) $(INSTALL_DIR)/bin/brick_game_tetris

uninstall:
	rm -rf $(INSTALL_DIR)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(INSTALL_DIR)
	rm -rf $(DIST_NAME)
	rm -f $(DIST_NAME).tar.gz
	rm -f $(DIST_NAME).zip
	rm -f *.gcda *.gcno *.gcov
	rm -f $(TETRIS_DIR)/*.gcda $(TETRIS_DIR)/*.gcno $(TETRIS_DIR)/*.gcov
	rm -f $(TEST_DIR)/*.gcda $(TEST_DIR)/*.gcno $(TEST_DIR)/*.gcov
	rm -f tetris_high_score.dat

rebuild: clean all

dvi:
	mkdir -p $(BUILD_DIR)/docs
	cp fsm_tetris.md $(BUILD_DIR)/docs/fsm_tetris.md
	@echo "Documentation copied to $(BUILD_DIR)/docs/fsm_tetris.md"

dist: clean
	mkdir -p $(DIST_NAME)
	cp -R Makefile .clang-format .gitkeep fsm_tetris.md brick_game gui tests $(DIST_NAME)/
	zip -r $(DIST_NAME).zip $(DIST_NAME)
	rm -rf $(DIST_NAME)

test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TETRIS_SRC) $(TEST_SRC) $(TETRIS_DIR)/tetris.h $(TETRIS_DIR)/tetris_backend.h | $(BUILD_DIR)
	$(CC) $(TEST_CFLAGS) $(CHECK_CFLAGS) $(TETRIS_SRC) $(TEST_SRC) -o $@ $(CHECK_LIBS)

gcov_report: clean
	mkdir -p $(BUILD_DIR)
	$(CC) $(TEST_CFLAGS) $(GCOVFLAGS) $(CHECK_CFLAGS) $(TETRIS_SRC) $(TEST_SRC) -o $(TEST_BIN) $(CHECK_LIBS)
	./$(TEST_BIN)
	lcov -t "brick_game_tetris" -o $(BUILD_DIR)/coverage.info -c -d .
	lcov --remove $(BUILD_DIR)/coverage.info '*/tests/*' -o $(BUILD_DIR)/coverage.info
	genhtml -o $(BUILD_DIR)/report $(BUILD_DIR)/coverage.info
	@echo "Coverage report: $(BUILD_DIR)/report/index.html"

clang:
	clang-format -n $(TETRIS_DIR)/*.c $(TETRIS_DIR)/*.h $(CLI_DIR)/*.c $(CLI_DIR)/*.h $(TEST_DIR)/*.c

format:
	clang-format -i $(TETRIS_DIR)/*.c $(TETRIS_DIR)/*.h $(CLI_DIR)/*.c $(CLI_DIR)/*.h $(TEST_DIR)/*.c

cppcheck:
	cppcheck --enable=all --std=c11 --check-level=exhaustive --disable=information \
	--suppress=missingIncludeSystem --suppress=missingInclude --suppress=checkersReport \
	$(TETRIS_DIR) $(CLI_DIR) $(TEST_DIR)