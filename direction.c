#include <ncurses.h>
#include "lib/direction.h"

direction get_direction(int key) {
    switch (key) {
		case KEY_RIGHT:
			return RIGHT;
			break;
		case KEY_LEFT:
			return LEFT;
			break;
		case KEY_UP:
			return UP;
			break;
		case KEY_DOWN:
			return DOWN;
			break;
		default: return NONE;
    }
}

direction opposite(direction d) {
    switch (d) {
		case RIGHT:
			return LEFT;
			break;
		case LEFT:
			return RIGHT;
			break;
		case UP:
			return DOWN;
			break;
		case DOWN:
			return UP;
			break;
		case NONE:
			return NONE;
			break;
		default: return NONE;
    }
}
