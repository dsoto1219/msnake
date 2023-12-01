#include <ncurses.h>
#include "lib/objects.h"

void printobj(object *obj) {
    mvwaddch(stdscr, obj->coords.y, obj->coords.x, obj->attire);
}

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

void printpart(part *p) {
    mvwaddch(stdscr, p->coords.y, p->coords.x, p->attire);
}

/* Combined dmovepart and printpart (inspired by combined ncurses functions, i.e. mvaddch) */
void dmoveprintpart(part *p, direction d) {
	dmovepart(p, d);
	printpart(p);
}

void moveprintpart(part *p) {
	dmoveprintpart(p, p->direction);
}

bool canmove(part *p, direction d) {
	if (d == opposite(p->direction)) return false;
	return true;
}
