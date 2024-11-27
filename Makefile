# Define the compiled
CC = gcc

# Compiler Flags:
CFLAGS = -g -Wall -Wpedantic -Wextra

SRC = $(wildcard src/*.c)
OBJ  = $(SRC:.c=.o)
BIN = bin

TEST_SRC = $(wildcard tests/*.c)
TEST_OBJ = $(TEST_SRC:.c=.o)

all: dir main test

main: $(OBJ)
	$(CC) -o $(BIN)/main $^ $(CFLAGS)

test: $(TEST_OBJ) src/cpu.o src/opcode.o
	$(CC) -o $(BIN)/test $^ $(CFLAGS)

dir:
	mkdir -p ./$(BIN)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ) $(TEST_OBJ)
