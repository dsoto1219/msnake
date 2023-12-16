#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "lib/direction.h"
#include "lib/keys.h"
#include "lib/objects.h"
#include "lib/snake.h"

#define TIMEOUT_DELAY 125		/* Delay is in ms */
#define INITIAL_SNAKE_LENGTH 3
#define WALLS_KILL true

int main(void) {
	initscr();					/* Start curses mode */
	// Non-window specific settings
    curs_set(0);				/* Hide cursor */
	noecho();					/* getch() doesn't print the character it receives */
	start_color();

	// Create Game Window
	int height = 12, width = 32;
	if (height > LINES || width > COLS) {
		curs_set(1);
		endwin();
		fprintf(stderr, "Current window size (%d x %d) is too small, must be at least %d x %d!\n", LINES, COLS, height, width);
		exit(EXIT_FAILURE);
	}
	int starty = (LINES - height) / 2;
	int startx = (COLS - width) / 2; 
	WINDOW *gamewin = newwin(height, width, starty, startx);

	// Settings for game window 
    keypad(gamewin, TRUE);				/* Enable F1,...,F12 and arrow keys */
    wtimeout(gamewin, TIMEOUT_DELAY);	/* Too complex to explain here, read docs */

	// Save bottom-right coordinates of gamewindow to row, col
    int row, col;
    getmaxyx(gamewin, row, col);

	srand(time(NULL));

	// Init snake
    direction d = RIGHT; /* Snake will always travel in this direction */
	snake *tail;
	snake *head = lcreatesnake(row / 2, col / 2, INITIAL_SNAKE_LENGTH, &tail, d);

	/* Init apple */

	food apple = { .attire = FOOD_ATTIRE };
	nosnakerandcoords(head, &apple, row, col);

	// Set the colors for the apple and the snake, respectively
	init_pair(1, COLOR_RED, COLOR_BLACK); 
	init_pair(2, COLOR_GREEN, COLOR_BLACK);

    int key;
	int length = INITIAL_SNAKE_LENGTH; /* Variable to dynamically track snake length */
	bool dead = false;
    while (key != QUIT_KEY) {
		/* Set and Print Background and Objects */
		// Call box first, so other elements can be printed on top. 
		box(gamewin, 0, 0);
		mvwprintw(gamewin, 0, 0, "(%d, %d)", head->part.coords.x, head->part.coords.y);
		mvwprintw(gamewin, row - 1, 0, "direction=%s", dirtostr(d));
		// The length of the help message is 16
		mvwprintw(gamewin, row - 1, col - 16, "Press h for help");
		mvwprintw(gamewin, 0, col - 9, "length=%d", length);

		wcolorprintobj(gamewin, COLOR_PAIR(1), apple);
		wcolorprintsnake(gamewin, COLOR_PAIR(2), head);

		/* Change game state */
		/* 
		   Always call getch() after printing snake. That way, the snake gets printed and 
		   then the delay from getch() will allow the player to see the snake before the 
		   screen is refreshed. 
	   */
		key = wgetch(gamewin);
		if (!dead) {
			if (key != ERR) {
				direction new_d = get_direction(key, d);
				if (new_d != opposite(d)) {
					d = new_d;
				}
			}
			
			if (d != NONE) {
				head = movesnake(head, tail, d);

				dead = touchingsnake(head, head->part, false);
				if (WALLS_KILL) {
					dead = dead || outofbounds(head->part, row, col);
				} 
				if (dead) {
					d = NONE;
					head->part.attire = DEAD_ATTIRE;
				}

				if (coordsequal(head->part.coords, apple.coords)) {
					tail = growsnake(tail, d);
					length++;
					nosnakerandcoords(head, &apple, row, col);
				}
			}
		} 
		if (key == RESET_KEY) {
			dead = false;
			freesnake(head);

			d = RIGHT;
			head = lcreatesnake(row / 2, col / 2, INITIAL_SNAKE_LENGTH, &tail, d);
			length = INITIAL_SNAKE_LENGTH;
			nosnakerandcoords(head, &apple, row, col);
		} 

		wrefresh(gamewin);
		werase(gamewin);
    }

	freesnake(head);

	curs_set(1);			/* Turn cursor back on */
    endwin();				/* End curses mode */
    return EXIT_SUCCESS;
}
