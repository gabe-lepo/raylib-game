.PHONY: default clean build run

default: clean run

APP_NAME = raylib_app
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = /Users/glepoutre/Documents/vscode/raylib/src
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/game.c $(SRC_DIR)/player.c $(SRC_DIR)/timer.c $(SRC_DIR)/screen.c

build: $(SRC)
	@echo "Building"
	mkdir -p $(BUILD_DIR)
	clang -I$(INCLUDE_DIR) -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libraylib.a $(SRC) -o $(BUILD_DIR)/$(APP_NAME)
	@echo "Build done"

run: build
	@echo "Running..."
	./$(BUILD_DIR)/$(APP_NAME)

clean:
	@echo "Cleaning"
	rm -rf $(BUILD_DIR)/*
	@echo "Clean done"