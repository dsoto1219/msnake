#ifndef SNAKE_H
#define SNAKE_H

#include "objects.h"

#define HEAD_ATTIRE '@'
#define BODY_ATTIRE 'O'
#define FOOD_ATTIRE '$'

/* Snake: Doubly Linked list of Parts */
typedef struct dllsnake {
	part part;
    struct dllsnake *prev;
    struct dllsnake *next;
} snake; 

snake *createsnake(part p);
snake *append(snake *head, part p);
void printsnake(snake *head);
void growsnake(snake *head);
void dmovesnake(snake *head, direction d);
void movesnake(snake *head);
void freesnake(snake *head);

#endif // !SNAKE_H
