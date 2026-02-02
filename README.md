*This project has been created as part of the 42 curriculum by esaleh.*

# so_long

## Description
A small 2D tile-based game for the 42 so_long project. The player collects all
collectibles and exits the map using the shortest path (by design).

## Instructions

### Build

### Linux (42 evaluation machines)
- Requires MiniLibX for Linux in `./mlx_linux`.
- Build:

```
make
```

### macOS (local testing)
- Requires MiniLibX for macOS in `./mlx` (or update the Makefile paths).
- If you want a mac build, adjust the MLX section in `Makefile` to use:

```
MLX_DIR := mlx
MLX_LIB := $(MLX_DIR)/libmlx.a
MLX_FLAGS := -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
```

### Run

```
./so_long maps/level1.ber
```

## Controls
- Move: `W/A/S/D` or arrow keys
- Exit: `ESC` or window close button

## Map rules (.ber)
- Rectangular, surrounded by walls.
- Valid chars only: `0` (floor), `1` (wall), `C` (collectible), `E` (exit), `P` (player).
- Exactly one `P` and one `E`, at least one `C`.
- A valid path must exist from `P` to all `C` and to `E`.
- On error, the program exits cleanly with `Error` and a message.

## Project layout
- `src/` core game logic
- `include/so_long.h` public header
- `maps/` sample maps
- `textures/` XPM sprites
- `libft/` local copy of libft

## Notes
- Movement count is printed to the shell on every valid move.
- Bonus features are not implemented yet.

## Resources
- MiniLibX documentation and examples (42 intra resources and MLX repos).
- XPM format reference and general 2D tile-based game tutorials.
- 42 so_long subject PDF for rules, constraints, and required behavior.
- AI usage: none in the implementation; used only for README wording and structure.
