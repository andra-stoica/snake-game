#pragma once

#include "all_h.h"

typedef struct double_list{
	int x, y;
	struct double_list *next;
	struct double_list *prev;
} ListNode;

typedef struct snake{
	ListNode *head;
	ListNode *tail;
} Snake;

// typedef struct food{
// 	int x, y;
// 	// char type; // b - big, s - small
// } food;

// typedef struct obstacle{
// 	int x, y;
// } obstacle;

char **initial_board(int width, int length);

char **free_board(char **board, int length);

Snake *create_list_snake(void);

ListNode *create_node_snake(int x, int y);

Snake *head_tail_snake(int width, int length, Snake *snake);

Snake *free_snake(Snake *snake);