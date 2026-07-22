#pragma once

#include "all_h.h"
#include "board_snake.h"

void generate_numbers(int *x, int *y, int length, int width);

char **generate_obstacle_2(int row_obstacles, int column_obstacles, 
							char **board, int length, int width);

char **generate_obstacle_3(int row_obstacles, int column_obstacles, 
							char **board, int length, int width);

char **generate_obstacle_4(int row_obstacles, int column_obstacles, 
							char **board, int length, int width);

char **generate_walls(char **board, int width, int length);

char **generating_food(char **board, Snake *snake, int width, int length);

int check_all(Snake *snake, char **board,char direction);

Snake *snake_movement(Snake *snake, char direction, int did_collide_food);

int check_snake_itself_collision(Snake *snake, char direction);

char **update_board(char **board, Snake *snake, 
					char direction, int width, int length, int *end_game);

void print_state(char **board, int width, int length);

char **difficulty_game(char **board, int length, int width, struct timespec *wait_time);

void dimensions_board(int *length, int *width);

void actual_game();