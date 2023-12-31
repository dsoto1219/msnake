# MSnake: A Minimalistic Snake Game for the Terminal

Final Project for CS50x.

## Description

A terminal snake game, meant to be an alternative for the popular [nSnake](https://github.com/alexdantas/nSnake). The snake's behavior is built to be more responsive, and the game itself is meant to be more minimalistic and easily replayable. 

### Roadmap

In the future, I plan to bring more customization into the game; meaning, I would like to give the player control over:

- The game's controls
- How the snake and apple looks 

Moreover, this game has been tested only on Windows 11's WSL2 Ubuntu 22.04. I have plans to dockerize the source code so it can be tested on other platforms.

### Known issues

Issues are listed in decreasing order of importance.

- Memory leak in at least one of the functions used to move the snake.
- Terminal's cursor disappears after quitting the game. 
- Snake can "sprint" if any of its movement keys are held down.

## Installation

### Building From Source

Requirements: GCC, GNU make.

1. Clone this repository, and change your directory to its location.
2. Run `make snake`.

## How to play

- Run `./snake` to run the game. 
- Use the arrow keys to move the snake in any given direction.
- Press `p` or `h` to pause the game (note: at this time, despite the bottom-left message, pressing `h` does not display a help message).
- Press `r` to restart the game. 
- Press `q` to quit the game.
