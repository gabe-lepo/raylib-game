UNITY_DIR = unity
UNITY_SRC = $(UNITY_DIR)/src/unity.c
UNITY_INC = -I $(UNITY_DIR)/src

TEST_SRC = test_main.c
TEST_BIN = test_main

CFLAGS = -Wall -Wextra -Werror

all: $(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(UNITY_SRC)
	gcc $(CFLAGS) -o $@ $^ $(UNITY_INC)

clean:
	rm -f $(TEST_BIN)

.PHONY: all clean