CC=gcc
CFLAGS=-Wall -Wextra -Iinclude -g
SOURCES=src/board_snake.c src/game.c src/main.c src/menu.c
TARGET=snake

.PHONY: clean valgrind

snake: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

valgrind: snake
	valgrind --leak-check=full --show-leak-kinds=all ./snake

clean:
	rm -f $(TARGET)