# cub3D

A first-person maze renderer written in C with raycasting and MiniLibX, developed as part of the 42 curriculum.

## What is included

- Parsing and validation of `.cub` scene files.
- Raycasting, textured walls, and player movement with collision checks.
- A separate bonus implementation with minimap, doors, and boss-related source files.
- A bundled C utility library, sample maps, and texture assets.

## Requirements

Linux, Make, a C compiler, X11 development libraries, and a built MiniLibX Linux installation. The Makefile expects `/usr/include/minilibx-linux/libmlx.a`; adjust `MLX_DIR` if MiniLibX is installed elsewhere. The bundled `mylib/` is built by the main Makefile.

## Build and run

Run from the repository root so relative texture paths resolve:

```sh
make
./cub3D maps/map1.cub

make bonus
./cub3D_bonus maps/bonus/door_test.cub
```

Use **W/A/S/D** to move and the **left/right arrows** to rotate in the base version.

```sh
make clean
make fclean
make re
```

## Source map

| Path | Purpose |
| --- | --- |
| `src/` | Base renderer, game loop, player movement, and parsing |
| `src_bonus/` | Bonus implementation |
| `inc/` | Headers and shared types |
| `maps/` | Sample scene files |
| `mylib/` | C utility functions |

The commands reflect the current Makefile. A working graphical session and the external MiniLibX dependency are required to run the renderer.
