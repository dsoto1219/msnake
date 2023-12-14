#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "lib/direction.h"
#include "lib/objects.h"
#include "lib/snake.h"

#define TIMEOUT_DELAY 125		/* Delay is in ms */
#define INITIAL_SNAKE_LENGTH 3

int main(void) {
	initscr();					/* Start curses mode */
    curs_set(0);				/* Hide cursor */

	int height = 15, width = 50;
	if (height > LINES || width > COLS) {
		curs_set(1);
		endwin();
		fprintf(stderr, "Current window size (%d x %d) is too small, must be at least %d x %d!\n", LINES, COLS, height, width);
		exit(EXIT_FAILURE);
	}
	int starty = (LINES - height) / 2;
	int startx = (COLS - width) / 2; 
	WINDOW *gamewin = newwin(height, width, starty, startx);

	noecho();					/* getch() doesn't print the character it receives */
    keypad(gamewin, TRUE);			/* Enable F1,...,F12 and arrow keys */
    wtimeout(gamewin, TIMEOUT_DELAY);

	/* Save bottom-right coordinates of gamewindow to row, col */
    int row, col;
    getmaxyx(gamewin, row, col);

	// Init head
	part head_p = { 
		.coords = {
			.y = row / 2,
			.x = col / 2,
		},
		.attire = HEAD_ATTIRE 
	};
    direction d = RIGHT; /* Snake will always travel in this direction */
	snake *head = lcreatesnake(head_p, INITIAL_SNAKE_LENGTH, d);
	snake *tail = head;

	srand(time(NULL));
	/* Init apple */
	food apple = { .attire = FOOD_ATTIRE };
	do {
		randcoords(&apple, row, col);
	} while (touchingsnake(head, apple, true));


    int key;
	int length = INITIAL_SNAKE_LENGTH;
	bool dead = FALSE;
	direction new_d;
    while (true) {
		/* Set and Print Background and Objects */
		// Call box first, so other elements can be printed on top. 
		box(gamewin, 0, 0);
		mvwprintw(gamewin, 0, 0, "(%d, %d)", head->part.coords.x, head->part.coords.y);
		mvwprintw(gamewin, row - 1, 0, "direction=%s,length=%d", dirtostr(d), length);
		// The length of the help message is 16
		mvwprintw(gamewin, row - 1, col - 16, "Press h for help");

		wprintobj(gamewin, &apple);
		wprintsnake(gamewin, head);

		/* Change game state */
		/* 
		   Always call getch() after printing snake. That way, the snake gets printed and 
		   then the delay from getch() will allow the player to see the snake before the 
		   screen is refreshed. 
	   */
		if ((key = wgetch(gamewin)) != ERR) {
			new_d = get_direction(key);
			if (new_d != opposite(d)) {
				d = new_d;
			}
		}
		
		if (d != NONE) {
			head = movesnake(head, tail, d);
			if (touchingsnake(head, head->part, false)) {
				d = NONE;
				head->part.attire = DEAD_ATTIRE;
				dead = TRUE;
			}
			if (coordsequal(head->part.coords, apple.coords)) {
				tail = growsnake(tail, d);
				length++;
				do {
					randcoords(&apple, row, col);
				} while (touchingsnake(head, apple, true));
			}
		}

		wrefresh(gamewin);
		werase(gamewin);
    }

	freesnake(head);

	curs_set(1);			/* Turn cursor back on */
    endwin();				/* End curses mode */
    return EXIT_SUCCESS;
}
