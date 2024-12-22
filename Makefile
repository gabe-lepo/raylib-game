.PHONY: default clean build run

default: clean run

APP_NAME = box_man
SRC_DIR = src
BUILD_DIR = build
RLIB_INCLUDE_DIR = /Users/glepoutre/Documents/vscode/raylib/src
BM_INCLUDE_DIR = /Users/glepoutre/Documents/vscode/raylib-game/src
SRC = $(SRC_DIR)/*c ${SRC_DIR}/menus/*c

build: $(SRC)
	@echo "Building"
	mkdir -p $(BUILD_DIR)
	clang -I$(RLIB_INCLUDE_DIR) -I$(BM_INCLUDE_DIR) -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libraylib.a $(SRC) -o $(BUILD_DIR)/$(APP_NAME)
	@echo "Build done"

run: build
	@echo "Running..."
	./$(BUILD_DIR)/$(APP_NAME)

clean:
	@echo "Cleaning"
	rm -rf $(BUILD_DIR)/*
	@echo "Clean done"