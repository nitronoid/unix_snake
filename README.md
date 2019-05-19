# Unix Snake

A simple program to make the classic snake game inside a Unix terminal.

## Build instructions
A makefile for Unix based systems is included.

> $ make

## Playing
After building, run the snake.out executable to start the game. 

You must provide 2 parameters to the game, the first is the size of the game and the second is the speed level.

The size is specified in number of terminal characters, and the speed is the fraction of a second specified as an integer, i.e. 1/1, 1/2, 1/3, 1/4, ...

```
$> # Launch a 20x20 game with refresh rate of 1/4 of a second
$> ./snake.out 20 4
```

The controls are WASD. The aim is to collect the food for points, and not hit yourself or the walls.

Press q to quit the game.

## Details

The aim of this project was to create a simple game in C with no external dependencies such as SDL or OpenGL.

The user input is handled asynchronously, using using pthreads to set up a dedicated thread for character input.

