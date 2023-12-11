#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "lib/direction.h"
#include "lib/snake.h"

#define TIMEOUT_DELAY 125		/* Delay is in ms */
#define INITIAL_SNAKE_LENGTH 3

int main(void) {
    // setlocale(LC_ALL, "");

	initscr();					/* Start curses mode */
	noecho();					/* getch() doesn't print the character it receives */
    curs_set(0);				/* Hide cursor */
    keypad(stdscr, TRUE);		/* Enable F1,...,F12 and arrow keys in stdscr */
    timeout(TIMEOUT_DELAY);

	/* Save window boundaries to row, col */
    int row, col;
    getmaxyx(stdscr, row, col);

	srand(time(NULL));
	/* Init apple */
	food apple = { 
		.coords = {
			.y = rand() % row, 
			.x = rand() % col
		},
		.attire = FOOD_ATTIRE 
	};

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

    int key;
	direction new_d;
    while (true) {
		/* Set and Print Background and Objects */
		getmaxyx(stdscr, row, col); /* Get size of screen each time, in case of resize */
		mvwprintw(stdscr, 0, 0, "(%d, %d)", head->part.coords.x, head->part.coords.y);
		mvwprintw(stdscr, row - 1, 0, "direction=%s", dirtostr(d));

		printobj(&apple);

		printsnake(head);

		/* Change state */
		/* 
		   Always call getch() after printing snake. That way, the snake gets printed and 
		   then the delay from getch() will allow the player to see the snake before the 
		   screen is refreshed. 
	   */
		if ((key = getch()) != ERR) {
			new_d = get_direction(key);
			if (new_d != opposite(d)) {
				d = new_d;
			}
		}

		/* Prepend head */
		part body_p = head->part;
		body_p.attire = HEAD_ATTIRE;
		dmoveobj(&body_p, d);

		head->part.attire = BODY_ATTIRE;
		head = insert(head, body_p);

		pop(head);

		if (coordsequal(head->part.coords, apple.coords)) {
			growsnake(head, d);
		}

		refresh();
		erase();
    }

	freesnake(head);

	curs_set(1);			/* Turn cursor back on */
    endwin();				/* End curses mode */
    return EXIT_SUCCESS;
}
