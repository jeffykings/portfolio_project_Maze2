# Raycasting Maze Game

A simple raycasting maze game implemented in C using SDL2.

## Table of Contents

- [Features](#features)
- [Prerequisites](#prerequisites)
- [Building](#building)
- [Controls](#controls)
- [Game Elements](#game-elements)
- [Contributing](#contributing)
- [License](#license)

## Features

- 3D raycasting engine
- Textured walls
- 2D minimap
- Enemy AI
- Weapon system
- Weather effects (rain)

## Prerequisites

To build and run this game, you'll need:

- SDL2 library
- C compiler (e.g., GCC)
- Make (optional, for build automation)

## Building

1. Clone the repository:
   ```
   git clone https://github.com/jeffykings/portfolio_project_Maze2.git
   cd portfolio_project_Maze2
   ```

2. Compile the game:
   ```
   gcc -Wall -Werror -Wextra -pedantic *.c -o maze_game -lSDL2 -lm
   ```

   Or, if you have a Makefile:
   ```
   make
   ```

3. Run the game:
   ```
   ./maze_game
   ```

## Controls

- W, A, S, D: Move the player
- Left/Right arrow keys: Rotate the camera
- M: Toggle minimap
- R: Toggle rain effect
- 1, 2, 3: Switch weapons
- ESC: Quit the game

## Game Elements

- Walls: Different colored/textured walls create the maze
- Enemies: Red squares that move randomly around the map
- Weapons: Three weapons to switch between (visual only)
- Weather: Optional rain effect

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is open source and available under the [MIT License](LICENSE).
