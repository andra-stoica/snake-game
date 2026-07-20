CC=gcc
CFLAGS=-Wall -Wextra -g

.PHONY: clean

snake: board_snake.c game.c main.c
	$(CC) $(CFLAGS) board_snake.c game.c main.c -o snake

valgrind: snake
	valgrind --leak-check=full --show-leak-kinds=all ./snake

clean:
	rm -f snake