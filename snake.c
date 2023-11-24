#include <ncurses.h>
#include "lib/snake.h"

/* Functions for parts */
// General movepart function
void dmovepart(part *p, direction d) {
    switch (d) {
		case RIGHT:
			p->coords.x++;
			break;
		case LEFT:
			p->coords.x--;
			break;
		case UP:
			p->coords.y--;
			break;
		case DOWN:
			p->coords.y++;
			break;
		case NONE:
			/* Do nothing */
			break;
		default: break;
    }
}

// Default movepart function, default value is p->direction
void movepart(part *p) {
	dmovepart(p, p->direction);
}

// Using this to abstract away the ncurses library as much as possible
void printpart(part *p) {
    mvwaddch(stdscr, p->coords.y, p->coords.x, p->attire);
}
