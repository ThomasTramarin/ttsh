CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g
SRC = src/main.c src/parser.c src/prompt.c src/builtin.c src/external.c
TARGET = build/ttsh

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)