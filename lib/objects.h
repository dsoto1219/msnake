#ifndef OBJECTS_H
#define OBJECTS_H

#include "direction.h"

typedef struct {
    int y, x;
} coordinates;

/* An object is anything that can be printed onto the screen. */
typedef struct {
	coordinates coords;
    char attire;
} object;

typedef object food;

#endif // !OBJECTS_H
