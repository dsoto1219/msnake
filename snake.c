#include <stdlib.h>
#include <ncurses.h>
#include "lib/snake.h"

/* SNAKE FUNCTIONS */
/* Initializes the snake linked list by creating the first element (the head), and returns the new head. */
snake *createsnake(part head_p) {
	snake *head = (snake *)malloc(sizeof(snake));
	if (head == NULL) {
		fprintf(stderr, "Unable to allocate memory for new part");
		exit(1);
	}
	head->part = head_p;

	head->prev = NULL;
	head->next = NULL;

	return head;
}

snake *insert(snake *head, part body_p) {
	snake *new = (snake *)malloc(sizeof(snake));
	if (new == NULL) {
		fprintf(stderr, "Unable to allocate memory for new part");
		exit(1);
	}
	new->part = body_p;

	new->prev = NULL;
	new->next = head;
	head->prev = new;
	head = new;

	return head;
}

/*
	Appends a part to snake linked list. This is a generic function for adding an element to a doubly linked list. 
	Returns the (new) tail of the snake.
	Note: this function does not necessarily place the part in the correct position for it to look correct on the screen.
	The function for that is growsnake, which relies on this function.
*/
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

/* Inputs: head of the snake, direction of the snake */
snake *growsnake(snake *head, direction d) {
	part body_p = { .attire = BODY_ATTIRE };
	snake *new = append(head, body_p); 

	new->part.coords = new->prev->part.coords;
	dmoveobj(&new->part, opposite(d));

	return new;
}

snake *pop(snake *head) {
	snake *ptr;
	for (ptr = head; ptr->next != NULL; ptr = ptr->next);
	snake *new_tail = ptr->prev;
	new_tail->next = NULL;
	free(ptr);

	return new_tail;
}

/*
   Creates a snake of a given length using the inputted head and body parts.
*/
snake *lcreatesnake(part head_p, int l, direction start_d) {
	snake *head = createsnake(head_p);
	for (int i = 1; i < l; i++)
		growsnake(head, start_d);
	return head;
}

void printsnake(snake *head) {
	for (snake *ptr = head; ptr != NULL; ptr = ptr->next)
		printobj(&ptr->part);
}

void movesnake(snake *head, direction d) {
	// TODO
}

/*
   Function for freeing the snake linked list. 
   In any other case, I wouldn't use a recursive solution for safety reasons. However, CS50 taught us this recursive 
   algorithm for freeing the snake in the shorts that I relied on to build this project, so I'm staying with this.
*/
void freesnake(snake *head) {
	if (head == NULL) 
		return;
	freesnake(head->next);
	free(head);
}
