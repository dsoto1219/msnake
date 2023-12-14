#ifndef DIRECTION_H
#define DIRECTION_H

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

#endif // !DIRECTION_H

