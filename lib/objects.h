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

/* Parts (Technically a type of object) */
typedef struct part {
	coordinates coords;
	char attire;
    direction direction;
} part;

void dmovepart(part *p, direction d); 
void movepart(part *p); 
void printpart(part *p); 
void dmoveprintpart(part *p, direction d); 
void moveprintpart(part *p); 
bool canmove(part *p, direction d);

#endif // !OBJECTS_H
