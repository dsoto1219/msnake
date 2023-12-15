#ifndef SNAKE_H
#define SNAKE_H

#include "objects.h"

#define HEAD_ATTIRE '@'
#define BODY_ATTIRE 'O'
#define FOOD_ATTIRE '$'
#define DEAD_ATTIRE 'X'

/* Snake: Doubly Linked list of Parts */
typedef struct dllsnake {
	part part;
    struct dllsnake *prev;
    struct dllsnake *next;
} snake; 

snake *createsnake(part head_p);
snake *insert(snake *head, part p);
snake *append(snake *head, part p);
snake *growsnake(snake *head, direction d);
snake *pop(snake *head);
snake *lcreatesnake(part head_p, int l, direction start_d);
snake *movesnake(snake *head, snake *tail, direction d);
void wprintsnake(WINDOW *win, snake *head);
void printsnake(snake *head);
void wcolorprintsnake(WINDOW *win, int color, snake *head);
void colorprintsnake(int color, snake *head);
bool touchingsnake(snake *head, object obj, bool include_head);
void freesnake(snake *head);

#endif // !SNAKE_H
