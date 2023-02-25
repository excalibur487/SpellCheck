CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Iinc
LDFLAGS = 

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

TARGET = $(BIN_DIR)/project

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*