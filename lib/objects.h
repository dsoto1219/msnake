#ifndef OBJECTS_H
#define OBJECTS_H

#include "direction.h"

typedef struct {
    int y, x;
} coordinates;

/* Wanted the snake's parts to inherit this */
typedef struct {
	coordinates coords;
    char attire;
} object;


typedef object food;
typedef object part;

void printobj(object *obj);
void dmoveobj(object *obj, direction d);

#endif // !OBJECTS_H
