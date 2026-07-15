CC = gcc
CXX = g++

CFLAGS = -Wall -Wextra -Werror -std=c11 -I.
CXXFLAGS = -Wall -Wextra -Werror -std=c++20 -I.
GCOVFLAGS = --coverage

BUILD_DIR = build
INSTALL_DIR = brickgame_install
DIST_NAME = brickgame_v2

COMMON_DIR = brick_game/common
TETRIS_DIR = brick_game/tetris
SNAKE_DIR = brick_game/snake
CLI_DIR = gui/cli
DESKTOP_DIR = gui/desktop
TEST_DIR = tests

APP_CLI = $(BUILD_DIR)/brick_game_cli
APP_DESKTOP = $(BUILD_DIR)/brick_game_desktop
TEST_BIN = $(BUILD_DIR)/test_brick_game

TETRIS_SRC = $(TETRIS_DIR)/tetris.c
SNAKE_SRC = $(SNAKE_DIR)/snake.cpp $(SNAKE_DIR)/snake_model.cpp $(SNAKE_DIR)/snake_controller.cpp
CLI_SRC = $(CLI_DIR)/main.cpp $(CLI_DIR)/frontend.cpp
DESKTOP_SRC = $(DESKTOP_DIR)/main.cpp $(DESKTOP_DIR)/main_window.cpp $(DESKTOP_DIR)/game_controller.cpp
TEST_SRC = $(TEST_DIR)/gtest_main.cpp $(TEST_DIR)/test_tetris.cpp $(TEST_DIR)/test_snake.cpp

TETRIS_OBJ = $(BUILD_DIR)/tetris.o
SNAKE_OBJ = $(BUILD_DIR)/snake.o $(BUILD_DIR)/snake_model.o $(BUILD_DIR)/snake_controller.o
CLI_OBJ = $(BUILD_DIR)/cli_main.o $(BUILD_DIR)/cli_frontend.o
DESKTOP_OBJ = $(BUILD_DIR)/desktop_main.o $(BUILD_DIR)/desktop_main_window.o $(BUILD_DIR)/desktop_game_controller.o

HAVE_NCURSES := $(shell echo "#include <ncurses.h>" | $(CXX) -E -x c++ - >/dev/null 2>&1 && echo yes || echo no)
ifeq ($(HAVE_NCURSES),yes)
  NCURSES_LIBS := -lncurses
else
  NCURSES_LIBS :=
endif

GTEST_PKG := $(shell pkg-config --exists gtest 2>/dev/null && echo yes || echo no)
ifeq ($(GTEST_PKG),yes)
  GTEST_CXXFLAGS := $(shell pkg-config --cflags gtest)
  GTEST_LIBS := $(shell pkg-config --libs gtest)
else
  GTEST_CXXFLAGS := -I$(TEST_DIR) -DS21_USE_GTEST_FALLBACK
  GTEST_LIBS :=
endif

QT6_PKG := $(shell pkg-config --exists Qt6Widgets 2>/dev/null && echo yes || echo no)
QT5_PKG := $(shell pkg-config --exists Qt5Widgets 2>/dev/null && echo yes || echo no)
ifeq ($(QT6_PKG),yes)
  QT_PKG := Qt6Widgets
else ifeq ($(QT5_PKG),yes)
  QT_PKG := Qt5Widgets
else
  QT_PKG :=
endif

.PHONY: all cli desktop install uninstall clean dvi dist test gcov_report clang format cppcheck rebuild

all: cli desktop

cli: $(APP_CLI)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(APP_CLI): $(TETRIS_OBJ) $(SNAKE_OBJ) $(CLI_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(NCURSES_LIBS)

$(TETRIS_OBJ): $(TETRIS_SRC) $(TETRIS_DIR)/tetris.h $(TETRIS_DIR)/tetris_backend.h $(COMMON_DIR)/game_info.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -DS21_NO_COMPAT_API -c $< -o $@

$(BUILD_DIR)/snake.o: $(SNAKE_DIR)/snake.cpp $(SNAKE_DIR)/snake.h $(SNAKE_DIR)/snake_controller.h $(SNAKE_DIR)/snake_model.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -DS21_NO_COMPAT_API -c $< -o $@

$(BUILD_DIR)/snake_model.o: $(SNAKE_DIR)/snake_model.cpp $(SNAKE_DIR)/snake_model.h $(SNAKE_DIR)/snake.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/snake_controller.o: $(SNAKE_DIR)/snake_controller.cpp $(SNAKE_DIR)/snake_controller.h $(SNAKE_DIR)/snake_model.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/cli_main.o: $(CLI_DIR)/main.cpp $(CLI_DIR)/frontend.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/cli_frontend.o: $(CLI_DIR)/frontend.cpp $(CLI_DIR)/frontend.h $(TETRIS_DIR)/tetris.h $(SNAKE_DIR)/snake.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -DS21_NO_COMPAT_API -c $< -o $@

desktop:
	@if [ -n "$(QT_PKG)" ]; then \
	  $(MAKE) $(APP_DESKTOP); \
	else \
	  echo "Qt Widgets not found: desktop target skipped"; \
	fi

$(APP_DESKTOP): $(TETRIS_OBJ) $(SNAKE_OBJ) $(DESKTOP_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $$(pkg-config --libs $(QT_PKG))

$(BUILD_DIR)/desktop_main.o: $(DESKTOP_DIR)/main.cpp $(DESKTOP_DIR)/main_window.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $$(pkg-config --cflags $(QT_PKG)) -DS21_NO_COMPAT_API -c $< -o $@

$(BUILD_DIR)/desktop_main_window.o: $(DESKTOP_DIR)/main_window.cpp $(DESKTOP_DIR)/main_window.h $(DESKTOP_DIR)/game_controller.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $$(pkg-config --cflags $(QT_PKG)) -DS21_NO_COMPAT_API -c $< -o $@

$(BUILD_DIR)/desktop_game_controller.o: $(DESKTOP_DIR)/game_controller.cpp $(DESKTOP_DIR)/game_controller.h $(TETRIS_DIR)/tetris.h $(SNAKE_DIR)/snake.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $$(pkg-config --cflags $(QT_PKG)) -DS21_NO_COMPAT_API -c $< -o $@

install: all
	mkdir -p $(INSTALL_DIR)/bin
	cp $(APP_CLI) $(INSTALL_DIR)/bin/brick_game_cli
	@if [ -f "$(APP_DESKTOP)" ]; then cp $(APP_DESKTOP) $(INSTALL_DIR)/bin/brick_game_desktop; fi

uninstall:
	rm -rf $(INSTALL_DIR)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(INSTALL_DIR)
	rm -rf $(DIST_NAME)
	rm -f $(DIST_NAME).tar.gz $(DIST_NAME).zip
	rm -f *.gcda *.gcno *.gcov
	find . -name '*.gcda' -o -name '*.gcno' -o -name '*.gcov' | xargs rm -f
	rm -f tetris_high_score.dat snake_high_score.dat

rebuild: clean all

dvi:
	mkdir -p $(BUILD_DIR)/docs
	cp fsm_tetris.md fsm_snake.md README.md $(BUILD_DIR)/docs/ 2>/dev/null || true
	@echo "Documentation copied to $(BUILD_DIR)/docs"

dist: clean
	mkdir -p $(DIST_NAME)
	cp -R Makefile .clang-format .gitkeep README.md fsm_tetris.md fsm_snake.md brick_game gui tests $(DIST_NAME)/
	zip -r $(DIST_NAME).zip $(DIST_NAME)
	rm -rf $(DIST_NAME)

test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TETRIS_SRC) $(SNAKE_SRC) $(TEST_SRC) $(TETRIS_DIR)/tetris_backend.h $(SNAKE_DIR)/snake.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -DS21_TETRIS_TEST -DS21_NO_COMPAT_API -c $(TETRIS_SRC) -o $(BUILD_DIR)/tetris_test.o
	$(CXX) $(CXXFLAGS) $(GTEST_CXXFLAGS) -DS21_SNAKE_TEST -DS21_NO_COMPAT_API -c $(SNAKE_DIR)/snake.cpp -o $(BUILD_DIR)/snake_test.o
	$(CXX) $(CXXFLAGS) $(GTEST_CXXFLAGS) -DS21_SNAKE_TEST -c $(SNAKE_DIR)/snake_model.cpp -o $(BUILD_DIR)/snake_model_test.o
	$(CXX) $(CXXFLAGS) $(GTEST_CXXFLAGS) -DS21_SNAKE_TEST -c $(SNAKE_DIR)/snake_controller.cpp -o $(BUILD_DIR)/snake_controller_test.o
	$(CXX) $(CXXFLAGS) $(GTEST_CXXFLAGS) -DS21_TETRIS_TEST -DS21_SNAKE_TEST $(TEST_SRC) $(BUILD_DIR)/tetris_test.o $(BUILD_DIR)/snake_test.o $(BUILD_DIR)/snake_model_test.o $(BUILD_DIR)/snake_controller_test.o -o $@ $(GTEST_LIBS)

gcov_report: clean
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(GCOVFLAGS) -DS21_TETRIS_TEST -DS21_NO_COMPAT_API -c $(TETRIS_SRC) -o $(BUILD_DIR)/tetris_test.o
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) $(GTEST_CXXFLAGS) -DS21_SNAKE_TEST -DS21_NO_COMPAT_API -c $(SNAKE_DIR)/snake.cpp -o $(BUILD_DIR)/snake_test.o
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) $(GTEST_CXXFLAGS) -DS21_SNAKE_TEST -c $(SNAKE_DIR)/snake_model.cpp -o $(BUILD_DIR)/snake_model_test.o
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) $(GTEST_CXXFLAGS) -DS21_SNAKE_TEST -c $(SNAKE_DIR)/snake_controller.cpp -o $(BUILD_DIR)/snake_controller_test.o
	$(CXX) $(CXXFLAGS) $(GTEST_CXXFLAGS) -DS21_TETRIS_TEST -DS21_SNAKE_TEST -c $(TEST_DIR)/gtest_main.cpp -o $(BUILD_DIR)/gtest_main.o
	$(CXX) $(CXXFLAGS) $(GTEST_CXXFLAGS) -DS21_TETRIS_TEST -DS21_SNAKE_TEST -c $(TEST_DIR)/test_tetris.cpp -o $(BUILD_DIR)/test_tetris.o
	$(CXX) $(CXXFLAGS) $(GTEST_CXXFLAGS) -DS21_TETRIS_TEST -DS21_SNAKE_TEST -c $(TEST_DIR)/test_snake.cpp -o $(BUILD_DIR)/test_snake.o
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) $(GTEST_CXXFLAGS) $(BUILD_DIR)/gtest_main.o $(BUILD_DIR)/test_tetris.o $(BUILD_DIR)/test_snake.o $(BUILD_DIR)/tetris_test.o $(BUILD_DIR)/snake_test.o $(BUILD_DIR)/snake_model_test.o $(BUILD_DIR)/snake_controller_test.o -o $(TEST_BIN) $(GTEST_LIBS)
	./$(TEST_BIN)
	lcov -t "brick_game_v2" -o $(BUILD_DIR)/coverage.info --capture --directory $(BUILD_DIR) --base-directory . --no-external --ignore-errors mismatch
	lcov --remove $(BUILD_DIR)/coverage.info '*/tests/*' '*/gui/*' -o $(BUILD_DIR)/coverage.info --ignore-errors unused
	genhtml -o $(BUILD_DIR)/report $(BUILD_DIR)/coverage.info
	@echo "Coverage report: $(BUILD_DIR)/report/index.html"

clang:
	clang-format -n $(TETRIS_DIR)/*.c $(TETRIS_DIR)/*.h $(COMMON_DIR)/*.h $(SNAKE_DIR)/*.cpp $(SNAKE_DIR)/*.h $(CLI_DIR)/*.cpp $(CLI_DIR)/*.h $(DESKTOP_DIR)/*.cpp $(DESKTOP_DIR)/*.h $(TEST_DIR)/*.cpp

format:
	clang-format -i $(TETRIS_DIR)/*.c $(TETRIS_DIR)/*.h $(COMMON_DIR)/*.h $(SNAKE_DIR)/*.cpp $(SNAKE_DIR)/*.h $(CLI_DIR)/*.cpp $(CLI_DIR)/*.h $(DESKTOP_DIR)/*.cpp $(DESKTOP_DIR)/*.h $(TEST_DIR)/*.cpp

cppcheck:
	cppcheck --enable=all --std=c++20 --check-level=exhaustive --inline-suppr --disable=information \
	--suppress=missingIncludeSystem --suppress=missingInclude --suppress=checkersReport \
	$(TETRIS_DIR) $(SNAKE_DIR) $(CLI_DIR) $(DESKTOP_DIR) $(TEST_DIR)
