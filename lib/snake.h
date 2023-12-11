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

snake *createsnake(part head_p);
snake *append(snake *head, part p);
snake *growsnake(snake *head, direction d);
snake *lcreatesnake(part head_p, int l, direction start_d);
void printsnake(snake *head);
void freesnake(snake *head);

#endif // !SNAKE_H
