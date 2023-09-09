# Define the compiled
CC = gcc

# Compiler Flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS = -g -Wall

SRC = $(wildcard src/*.c)
OBJ  = $(SRC:.c=.o)
BIN = bin

TEST_SRC = $(wildcard tests/*.c)
TEST_OBJ = $(TEST_SRC:.c=.o)

all: dir main test

main: $(OBJ)
	$(CC) -o $(BIN)/main $^

test: $(TEST_OBJ) src/cpu.o
	$(CC) -o $(BIN)/test $^

dir:
	mkdir -p ./$(BIN)

%.o: %.c
	echo "testing"
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ) $(TEST_OBJ)