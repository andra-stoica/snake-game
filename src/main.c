#include "menu.h"

int main(void)
{
	int width, length;
	FILE *f_board = fopen("data/board.txt", "r");
	if (!f_board) {
		return -1;
	}

	char *line = malloc(LINE_LENGTH * sizeof(char));
	if (!line) {
		return -1;
	}

	fgets(line, LINE_LENGTH, f_board);
	char *p = strtok(line, " ");
	length = atoi(p);
	p = strtok(NULL, " ");
	width = atoi(p);

	menu(length, width);
	free(line);

	// int ch;
	// while ((ch = getchar()) != '\n' && ch != EOF);
	return 0;
}