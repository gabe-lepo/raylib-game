.PHONY: default clean build run

default: build run

APP_NAME = "RGB Sine Wave Shader"
SRC_DIR = ./
BUILD_DIR = build
LOG_DIR = logs
RLIB_INCLUDE_DIR = /Users/glepoutre/Documents/vscode/raylib/src
BM_INCLUDE_DIR = /Users/glepoutre/Documents/vscode/raylib-game/raylib-examples/
LIBRAYLIB_A_DIR = /Users/glepoutre/Documents/vscode/raylib-game/libraylib.a
SRC = $(shell find $(SRC_DIR) -name '*.c')

build: $(SRC)
	@echo "# Building"
	mkdir -p $(BUILD_DIR)
	clang -I$(RLIB_INCLUDE_DIR) -I$(BM_INCLUDE_DIR) -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL $(LIBRAYLIB_A_DIR) $(SRC) -o $(BUILD_DIR)/$(APP_NAME)
	@echo "Build done"

run: build
	@echo "# Running"
	./$(BUILD_DIR)/$(APP_NAME)

clean:
	@echo "# Cleaning"
	rm -rf $(BUILD_DIR)/*
	rm -rf $(LOG_DIR)/*
	@echo "Clean done"