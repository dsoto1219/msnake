#ifndef SNAKE_H
#define SNAKE_H

#include "objects.h"

/* Part */
typedef struct part {
	coordinates coords;
	char attire;
    direction direction;
} part;

void dmovepart(part *p, direction d); 
void movepart(part *p); 
void printpart(part *p); 


/* Snake */
typedef struct snake {
    int length;
    part head;
    part *nextbody;
} snake; 

void movesnake(snake *S, direction d);

#endif // !SNAKE_H
