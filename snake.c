#include <stdlib.h>
#include <ncurses.h>
#include "lib/snake.h"

/* SNAKE FUNCTIONS */
// Declare head of snake
snake *createsnake(part p) {
	snake *head = (snake *)malloc(sizeof(snake));
	if (head == NULL) {
		fprintf(stderr, "Unable to allocate memory for new part");
		exit(1);
	}
	head->part = p;

	head->prev = NULL;
	head->next = NULL;

	return head;
}

snake *append(snake *head, part p) {
	snake *new = (snake *)malloc(sizeof(snake));
	if (new == NULL) {
		fprintf(stderr, "Unable to allocate memory for new part");
		exit(1);
	}
	new->part = p;

	for (snake *ptr = head; true; ptr = ptr->next) {
		if (ptr->next == NULL) {
			ptr->next = new;
			new->prev = ptr;
			break;
		}
	}
	new->next = NULL;

	return new; 
}

void printsnake(snake *head) {
	for (snake *ptr = head; ptr != NULL; ptr = ptr->next) {
		printpart(&ptr->part);
	}
}

void growsnake(snake *head) {
	part body_p = head->part;
	body_p.attire = BODY_ATTIRE;
	snake *new = append(head, body_p);
	snake *prev = new->prev;
	new->part.coords = prev->part.coords;
	dmovepart(&new->part, opposite(new->prev->part.direction));
}

void dmovesnake(snake *head, direction d) {
	// 1. Move head in direction d
	part *phead_p = &head->part;
	if (canmove(phead_p, d)) {
		dmovepart(phead_p, d);
	}

	// 2. Move connected parts in the direction their previous parts are travelling in 
	for (snake *ptr = head->next; ptr != NULL; ptr = ptr->next) {
		dmovepart(&ptr->part, ptr->prev->part.direction);
	}
}

void movesnake(snake *head) {
	dmovesnake(head, head->part.direction);
}

void freesnake(snake *head) {
	if (head == NULL) 
		return;
	freesnake(head->next);
	free(head);
}
