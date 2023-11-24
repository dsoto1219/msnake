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

void printobj(object *obj);

typedef object food;

#endif // !OBJECTS_H
