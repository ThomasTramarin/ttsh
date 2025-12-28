CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g
SRC = src/main.c
TARGET = build/ttsh

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)