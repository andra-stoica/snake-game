#include "all_h.h"

int main(void)
{
	int width, length;
	while (1) {
		scanf("%d %d", &length, &width);
		if (length < 10 || width < 10) {
			scanf("%d %d", &length, &width);
		} else {
			break;
		}
	}

	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
	char **board = initial_board(width, length);
	Snake *snake = create_list_snake();
	snake = head_tail_snake(width, length, snake);

	printf("\033[2J\033[H");
	fflush(stdout);

	struct timespec wait_time = {0, MS_TO_NSEC(200)};
	struct termios game_terminal, original_terminal;
	if (tcgetattr(STDIN_FILENO, &game_terminal) < 0) {
		return 1;
	}

	original_terminal = game_terminal;
	game_terminal.c_lflag &= ~ICANON;
	game_terminal.c_lflag &= ~ECHO;
	game_terminal.c_cc[VMIN] = 0;
	game_terminal.c_cc[VTIME] = 0;

	if (tcsetattr(STDIN_FILENO, TCSANOW, &game_terminal) < 0) {
		return 1;
	} 

	char c, character = 'a';
	int n;
	int end_game = 0;
	while (1) {
		n = read(STDIN_FILENO, &c, 1);
		if (n == 1) {
			// input (change of direction)
			if (c == 'q') {
				break;
			} else if (c == 'w' || c == 'a' || c == 's' || c == 'd') {
				character = c;
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

	// printf("exit game\n");
	if (tcsetattr(STDIN_FILENO, TCSANOW, &original_terminal) < 0) {
		return 1;
	}

	board = free_board(board, length);
	snake = free_snake(snake);

	return 0;
}