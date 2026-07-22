#include "game.h"

void generate_numbers(int *x, int *y, int length, int width)
{
	*x = rand() % (length - 1);
	if (*x == 0) {
		(*x)++;
	}

	*y = rand() % (width - 1);
	if (*y == 0) {
		(*y)++;
	}
}

char **generate_obstacle_2(int row_obstacles, int column_obstacles, 
							char **board, int length, int width)
{

	while (1) {
		if (board[row_obstacles][column_obstacles] == ' ') {
			if (board[row_obstacles - 1][column_obstacles] == ' ' &&
					board[row_obstacles + 1][column_obstacles] == ' ' &&
					board[row_obstacles][column_obstacles - 1] == ' ' &&
					board[row_obstacles][column_obstacles + 1] == ' ') {
						if (board[row_obstacles][column_obstacles + 2] == ' ') {
							board[row_obstacles][column_obstacles] = '#';
							board[row_obstacles][column_obstacles + 1] = '#';
							break;
						} else if (board[row_obstacles + 2][column_obstacles] == ' ') {
							board[row_obstacles][column_obstacles] = '#';
							board[row_obstacles + 1][column_obstacles] = '#';
							break;
						} else if (board[row_obstacles][column_obstacles - 2] == ' ') {
							board[row_obstacles][column_obstacles] = '#';
							board[row_obstacles][column_obstacles - 1] = '#';
							break;
						} else if (board[row_obstacles - 2][column_obstacles] == ' ') {
							board[row_obstacles][column_obstacles] = '#';
							board[row_obstacles - 1][column_obstacles] = '#';
							break;
						}
			}
		}

		generate_numbers(&row_obstacles, &column_obstacles, length, width);
	}

	return board;
}

char **generate_obstacle_3(int row_obstacles, int column_obstacles, 
							char **board, int length, int width)
{
	while (1) {
		if (board[row_obstacles][column_obstacles] == ' ') {
			if (board[row_obstacles - 1][column_obstacles] == ' ' &&
					board[row_obstacles + 1][column_obstacles] == ' ' &&
					board[row_obstacles][column_obstacles - 1] == ' ' &&
					board[row_obstacles][column_obstacles + 1] == ' ') {
						if (board[row_obstacles + 2][column_obstacles] == ' ' && 
							board[row_obstacles + 3][column_obstacles] == ' ') {
							board[row_obstacles][column_obstacles] = '#';
							board[row_obstacles + 1][column_obstacles] = '#';
							board[row_obstacles + 2][column_obstacles] = '#';
							break;
						} else if (board[row_obstacles][column_obstacles - 2] == ' ' && 
									board[row_obstacles][column_obstacles - 3] == ' ') {
							board[row_obstacles][column_obstacles] = '#';
							board[row_obstacles][column_obstacles - 1] = '#';
							board[row_obstacles][column_obstacles - 2] = '#';
							break;
						} else if (board[row_obstacles - 2][column_obstacles] == ' ' && 
									board[row_obstacles - 3][column_obstacles] == ' ') {
							board[row_obstacles][column_obstacles] = '#';
							board[row_obstacles - 1][column_obstacles] = '#';
							board[row_obstacles - 2][column_obstacles] = '#';
							break;
						} else if (board[row_obstacles][column_obstacles + 2] == ' ' && 
									board[row_obstacles][column_obstacles + 3] == ' ') {
							board[row_obstacles][column_obstacles] = '#';
							board[row_obstacles][column_obstacles + 1] = '#';
							board[row_obstacles][column_obstacles + 2] = '#';
							break;
						}
			}
		}

		generate_numbers(&row_obstacles, &column_obstacles, length, width);
	}

	return board;
}

char **generate_obstacle_4(int row_obstacles, int column_obstacles, 
							char **board, int length, int width)
{
	while (1) {
		if (board[row_obstacles][column_obstacles] == ' ') {
			if (board[row_obstacles - 1][column_obstacles] == ' ' &&
					board[row_obstacles + 1][column_obstacles] == ' ' &&
					board[row_obstacles][column_obstacles - 1] == ' ' &&
					board[row_obstacles][column_obstacles + 1] == ' ') {
						if (board[row_obstacles][column_obstacles - 2] == ' ' && 
							board[row_obstacles][column_obstacles - 3] == ' ' &&
							board[row_obstacles][column_obstacles - 4] == ' ') {
							board[row_obstacles][column_obstacles] = '#';
							board[row_obstacles][column_obstacles - 1] = '#';
							board[row_obstacles][column_obstacles - 2] = '#';
							board[row_obstacles][column_obstacles - 3] = '#';
							break;
						} else if (board[row_obstacles - 2][column_obstacles] == ' ' && 
									board[row_obstacles - 3][column_obstacles] == ' ' &&
									board[row_obstacles - 4][column_obstacles] == ' ') {
							board[row_obstacles][column_obstacles] = '#';
							board[row_obstacles - 1][column_obstacles] = '#';
							board[row_obstacles - 2][column_obstacles] = '#';
							board[row_obstacles - 3][column_obstacles] = '#';
							break;
						} else if (board[row_obstacles][column_obstacles + 2] == ' ' && 
									board[row_obstacles][column_obstacles + 3] == ' ' &&
									board[row_obstacles][column_obstacles + 4] == ' ') {
							board[row_obstacles][column_obstacles] = '#';
							board[row_obstacles][column_obstacles + 1] = '#';
							board[row_obstacles][column_obstacles + 2] = '#';
							board[row_obstacles][column_obstacles + 3] = '#';
							break;
						} else if (board[row_obstacles + 2][column_obstacles] == ' ' && 
									board[row_obstacles + 3][column_obstacles] == ' ' &&
									board[row_obstacles + 4][column_obstacles] == ' ') {
							board[row_obstacles][column_obstacles] = '#';
							board[row_obstacles + 1][column_obstacles] = '#';
							board[row_obstacles + 2][column_obstacles] = '#';
							board[row_obstacles + 3][column_obstacles] = '#';
							break;
						}
			}
		}

		generate_numbers(&row_obstacles, &column_obstacles, length, width);
	}

	return board;
}

char **generate_walls(char **board, int width, int length)
{
	int interior = (length - 2) * (width - 2);
	int obstacles = interior / 10;
	int pair9 = obstacles / 9;
	int row_obstacles, column_obstacles;
	while (obstacles > 0) {
		while (board[column_obstacles][row_obstacles] != ' ') {
			generate_numbers(&row_obstacles, &column_obstacles, length, width);
		}

		if (pair9) {
			board = generate_obstacle_4(row_obstacles, column_obstacles, board, length, width);
			board = generate_obstacle_3(row_obstacles, column_obstacles, board, length, width);
			board = generate_obstacle_2(row_obstacles, column_obstacles, board, length, width);
			pair9--;
		} else {
			board = generate_obstacle_4(row_obstacles, column_obstacles, board, length, width);
			board = generate_obstacle_3(row_obstacles, column_obstacles, board, length, width);
			obstacles = 0;
		}

		obstacles = obstacles - 9;
	}

	return board;
}

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
			if (board[i][j] != '*' && board[i][j] != '#') {
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

char **difficulty_game(char **board, int length, int width, struct timespec *wait_time) 
{
	FILE *f_diff = fopen("data/difficulty.txt", "r");
	if (!f_diff) {
		return NULL;
	}

	char *line = malloc(LINE_LENGTH * sizeof(char));
	if (!line) {
		return NULL;
	}

	fgets(line, LINE_LENGTH, f_diff);
	char *p = strchr(line, '\n');
	if (p) {
		*p = '\0';
	}

	if (strcmp(line, "hard") == 0) {
		// poate fac ceva la viteza ca sa fie progresiva
		board = generate_walls(board, width, length);
		wait_time->tv_sec = 0;
		wait_time->tv_nsec = MS_TO_NSEC(150);
	} else if (strcmp(line, "easy") == 0) {
		wait_time->tv_sec = 0;
		wait_time->tv_nsec = MS_TO_NSEC(250);
	}

	// o sa mai adaug chestii pt fiecare mod
	fclose(f_diff);
	free(line);
	return board;
}

void dimensions_board(int *length, int *width)
{
	FILE *f_board = fopen("data/board.txt", "r");
	if (!f_board) {
		return;
	}

	char *line = malloc(LINE_LENGTH * sizeof(char));
	if (!line) {
		return;
	}

	fgets(line, LINE_LENGTH, f_board);
	char *p = strtok(line, " ");
	*length = atoi(p);

	p = strtok(NULL, " ");
	*width = atoi(p);

	free(line);
	fclose(f_board);
}

void actual_game()
{
	int width, length;
	dimensions_board(&length, &width);

	char **board = initial_board(width, length);

	struct timespec wait_time = {0, MS_TO_NSEC(200)};
	board = difficulty_game(board, length, width, &wait_time);

	Snake *snake = create_list_snake();
	snake = head_tail_snake(width, length, snake);

	printf("\033[2J\033[H");
	fflush(stdout);

	struct termios game_terminal, original_terminal;
	if (tcgetattr(STDIN_FILENO, &game_terminal) < 0) {
		return;
	}

	original_terminal = game_terminal;
	game_terminal.c_lflag &= ~ICANON;
	game_terminal.c_lflag &= ~ECHO;
	game_terminal.c_cc[VMIN] = 0;
	game_terminal.c_cc[VTIME] = 0;

	if (tcsetattr(STDIN_FILENO, TCSANOW, &game_terminal) < 0) {
		return;
	} 

	char c, character = 'a';
	int n;
	int end_game = 0;
	while (1) {
		n = read(STDIN_FILENO, &c, 1);
		if (n == 1) {
			if (c == 'q') {
				break;
			} else if (c == 'w' || c == 'a' || c == 's' || c == 'd') {
				character = c;
			} else if (c == 'p') {
				// pause screen
				;
			}
		}

		board = update_board(board, snake, character, width, length, &end_game);
		printf("\033[H");
		if (end_game) {
			break;
		}

		print_state(board, width, length);
		fflush(stdout);
		nanosleep(&wait_time, NULL);

	}

	if (tcsetattr(STDIN_FILENO, TCSANOW, &original_terminal) < 0) {
		return;
	}

	board = free_board(board, length);
	snake = free_snake(snake);
}

