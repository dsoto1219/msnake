#ifndef SNAKE_H
#define SNAKE_H

#include "objects.h"

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
