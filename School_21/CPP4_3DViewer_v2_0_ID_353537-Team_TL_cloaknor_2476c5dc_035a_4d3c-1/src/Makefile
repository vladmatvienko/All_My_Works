CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Werror -pedantic -I.
APP := 3DViewer_v2
INSTALL_DIR ?= $(CURDIR)/install
BUILD_DIR := build
QMAKE := $(shell command -v qmake6 2>/dev/null || command -v qmake-qt5 2>/dev/null || command -v qmake 2>/dev/null)
ZIP := $(shell command -v zip 2>/dev/null)
DIST_NAME := 3DViewer_v2.zip
DIST_ROOT := 3DViewer_v2

CORE_SOURCES := \
  s21_matrix_oop.cc \
  model/base_file_reader.cc \
  model/facade.cc \
  model/figure.cc \
  model/geometry.cc \
  model/gif_encoder.cc \
  model/obj_file_reader.cc \
  model/render_settings.cc \
  model/scene_loader.cc \
  model/scene.cc \
  model/transform_matrix.cc

TEST_SOURCES := tests/unit_tests.cc $(CORE_SOURCES)
TEST_TARGET := $(BUILD_DIR)/unit_tests

.PHONY: all install uninstall clean dvi dist tests test style clang format rebuild check_qmake check_zip

all: check_qmake
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(QMAKE) ../viewer.pro
	$(MAKE) -C $(BUILD_DIR)

check_qmake:
	@if [ -z "$(QMAKE)" ]; then \
	  echo "Qt qmake was not found. Install qtbase5-dev or qt6-base-dev and qmake."; \
	  exit 1; \
	fi

check_zip:
	@if [ -z "$(ZIP)" ]; then \
	  echo "zip was not found. Install it with: sudo apt install zip"; \
	  exit 1; \
	fi

install: all
	mkdir -p $(INSTALL_DIR)
	cp -f $(BUILD_DIR)/$(APP) $(INSTALL_DIR)/$(APP)
	@echo "Installed to $(INSTALL_DIR)/$(APP)"

uninstall:
	rm -rf $(INSTALL_DIR)

$(TEST_TARGET): $(TEST_SOURCES)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_SOURCES) -o $(TEST_TARGET)

tests: $(TEST_TARGET)
	./$(TEST_TARGET)

test: tests

dvi:
	mkdir -p docs/html
	printf '<html><body><h1>3DViewer v2.0</h1><p>See docs/README.md and source comments.</p></body></html>\n' > docs/html/index.html
	@echo "Documentation created at docs/html/index.html"

dist: clean check_zip
	@tmp_dir=$$(mktemp -d); \
	mkdir -p "$$tmp_dir/$(DIST_ROOT)/src"; \
	find . -mindepth 1 -maxdepth 1 \
	  ! -name '$(BUILD_DIR)' \
	  ! -name '$(DIST_NAME)' \
	  ! -name 'install' \
	  ! -name '*.tar.gz' \
	  ! -name '.git' \
	  -exec cp -R {} "$$tmp_dir/$(DIST_ROOT)/src/" \; ; \
	cd "$$tmp_dir" && "$(ZIP)" -qr "$(CURDIR)/$(DIST_NAME)" "$(DIST_ROOT)"; \
	status=$$?; \
	rm -rf "$$tmp_dir"; \
	if [ $$status -ne 0 ]; then exit $$status; fi; \
	echo "Archive created: $(DIST_NAME)"

CLANG_FILES := $(shell find . \( -path './build' -o -path './install' \) -prune -o \( -name '*.cc' -o -name '*.h' \) -print)

style: clang

clang:
	@if [ -z "$(CLANG_FILES)" ]; then \
	  echo "No source files found for clang-format"; \
	  exit 1; \
	fi
	clang-format -n $(CLANG_FILES)

format:
	clang-format -i $(CLANG_FILES)

rebuild: clean all

clean:
	rm -rf $(BUILD_DIR) $(DIST_NAME) *.tar.gz docs/html
