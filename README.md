# Game of Life GB

## About

A port of Conway's Game of Life for the Game Boy.

## How to use

The game is simple to use:
- A - Put / Remove cell from grid
- Start - Pause/Unpause the simulation
- Select - Go to settings menu (only when it's paused)
- Directional Pad - Moves the cursor on the grid when paused

### Settings menu

The settings menu allow to change the rules on the grid and clear/randomize the grid.

- Left or Right to increment/decrement a value settings
- A to action a settings (randomize grid or clear grid)
- B or Select to go back in the grid.

## How to compile

Just do these commands if it's the first time building it:

```
mkdir build
cd build
cmake ..
make
```

And a `GameOfLife.gb` file will be generated!
