#include <stdlib.h>
#include <ncurses.h>
#include "lib/snake.h"

/* Functions for parts */
// General movepart function
void dmovepart(part *p, direction d) {
    switch (d) {
		case RIGHT:
			p->coords.x++;
			break;
		case LEFT:
			p->coords.x--;
			break;
		case UP:
			p->coords.y--;
			break;
		case DOWN:
			p->coords.y++;
			break;
		case NONE:
			/* Do nothing */
			break;
		default: break;
    }
}

// Default movepart function, default value is p->direction
void movepart(part *p) {
	dmovepart(p, p->direction);
}

void printpart(part *p) {
    mvwaddch(stdscr, p->coords.y, p->coords.x, p->attire);
}

/* Combined dmovepart and printpart (inspired by combined ncurses functions, i.e. mvaddch) */
void dmoveprintpart(part *p, direction d) {
	dmovepart(p, d);
	printpart(p);
}

void moveprintpart(part *p) {
	dmoveprintpart(p, p->direction);
}

/* SNAKE FUNCTIONS */
snake *createsnake(int length, part head) {
	snake *S;
	S->length = length;
	S->head = head;
	return S;
}

snake *insert(snake *head, part p) {
	// 1. Allocate Node and Populate it with data
	snake *new = (snake *)malloc(sizeof(snake));
	if (new == NULL) {
		printf("Error: new snake part is NULL");
		exit(1);
	}
	new->part = p;

	// new is going to be the new head
	new->prev = NULL;
	new->next = head;
	head->prev = new;
	head = new;

	return new;
}

snake *append(snake *head, part p) {
	snake *new = (snake *)malloc(sizeof(snake));
	if (new == NULL) {
		printf("Error: new snake part is NULL");
		exit(1);
	}
	new->part = p;

	for (snake *ptr = head; ptr != NULL; ptr = ptr->next) {
	
	}

	return new; 
}

void freesnake(snake *head) {
	if (head == NULL) 
		return;
	freesnake(head->next);
	free(head);
}
