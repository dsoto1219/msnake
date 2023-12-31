# MSnake: A Minimalistic Snake Game for the Terminal

Final Project for CS50x.

#### Video Demo: https://www.youtube.com/watch?v=-gqIlLWRuK8

## Description

A terminal snake game, meant to be an alternative for the popular [nSnake](https://github.com/alexdantas/nSnake). The snake's behavior is built to be more responsive, and the game itself is meant to be more minimalistic and easily replayable. 

### File Descriptions:

#### Source files (found in `src/`):

- `snake.c`: Contains all functions related to the snake game, such as functions for creating the snake, deleting the snake, moving the snake, creating and positioning the food, and other lower-level functions that would otherwise clutter the `main.c` file if they were declared in that file.
- `main.c`: Contains `main()`, which handles creating the game window and handling all game logic.

#### Header files (found in `lib/`):

- `snake.h`: Top-level declarations of functions found in `snake.c`, as well as definitions of structs that define game objects, such as the snake's `food` and the snake itself.
- `keys.h`: Top-level declarations of global variables that define the keys that are to be used for the game.


### Design Choices

#### `timeout()`

To make the snake more responsive, I used the `ncurses` function (timeout) to handle how the game reads keypresses. With this setting, if the key-reading function `getch` reads a key, the program's response is immediate, thus allowing the snake to move exactly when the player prompts it to move (if this function does not read a key, it simply returns).  

#### `typedef struct { ... } object`

I tried to employ polymorphism in this project by creating a general "object" struct and having the parts of the snake and the snake's food be types of objects. 

#### `Linked list nodes`

If I could start this project over (which I might do at some point), I would redo the snake's logic as a linked list, instead calling each node an `snode` (snake node) instead of the confusing `snake` term, and I would create an entirely new struct called `snake` that would keep track of the head of the snode head, the snode tail, and the length of the snode linked list.

### Roadmap

In the future, I plan to bring more customization into the game; meaning, I would like to give the player control over a number of aspects of the game, including (but not limited to):

- The game's controls
- The game's window sizes
- How the snake and apple looks 

This game has been tested only on Windows 11's WSL2 Ubuntu 22.04. I have plans to dockerize the source code so it can be tested on other platforms.

### Known issues

Issues are listed in decreasing order of importance.

- Memory leak in at least one of the functions used to move the snake.
- Terminal's cursor disappears after quitting the game. 
- Snake can "sprint" if any of its movement keys are held down.

## Installation

### Building From Source

Requirements: GCC, GNU make, and ncurses.

1. Clone this repository, and change your directory to its location.
2. Run `make snake`.

## How to play

- Run `./snake` to run the game. 
- Use the arrow keys to move the snake in any given direction.
- Press `p` or `h` to pause the game (note: at this time, despite the bottom-left message, pressing `h` does not display a help message).
- Press `r` to restart the game. 
- Press `q` to quit the game.
