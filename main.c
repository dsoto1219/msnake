#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "lib/direction.h"
#include "lib/snake.h"

#define TIMEOUT_DELAY 125		/* Delay is in ms */
#define INITIAL_SNAKE_LENGTH 3

int main(void) {
    // setlocale(LC_ALL, "");

	initscr();					/* Start curses mode */
	noecho();					/* getch() doesn't print the character it receives */
    curs_set(0);				/* Hide cursor */
    keypad(stdscr, TRUE);		/* Enable F1,...,F12 and arrow keys in stdscr */
    timeout(TIMEOUT_DELAY);

	/* Save window boundaries to row, col */
    int row, col;
    getmaxyx(stdscr, row, col);

	srand(time(NULL));
	/* Init apple */
	food apple = {
		.coords.y = rand() % row,
		.coords.x = rand() % col,
		.attire = '@' 
	};

	/* Init snake as a linked list of parts */
	part head_p = {
		.coords.y = rand() % row,
		.coords.x = rand() % col,
		.attire = 'O',
		.direction = RIGHT
	};
	snake *head = createsnake(head_p);

	// Create snake parts 1 and 2 by inserting them (head is part 0)
	part p;

	p.coords.y = head->part.coords.y;
	p.coords.x = head->part.coords.x - 1;
	p.attire = 'o';
	p.direction = head->part.direction;
	head = insert(head, p);
	p.coords.y = head->part.coords.y;
	p.coords.x = head->part.coords.x - 1;
	p.attire = 'o';
	p.direction = head->part.direction;
	head = insert(head, p);

    int key;
    direction d = head->part.direction; /* Direction for the entire snake to move in */
    while (true) {
		/* Set and Print Background */
		getmaxyx(stdscr, row, col); /* Get size of screen each time, in case of resize */
		mvwprintw(stdscr, 0, 0, "(%d, %d)", head->part.coords.x, head->part.coords.y);
		mvwprintw(stdscr, row - 1, 0, "direction=%i", d);

		printobj(&apple);
		for (snake *ptr = head; ptr != NULL; ptr = ptr->next) {
			part *p = &ptr->part;
			moveprintpart(p);
			if (d != opposite(head->part.direction)) {
				p->direction = d;
			}
		}

		if ((key = getch()) != ERR) {
			d = head->part.direction;
			head->part.direction = get_direction(key);
		}

		refresh();
		erase();
    }

	freesnake(head);

    endwin();				/* End curses mode */
    return EXIT_SUCCESS;
}
