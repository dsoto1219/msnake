#include <stdlib.h>
#include <ncurses.h>
#include "../lib/snake.h"
#include "../lib/keys.h"

/* DIRECTION FUNCTIONS */

direction get_direction(int key, direction current_d) {
    switch (key) {
		case RIGHT_KEY: return RIGHT;
		case LEFT_KEY: return LEFT;
		case UP_KEY: return UP;
		case DOWN_KEY: return DOWN;
		case PAUSE_KEY:
		case HELP_KEY: return NONE;
		default: return current_d;
    }
}

direction opposite(direction d) {
    switch (d) {
		case RIGHT: return LEFT;
		case LEFT: return RIGHT;
		case UP: return DOWN;
		case DOWN: return UP;
		case NONE: return NONE;
		default: return d;
    }
}

char *dirtostr(direction d) {
    switch (d) {
		case RIGHT: return "RIGHT";
		case LEFT: return "LEFT";
		case UP: return "UP";
		case DOWN: return "DOWN";
		case NONE: return "NONE";
		// UND = Undefined
		default: return "UND";
    }
}

/* COOORDINATE FUNCTIONS */

bool coordsequal(coordinates c1, coordinates c2) {
	bool xequal = (c1.x == c2.x);
	bool yequal = (c1.y == c2.y);
	return xequal && yequal;
}

/* GAME OBJECTS */

void wprintobj(WINDOW *win, object obj) {
    mvwaddch(win, obj.coords.y, obj.coords.x, obj.attire);
}

void printobj(object obj) {
	wprintobj(stdscr, obj);
}

void wcolorprintobj(WINDOW *win, int color, object obj) {
	wattron(win, color);
	wprintobj(win, obj);
	wattroff(win, color);
}

void colorprintobj(int color, object obj) {
	wcolorprintobj(stdscr, color, obj);
}

void dmoveobj(object *obj, direction d) {
	coordinates *c = &obj->coords;
	switch (d) {
		case RIGHT:
			c->x++;
			break;
		case LEFT:
			c->x--;
			break;
		case UP:
			c->y--;
			break;
		case DOWN:
			c->y++;
			break;
		default: 
			return;
	}
}

/* Returns of object is outside of given bounds, including the boundaries themselves. */
bool outofbounds(object obj, int row, int col) {
	bool toofar_up = obj.coords.y <= 0;
	// We add the -1 to include the border around the window
	bool toofar_down = obj.coords.y >= row - 1;
	bool toofar_right = obj.coords.x >= col - 1;
	bool toofar_left = obj.coords.x <= 0;
	return (toofar_up || toofar_down || toofar_right || toofar_left);
}

/* Randomizes the coordinates of the given object such that the object remains inside
   the given boundaries (not including the boundaries themselves).
*/

void randcoords(object *obj, int row, int col) {
	/*
	   Instead of just randomizing coordinates and adding a check to make sure that they 
	   aren't out of bounds, we instead limit where the random coordinates 
	   could end up using the following logic (using row as an example, but the same logic
	   applies to col):

	   rand() % row \in \{0, 1, 2, ..., row \}
	   \implies rand() % (row - 2) \in \{0, 1, 2, ..., row - 2\}
	   \implies (rand() % (row - 2)) + 1 \in \{1, 2, 3, ..., row - 1\}
	*/
	obj->coords.y = (rand() % (row - 2)) + 1;
	obj->coords.x = (rand() % (col - 2)) + 1;
}

/* SNODE & SNAKE FUNCTIONS */
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

/* Add element to beginning of snake linked list */
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

	return new;
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

/*
   growsnake appends a body part to the end of the snake. Using the inputted direction,
   it ensures that the part is in the correct position.
*/
snake *growsnake(snake *head, direction d) {
	part body_p = { .attire = BODY_ATTIRE };
	snake *new = append(head, body_p); 

	new->part.coords = new->prev->part.coords;
	dmoveobj(&new->part, opposite(d));

	return new;
}

snake *pop(snake *head) {
	if (head == NULL) {
		// List is empty, nothing to pop
		return NULL;
	}

	snake *ptr;
	for (ptr = head; ptr->next != NULL; ptr = ptr->next);

	snake *new_tail = ptr->prev;
	new_tail->next = NULL;
	free(ptr);

	return new_tail;
}

/*
   Creates a snake of a given length using the inputted head and body parts. Since it uses
   growsnake to grow the snake to the given length, it takes in a starting direction as an 
   input to ensure parts are placed in the correct positions. The function returns the head of 
   the snake.

   Since growsnake() returns the tail of the snake, the user can input a pointer variable 
   to the tail to initialize the tail pointer in the program.
*/
snake *lcreatesnake(int init_y, int init_x, int length, snake **tail, direction start_d) {
	part head_p = { 
		.coords = {
			.y = init_y,
			.x = init_x,
		},
		.attire = HEAD_ATTIRE 
	};
	snake *head = createsnake(head_p);
	for (int i = 1; i < length; i++)
		*tail = growsnake(head, start_d);
	
	return head;
}

/* Prints each part of the snake. It prints the head last so that if the snake is dead,
   the head's "dead" attire will be printed on top of the body, rather than vice versa. 
*/
void wprintsnake(WINDOW *win, snake *head) {
	for (snake *ptr = head->next; ptr != NULL; ptr = ptr->next) {
		wprintobj(win, ptr->part);
	}
	wprintobj(win, head->part);
}

void printsnake(snake *head) {
	wprintsnake(stdscr, head);
}

void wcolorprintsnake(WINDOW *win, int color, snake *head) {
	wattron(win, color);
	wprintsnake(win, head);
	wattroff(win, color);
}

void colorprintsnake(int color, snake *head) {
	wcolorprintsnake(stdscr, color, head);
}

snake *movesnake(snake *head, snake *tail, direction d) {
	part *currenthead_pp = &head->part;
	part newhead_p = *currenthead_pp;
	dmoveobj(&newhead_p, d);
	currenthead_pp->attire = BODY_ATTIRE;

	head = insert(head, newhead_p);
	pop(tail);

	return head;
}

/* 
   Function for determining whether the inputted object is touching the snake (i.e.
   the object and some part of the snake share the same coordinates). 

   This function's last argument lets the user decide whether to include the head as one of 
   the parts to check the object against; this is because this function is used to determine 
   whether the snake head is touching some part of its body during the game. If the snake head 
   were always included, then during this check the snake would always techincally be "touching
   itself" (please excuse my poor choice of words).
*/
bool touchingsnake(snake *head, object obj, bool include_head) {
	snake *ptr = head;
	if (include_head == false) ptr = head->next;
	while (ptr != NULL) {
		if (coordsequal(obj.coords, ptr->part.coords)) 
			return true;
		ptr = ptr->next;
	}
	return false;
}

void nosnakerandcoords(snake *head, object *obj, int row, int col) {
	do {
		randcoords(obj, row, col);
	} while (touchingsnake(head, *obj, true));
}

/*
   Recursive function for freeing the snake linked list. 

   In any other case, I wouldn't use a recursive solution for safety reasons. However, 
   the shorts from CS50 that I relied on to build this project taught this method, 
   so I'm staying with this.
*/
void freesnake(snake *head) {
	if (head == NULL) 
		return;
	freesnake(head->next);
	free(head);
}
