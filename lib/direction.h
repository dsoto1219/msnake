#ifndef DIRECTION_H
#define DIRECTION_H

typedef enum direction {
	NONE,
    RIGHT,
    LEFT,
    UP,
    DOWN
} direction;

direction get_direction(int key);
direction opposite(direction d);

#endif // !DIRECTION_H

