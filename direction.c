#include <ncurses.h>
#include "lib/direction.h"
#include "lib/keys.h"

direction get_direction(int key, direction current_d) {
    switch (key) {
		case KEY_RIGHT: return RIGHT;
		case KEY_LEFT: return LEFT;
		case KEY_UP: return UP;
		case KEY_DOWN: return DOWN;
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
