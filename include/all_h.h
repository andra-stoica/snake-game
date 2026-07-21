#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>

#define MS_TO_NSEC(ms) ((ms) * 1000000L) // miliseconds in nanoseconds

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

typedef struct obstacle{
	int x, y;
} obstacle;

// board_snake.c
char **initial_board(int width, int length);

Snake *create_list_snake(void);

ListNode *create_node_snake(int x, int y);

Snake *head_tail_snake(int width, int length, Snake *snake);

char **free_board(char **board, int length);

Snake *free_snake(Snake *snake);

//-------------------------------------------------
// game.c

char **generating_food(char **board, Snake *snake, int width, int length);

int check_all(Snake *snake, char **board,char direction);

Snake *snake_movement(Snake *snake, char direction, int did_collide_food);

int check_snake_itself_collision(Snake *snake, char direction);

char **update_board(char **board, Snake *snake, 
					char direction, int width, int length, int *end_game);

void print_state(char **board, int width, int length);

void actual_game(int width, int length);
