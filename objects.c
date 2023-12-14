#include <ncurses.h>
#include <stdlib.h>
#include "lib/objects.h"

bool coordsequal(coordinates c1, coordinates c2) {
	bool xequal = (c1.x == c2.x);
	bool yequal = (c1.y == c2.y);
	return xequal && yequal;
}

void wprintobj(WINDOW *win, object *obj) {
    mvwaddch(win, obj->coords.y, obj->coords.x, obj->attire);
}

void printobj(object *obj) {
	wprintobj(stdscr, obj);
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

/* Returns of object is outside of given bounds, including the boundaries themselves. */
bool outofbounds(object obj, int row, int col) {
	bool toofar_up = obj.coords.y <= 0;
	bool toofar_down = obj.coords.y >= row;
	bool toofar_right = obj.coords.x >= col;
	bool toofar_left = obj.coords.x <= 0;
	return (toofar_up || toofar_down || toofar_right || toofar_left);
}

/* Randomizes the coordinates of the given object such that the object remains inside
   the given boundaries (not including the boundaries themselves).
*/

void randcoords(object *obj, int row, int col) {
	/*
	   Instead of just randomizing coordinates and adding a check to make sure that they 
	   aren't out of bounds, we instead limit where the random coordinates 
	   could end up using the following logic (using row as an example, but the same logic
	   applies to col):

	   rand() % row \in \{0, 1, 2, ..., row \}
	   \implies rand() % (row - 2) \in \{0, 1, 2, ..., row - 2\}
	   \implies (rand() % (row - 2)) + 1 \in \{1, 2, 3, ..., row - 1\}
	*/
	obj->coords.y = (rand() % (row - 2)) + 1;
	obj->coords.x = (rand() % (col - 2)) + 1;
}
