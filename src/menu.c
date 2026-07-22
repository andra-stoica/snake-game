#include "menu.h"
#include "game.h"

void print_banner_snake(void)
{
    printf("=========================\n");
    printf("      ---SNAKE---\n");
    printf("=========================\n\n");
}

void print_game_options(void)
{
    printf("1. New Game\n");
    printf("2. High Score\n");
    printf("3. Settings\n");
    printf("4. Help\n");
    printf("5. Exit\n\n");
    printf("Your Choice: ");
}

void high_score_menu(char *name)
{
    printf("\033[2J\033[H");
	fflush(stdout);
    print_banner_snake();
    printf("Your Highest Score is:\n");
    char *line = malloc(LINE_LENGTH * sizeof(char));
    if (!line) {
        return;
    }

    FILE *fin = fopen("data/players.txt", "r");
    if (!fin) {
        printf("The players file can't be opened\n");
        free(name);
        free(line);
        return;
    }

    int number_players = 0;
    int easy_score = 0, normal_score = 0, hard_score = 0;
    while (fgets(line, LINE_LENGTH, fin)) {
        char *p = strtok(line, " ");
        char *pointer = strchr(name, '\n');
        if (pointer) {
            *pointer = '\0';
        }

        if (strcmp(name, p) == 0) {
            p = strtok(NULL, " ");
            easy_score = atoi(p);

            p = strtok(NULL, " ");
            normal_score = atoi(p);

            p = strtok(NULL, " ");
            hard_score = atoi(p);
        }

        number_players++;
    }

    printf("Easy: %d\n", easy_score);
    printf("Normal: %d\n", normal_score);
    printf("Hard: %d\n", hard_score);

    rewind(fin);

    printf("\n\nOther players: (easy, normal, hard)\n");
    printf("<---------------->\n");
    int i = 0, j = 0;
    while (fgets(line, LINE_LENGTH, fin)) {
        i++;
        char *p = strtok(line, " ");
        char *pointer = strchr(name, '\n');
        if (pointer) {
            *pointer = '\0';
        }

        if (strcmp(name, p) != 0) {
            j++;
            printf("@%s: ", p);
            p = strtok(NULL, " ");
            easy_score = atoi(p);

            p = strtok(NULL, " ");
            normal_score = atoi(p);

            p = strtok(NULL, " ");
            hard_score = atoi(p);
            
            if (i == number_players || (number_players == i  + 1 && i == j)) {
                printf("%d %d %d\n", easy_score, normal_score, hard_score);
            } else {
                printf("%d %d %d\n\n", easy_score, normal_score, hard_score);
            }
        }
    }

    printf("<---------------->\n");

    printf("Press 'q' to return!\n");
    while (1) {
        fgets(line, LINE_LENGTH, stdin);
        char c = line[0];

        if (c == 'q') {
            break;
        }
    }

    free(line);
    fclose(fin);
}

void add_player(char *name)
{
    char *line = malloc(LINE_LENGTH * sizeof(char));
    if (!line) {
        return;
    }

    while (1) {
        fgets(line, LINE_LENGTH, stdin);
        char c = line[0];

        if (c == 'y') {
            printf("> Welcome to SNAKE, %s!\n", name);
            sleep(2);
            break;
        } else if (c == 'n') {
            printf("> Guest Mode Active!\n");
            sleep(2);
            strcpy(name, "Guest");
            break;
        }
    }

    FILE *fout = fopen("data/players.txt", "a");
    if (!fout) {
        return;
    }

    char *p = strchr(name, '\n');
    if (p) {
        *p = '\0';
    }

    fprintf(fout, "%s %d %d %d\n", name, 0, 0, 0);
    fclose(fout);
    free(line);
}

void settings_menu()
{
    printf("\033[2J\033[H");
	fflush(stdout);

    printf("==================================\n");
    printf("\tSNAKE--SETTINGS MENU\t\n");
    printf("==================================\n\n");

    printf("1. Difficulty\n");
    printf("2. Board Size\n\n");
    printf("\tPress 'q' to return\n");

    char *line = malloc(LINE_LENGTH * sizeof(char));
    if (!line) {
        return;
    }

    while (1) {
        fgets(line, LINE_LENGTH, stdin);
        char c = line[0];

        if (c == '1') {
            difficulty_settings_menu();
        } else if (c == '2') {
            board_settings_menu();
        } else if (c == 'q') {
            break;
        } else {
            printf("Choose again\n");
            sleep(1);
        }

        printf("\033[2J\033[H");
        fflush(stdout);

        printf("==================================\n");
        printf("\tSNAKE--SETTINGS MENU\t\n");
        printf("==================================\n\n");

        printf("1. Difficulty\n");
        printf("2. Board Size\n\n");
        printf("\tPress 'q' to return\n");
    }

    free(line);
}

void difficulty_settings_menu()
{
    printf("\033[2J\033[H");
	fflush(stdout);

    printf("==================================\n");
    printf("\tSETTINGS -- DIFFICULTY MENU\t\n");
    printf("==================================\n\n");

    // as putea sa explic ce are fiecare in parte, in alta versiune a jocului
    printf("> easy (1)\n");
    printf("> normal (2)\n");
    printf("> hard (3)\n");
    FILE *f_diff = fopen("data/difficulty.txt", "w");
    if (!f_diff) {
        return;
    }

    char *line = malloc(LINE_LENGTH * sizeof(char));
    if (!line) {
        return;
    }

    while (1) {
        fgets(line, LINE_LENGTH, stdin);
        char c = line[0];

        if (c == '1') {
            fprintf(f_diff, "easy");
            break;
        } else if (c == '2') {
            fprintf(f_diff, "normal");
            break;
        } else if (c == '3') {
            fprintf(f_diff, "hard");
            break;
        } else {
            // choose again
            printf("Choose again\n");
            sleep(1);
            printf("\033[2J\033[H");
            fflush(stdout);

            printf("==================================\n");
            printf("\tSETTINGS -- DIFFICULTY MENU\t\n");
            printf("==================================\n\n");

            printf("> easy (1)\n");
            printf("> normal (2)\n");
            printf("> hard (3)\n");
        }
    }

    fclose(f_diff);
    free(line);
}

void board_settings_menu()
{
    printf("\033[2J\033[H");
	fflush(stdout);

    printf("==================================\n");
    printf("\tSETTINGS -- BOARD MENU\t\n");
    printf("==================================\n\n");

    printf("> 16x16  (press '1')\n");
    printf("> 32x32  (press '2')\n");
    printf("> custom (press 'c')\n");
    FILE *f_board = fopen("data/board.txt", "w");
    if (!f_board) {
        return;
    }

    char *line = malloc(LINE_LENGTH * sizeof(char));
    if (!line) {
        return;
    }

    while (1) {
        fgets(line, LINE_LENGTH, stdin);
        char c = line[0];

        if (c == '1') {
            fprintf(f_board, "16 16");
            break;
        } else if (c == '2') {
            fprintf(f_board, "32 32");
            break;
        } else if (c == 'c') {
            char *data = malloc(LINE_LENGTH * sizeof(char));
            if (!data) {
                return;
            }

            printf("LENGTH: ");
            fgets(data, LINE_LENGTH, stdin);
            int length = atoi(data);

            printf("WIDTH: ");
            fgets(data, LINE_LENGTH, stdin);
            int width = atoi(data);

            fprintf(f_board, "%d %d", length, width);
            free(data);
            break;
        } else if (c == 'q') {
            break;
        } else {
            printf("Choose again\n");
            sleep(1);

            printf("\033[2J\033[H");
            fflush(stdout);

            printf("==================================\n");
            printf("\tSETTINGS -- BOARD MENU\t\n");
            printf("==================================\n\n");

            printf("> 16x16  (press '1')\n");
            printf("> 32x32  (press '2')\n");
            printf("> custom (press 'c')\n");
            
        }
    }

    fclose(f_board);
    free(line);
}

void help_menu(void)
{
    printf("\033[2J\033[H");
	fflush(stdout);

    printf("==================================\n");
    printf("\t\tSNAKE--HELP MENU\t\t\n");
    printf("==================================\n\n");

    printf("OBJECTIVE:\n");
    printf("Eat the food (*) to grow as long as possible.\n");
    printf("Avoid hitting the walls (#) or your own body(o).\n\n");

    printf("CONTROLS:\n");
    printf("  W - Move Up\n");
    printf("  A - Move Left\n");
    printf("  S - Move Down\n");
    printf("  D - Move Rights\n");
    printf("  P - Pause Game\n");
    printf("  Q - Quit Game\n\n");

    printf("SYMBOLS:\n");
    printf("  @ - Snake Head\n");
    printf("  o - Snake Body\n");
    printf("  * - Food\n");
    printf("  # - Wall\n\n");

    printf("Press 'q' to return\n");
    char *line = malloc(LINE_LENGTH * sizeof(char));
    if (!line) {
        return;
    }

    while (1) {
        fgets(line, LINE_LENGTH, stdin);
        char c = line[0];

        if (c == 'q') {
            break;
        } else {
            printf("Choose again\n");
            sleep(1);

            printf("\033[2J\033[H");
            fflush(stdout);

            printf("==================================\n");
            printf("\t\tSNAKE--HELP MENU\t\t\n");
            printf("==================================\n\n");

            printf("OBJECTIVE:\n");
            printf("Eat the food (*) to grow as long as possible.\n");
            printf("Avoid hitting the walls (#) or your own body(o).\n\n");

            printf("CONTROLS:\n");
            printf("  W - Move Up\n");
            printf("  A - Move Left\n");
            printf("  S - Move Down\n");
            printf("  D - Move Rights\n");
            printf("  P - Pause Game\n");
            printf("  Q - Quit Game\n\n");

            printf("SYMBOLS:\n");
            printf("  @ - Snake Head\n");
            printf("  o - Snake Body\n");
            printf("  * - Food\n");
            printf("  # - Wall\n\n");

            printf("Press 'q' to return\n");
        }
    }

    free(line);
}

void menu()
{
    printf("\033[2J\033[H");
	fflush(stdout);

    print_banner_snake();

    char *name = malloc(NAME * sizeof(char));
    if (!name) {
        return;
    }

    printf("Enter your player name:\n> ");
    fgets(name, NAME, stdin);
    printf("\n\n");
    FILE *fin = fopen("data/players.txt", "r");
    if (!fin) {
        printf("The players file can't be opened\n");
        free(name);
        return;
    }

    char *line = malloc(LINE_LENGTH * sizeof(char));
    if (!line) {
        free(name);
        return;
    }

    int player_exists = 0;
    while (fgets(line, LINE_LENGTH, fin)) {
        char *p = strtok(line, " ");
        char *pointer = strchr(name, '\n');
        if (pointer) {
            *pointer = '\0';
        }
        
        if (strcmp(name, p) == 0) {
            player_exists = 1;
            printf("> Welcome back, %s!\n", name);
            fflush(stdout);
            sleep(1);
            printf("   Loading menu...");
            fflush(stdout);
            sleep(2);
            break;
        }
    }

    fclose(fin);

    if (!player_exists) {
        // add a new player
        printf("Player not found.\n");
        printf("Create new player? (y/n): ");
        add_player(name);
    }

    while (1) {
        printf("\033[2J\033[H");
        fflush(stdout);

        print_banner_snake();
        print_game_options();
        fflush(stdout);

        fgets(line, LINE_LENGTH, stdin);
        char choice = line[0];

        if (choice == '1') {
            actual_game();
            printf("\033[2J\033[H");
            fflush(stdout);

            print_banner_snake();
            printf("You lost! hihi\n");
            sleep(2);

            printf("\033[2J\033[H");
            fflush(stdout);

            print_banner_snake();
            print_game_options();
            fflush(stdout);
        } else if (choice == '2') {
            high_score_menu(name);
        } else if (choice =='3') {
            settings_menu();
        } else if (choice == '4') {
            help_menu();
        } else if (choice == '5' || choice == 'q') {
            break;
        } else {
            printf("\033[2J\033[H");
            fflush(stdout);

            print_banner_snake();
            printf("\t\t\n\nChoose a number that ACTUALLY appears on the screen!\n");
            sleep(2);
            // bla bla mai am de adaugat aici
        }
    }

    // poate ar fi bine sa adaug undeva si numele celui care joaca (player name)

    free(name);
    free(line);
}