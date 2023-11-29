#ifndef SNAKE_H
#define SNAKE_H

#include "objects.h"

/* Parts */
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

/* Snake: Doubly Linked list of Parts */
typedef struct dllsnake {
	part part;
    struct dllsnake *prev;
    struct dllsnake *next;
} snake; 

snake *createsnake(part p);
snake *insert(snake *head, part p);
void movesnake(snake *head, direction d);
void freesnake(snake *head);

#endif // !SNAKE_H
