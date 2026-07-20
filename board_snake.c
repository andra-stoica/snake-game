#include "all_h.h"

char **initial_board(int width, int length)
{
	char **board = malloc(length * sizeof(char *));
	if (!board) {
		return NULL;
	}

	for (int i = 0; i < length; i++) {
		board[i] = malloc(width * sizeof(char));
		if (!board[i]) {
			free(board);
			return NULL;
		}
	}

	for (int i = 1; i < length - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			board[i][j] = ' ';
		}
	}

	for (int i = 0; i < width; i++) {
		board[0][i] = '#';
		board[length - 1][i] = '#';
	}

	for (int j = 0; j < length; j++) {
		board[j][0] = '#';
		board[j][width - 1] = '#';
	}

	board[length / 2][width / 2] = '@'; // head of the snake

	int food_row = rand() % length;
	while (food_row == length / 2) {
		food_row = rand() % length;
	}

	int food_column = rand() % width; // we have the first food on the board
	board[food_row][food_column] = '*';

	return board;
}

Snake *create_list_snake(void)
{
	Snake* snake = malloc(sizeof(Snake));
	if (!snake) {
		return NULL;
	}
	
	snake->head = NULL;
	snake->tail = NULL;

	return snake;
}

ListNode *create_node_snake(int x, int y)
{
	ListNode *node = malloc(sizeof(ListNode));
	if (!node) {
		return NULL;
	}

	node->next = NULL;
	node->prev = NULL;
	node->x = x;
	node->y = y;

	return node;
}

Snake *head_tail_snake(int width, int length, Snake *snake)
{
	ListNode *node = create_node_snake(length / 2, width / 2);
	if (!node) {
		return NULL;
	}

	snake->head = node;
	snake->tail = node;

	return snake;
}

char **free_board(char **board, int length)
{
	for (int i = 0; i < length; i++) {
		free(board[i]);
	}

	free(board);
	return NULL;
}

Snake *free_snake(Snake *snake)
{
	ListNode *node = snake->head;
	while (node) {
		snake->head = snake->head->next;
		free(node);
		node = snake->head;
	}

	free(snake);
	return NULL;
}
