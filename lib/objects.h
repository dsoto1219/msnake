#ifndef OBJECTS_H
#define OBJECTS_H

#include <ncurses.h>
#include "direction.h"

typedef struct {
    int y, x;
} coordinates;

bool coordsequal(coordinates c1, coordinates c2);

/* Wanted the snake's parts to inherit this */
typedef struct {
	coordinates coords;
    char attire;
} object;

typedef object food;
typedef object part;

void wprintobj(WINDOW *win, object *obj);
void printobj(object *obj);
void dmoveobj(object *obj, direction d);

#endif // !OBJECTS_H
