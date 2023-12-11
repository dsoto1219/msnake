#include <ncurses.h>
#include "lib/objects.h"

void printobj(object *obj) {
    mvwaddch(stdscr, obj->coords.y, obj->coords.x, obj->attire);
}

void dmoveobj(object *obj, direction d) {
	coordinates *c = &obj->coords;
	switch (d) {
		case RIGHT:
			c->x++;
			break;
		case LEFT:
			c->x--;
			break;
		case UP:
			c->y--;
			break;
		case DOWN:
			c->y++;
			break;
		default: 
			return;
	}
}
