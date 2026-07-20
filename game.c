#include "all_h.h"

char **generating_food(char **board, Snake *snake, int width, int length)
{
	ListNode *node = snake->head;
	int food_raw = rand() % (length - 1);
	if (food_raw == 0) {
		food_raw++;
	}

	int food_column = rand() % (width - 1);
	if (food_column == 0) {
		food_column++;
	}

	while (node) {
		if (food_raw == node->x && food_column == node->y) {
			food_raw = rand() % (length - 1);
			if (food_raw == 0) {
				food_raw++;
			}
			
			food_column = rand() % (width - 1);
			if (food_column == 0) {
				food_column++;
			}

			node = snake->head;
		} else {
			node = node->next;
		}
	}

	board[food_raw][food_column] = '*';
	return board;
}

Snake *snake_movement(Snake *snake, char direction, int did_collide_food)
{
	int x = snake->head->x;
	int y = snake->head->y;
	if (direction == 'w') {
		x = x - 1;
	} else if (direction == 'a') {
		y = y - 1;
	} else if (direction == 's') {
		x = x + 1;
	} else if (direction == 'd') {
		y = y + 1;
	}

	ListNode *new_head = create_node_snake(x, y);
	new_head->next = snake->head;
	snake->head->prev = new_head;
	snake->head = new_head;

	if (!did_collide_food) {
		ListNode *temp = snake->tail;
		snake->tail = snake->tail->prev;
		snake->tail->next = NULL;
		free(temp);
	}

	return snake;
}

// 1 - collide itself
int check_snake_itself_collision(Snake *snake, char direction)
{
	int x = snake->head->x;
	int y = snake->head->y;
	if (direction == 'w') {
		x = x - 1;
	} else if (direction == 'a') {
		y = y - 1;
	} else if (direction == 's') {
		x = x + 1;
	} else if (direction == 'd') {
		y = y + 1;
	}

	ListNode *temp = snake->head->next;
	while (temp) {
		if (x == temp->x && y == temp->y) {
			return 1;
		}

		temp = temp->next;
	}

	return 0;
}

// 2 - end game, 1 - grow, 0 - simply moves
int check_all(Snake *snake, char **board,char direction)
{
	int x = snake->head->x;
	int y = snake->head->y;
	if (direction == 'w') {
		x = x - 1;
	} else if (direction == 'a') {
		y = y - 1;
	} else if (direction == 's') {
		x = x + 1;
	} else if (direction == 'd') {
		y = y + 1;
	}

	if (board[x][y] == '*') {
		return 1;
	}

	if (board[x][y] == '#') {
		return 2;
	}

	if (check_snake_itself_collision(snake, direction)) {
		return 2;
	}

	return 0;
}

char **update_board(char **board, Snake *snake, 
					char direction, int width, int length, int *end_game)
{	int state = check_all(snake, board, direction);
	if (state == 0) {
		// the snake simply moves
		snake = snake_movement(snake, direction, 0);
	} else if (state == 1) {
		// the snake grows
		snake = snake_movement(snake,direction, 1);
		board[snake->head->x][snake->head->y] = ' ';
		board = generating_food(board, snake, width, length);
	} else {
		// wall / snake collision -> end game
		*end_game = 1;
		return board;
	}
	
	for (int i = 1; i < length - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			if (board[i][j] != '*') {
				board[i][j] = ' ';
			}
		}
	}
	
	ListNode *temp = snake->head->next;
	board[snake->head->x][snake->head->y] = '@';
	while (temp) {
		board[temp->x][temp->y] = 'o';
		temp = temp->next;
	}
	

	return board;
}

void print_state(char **board, int width, int length)
{
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			printf("%c", board[i][j]);
		}
		
		printf("\n");
	}
}

