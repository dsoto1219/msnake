#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>
#include "lib/direction.h"
#include "lib/snake.h"

#define DELAY 500

int main(void) {
    // setlocale(LC_ALL, "");

	initscr();					/* Start curses mode */
	noecho();					/* getch() doesn't print the character it receives */
    curs_set(0);				/* Hide cursor */
    keypad(stdscr, TRUE);		/* Enable F1,...,F12 and arrow keys in stdscr */
    timeout(DELAY);

    int row, col;
    getmaxyx(stdscr, row, col);

	/* Init snake */
    snake S = { 
		.length = 3,

		/* Init head */
		.head.coords.y = row / 2,
		.head.coords.x = col / 2,
		.head.attire = 'O',
		.head.direction = RIGHT,
	};
	part *head = &S.head;

    int key;
    direction d = RIGHT;
    while (true) {
		/* Set Background */
		getmaxyx(stdscr, row, col); /* Get size of screen each time, in case of resize */
		mvwprintw(stdscr, 0, 0, "(%d, %d)", head->coords.x, head->coords.y);
		mvwprintw(stdscr, row - 1, 0, "direction=%i", d);

		/* Prepare for next frame */
		movepart(head);		/* Call this before getch(), or else part won't print */
		printpart(head);
		key = getch();
		if (key != ERR) {
			d = get_direction(key);
			if (d != opposite(head->direction)) {
				head->direction = d;
			}
		}

		refresh();
		erase();
    }

    curs_set(2);				/* Show cursor */
    endwin();				/* End curses mode */
    return EXIT_SUCCESS;
}
