#include <ncurses.h>
#include "lib/objects.h"

void printobj(object *obj) {
    mvwaddch(stdscr, obj->coords.y, obj->coords.x, obj->attire);
}
