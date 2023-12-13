#include <ncurses.h>
#include "lib/objects.h"

void wprintobj(WINDOW *win, object *obj) {
    mvwaddch(win, obj->coords.y, obj->coords.x, obj->attire);
}

void printobj(object *obj) {
	wprintobj(stdscr, obj);
}

bool coordsequal(coordinates c1, coordinates c2) {
	bool xequal = (c1.x == c2.x);
	bool yequal = (c1.y == c2.y);
	return xequal && yequal;
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
