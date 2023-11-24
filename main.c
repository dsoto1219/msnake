#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
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

	/* Init apple */
	srand(time(NULL));
	food apple = { .coords.y = rand() % row, .coords.x = rand() % col, .attire = '@' };

	/* Init snake */
    snake S = { 
		.length = 3,

		/* Init head */
		.head.coords.y = row / 2,
		.head.coords.x = col / 2,
		.head.attire = 'O',
		.head.direction = RIGHT,

		.body.coords.y = S.head.coords.y,
		.body.coords.x = S.head.coords.x - 1,
		.body.attire = 'o',
		.body.direction = RIGHT,
	};
	part *head = &S.head;
	part *body = &S.body;

    int key;
    direction d = S.head.direction; /* Direction for the entire snake to move in */
    while (true) {
		/* Set Background */
		getmaxyx(stdscr, row, col); /* Get size of screen each time, in case of resize */
		mvwprintw(stdscr, 0, 0, "(%d, %d)", head->coords.x, head->coords.y);
		mvwprintw(stdscr, row - 1, 0, "direction=%i", d);
		/* End Setting Background */

		/* Prepare for next frame */
		/* ***MOVE SNAKE*** */
		/*
		   We must do this before calling getch(), or else the snake print!
		   (found this out via testing)

		   We want a delay between when the head moved and when the body is moved
		   (in general, we want a delay between the move of any given part and 
		   the move of the part after it). So, we can move and print the head normally, 
		   but we need to handle the following part carefully: instead of changing its position
		   and moving it in the same step, we split this into two steps and add a check in-between 
		   them. 
			Ex: d = RIGHT, head->direction = RIGHT, we want body->direction = RIGHT.
				Next frame: d = UP, head->direction = UP, we want body->direction = RIGHT
		*/
		moveprintpart(head); 
		movepart(body); 
		if (d != opposite(body->direction)) {
			body->direction = d;
		}
		printpart(body);
		printobj(&apple);
		/* ***DONE MOVING SNAKE*** */

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

    endwin();				/* End curses mode */
    return EXIT_SUCCESS;
}
