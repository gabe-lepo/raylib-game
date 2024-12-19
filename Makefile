.PHONY: default clean build run

default: clean run

APP_NAME = raylib_app
SRC_DIR = src
BUILD_DIR = build
SRC = $(SRC_DIR)/main.c

build: $(SRC)
	@echo "Building"
	mkdir -p $(BUILD_DIR)
	clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libraylib.a $(SRC) -o $(BUILD_DIR)/$(APP_NAME)
	@echo "Build done"

run: build
	@echo "Running..."
	./$(BUILD_DIR)/$(APP_NAME)

clean:
	@echo "Cleaning"
	rm -rf $(BUILD_DIR)/*
	@echo "Clean done"