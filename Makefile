.PHONY: default clean build run

default: build run

APP_NAME = box_man
SRC_DIR = src
BUILD_DIR = build
LOG_DIR = logs
RLIB_INCLUDE_DIR = /Users/glepoutre/Documents/old_projects/raylib/src
BM_INCLUDE_DIR = /Users/glepoutre/Documents/old_projects/raylib-game/src
SRC = $(shell find $(SRC_DIR) -name '*.c')

build: $(SRC)
	@echo "# Building"
	mkdir -p $(BUILD_DIR)
	clang -I$(RLIB_INCLUDE_DIR) -I$(BM_INCLUDE_DIR) -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libraylib.a $(SRC) -o $(BUILD_DIR)/$(APP_NAME)
	@echo "Build done"

run: build
	@echo "# Running"
	./$(BUILD_DIR)/$(APP_NAME)

clean:
	@echo "# Cleaning"
	rm -rf $(BUILD_DIR)/*
	rm -rf $(LOG_DIR)/*
	@echo "Clean done"
