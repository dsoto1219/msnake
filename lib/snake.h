#ifndef SNAKE_H
#define SNAKE_H

#include <ncurses.h>

#define HEAD_ATTIRE '@'
#define BODY_ATTIRE 'O'
#define FOOD_ATTIRE '$'
#define DEAD_ATTIRE 'X'

typedef enum direction {
	NONE,
    RIGHT,
    LEFT,
    UP,
    DOWN
} direction;

direction get_direction(int key, direction current_d);
direction opposite(direction d);
char *dirtostr(direction d);

typedef struct {
    int y; 
	int x;
} coordinates;

bool coordsequal(coordinates c1, coordinates c2);

/* Wanted the snake's parts to inherit this */
typedef struct {
	coordinates coords;
    char attire;
} object;

void wprintobj(WINDOW *win, object obj);
void printobj(object obj);
void wcolorprintobj(WINDOW *win, int color, object obj);
void colorprintobj(int color, object obj);
void dmoveobj(object *obj, direction d);
bool outofbounds(object obj, int row, int col);
void randcoords(object *obj, int row, int col);

typedef object food; 
typedef object part;

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
snake *lcreatesnake(int init_y, int init_x, int length, snake **tail, direction start_d);
snake *movesnake(snake *head, snake *tail, direction d);
void wprintsnake(WINDOW *win, snake *head);
void printsnake(snake *head);
void wcolorprintsnake(WINDOW *win, int color, snake *head);
void colorprintsnake(int color, snake *head);
bool touchingsnake(snake *head, object obj, bool include_head);
void nosnakerandcoords(snake *head, object *obj, int row, int col);
void freesnake(snake *head);

#endif // !SNAKE_H
