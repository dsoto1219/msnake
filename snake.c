#include <stdlib.h>
#include <ncurses.h>
#include "lib/snake.h"

/* SNAKE FUNCTIONS */
// Declare head of snake
snake *createsnake(part p) {
	snake *head = (snake *)malloc(sizeof(snake));
	if (head == NULL) exit(1);
	head->part = p;

	head->prev = NULL;
	head->next = NULL;

	return head;
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

	for (snake *ptr = head; ptr != NULL; ptr = ptr->next);

	return new; 
}

void freesnake(snake *head) {
	if (head == NULL) 
		return;
	freesnake(head->next);
	free(head);
}
