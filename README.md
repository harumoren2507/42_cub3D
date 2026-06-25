*This project has been created as part of the 42 curriculum by retoriya, maono.*

## Description
A raycasting 3D game like Wolfenstein 3D. Renders .cub maps in real-time using miniLibX. Features include 4-direction wall textures, floor/ceiling colors, and basic player movement.

## Demo
![Demo](./cub3d.gif)

## Instructions
Just run make to compile:
```bash
make
```

Then run it with a map:
```bash
./cub3D maps/test.cub
```

Controls:
- W/S: Move forward / backward
- A/D: Strafe left / right
- Left/Right arrows: Rotate view
- ESC or red cross: Quit game

Clean object files with `make clean` or `make fclean`.

## Resources
- Lode's Raycasting Tutorial (https://lodev.org/cgtutor/raycasting.html)
- miniLibX documentation
- AI was used to help find and fix some bugs.
