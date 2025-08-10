# 🧭 Cub3D Roadmap

## ✅ Phase 1: Parsing the .cub file (COMPLETED)
- [x] Read .cub line by line
- [x] Identify and store:
  - [x] NO path
  - [x] SO path
  - [x] WE path
  - [x] EA path
  - [x] F color
  - [x] C color
- [x] Extract map lines and store in 2D array
- [x] Validate map:
  - [x] Only `0`, `1`, `N`, `S`, `E`, `W`, and spaces
  - [x] Exactly 1 player start
  - [x] Map is surrounded by walls (no holes in interior)
- [x] Normalize map (padding for jagged lines)
- [x] Handle file format errors and exit with `Error\n<msg>`

**Note**: Current test map has interior holes (spaces inside map area). Need valid test map.

---

## ✅ Phase 2: Init Game State (COMPLETED)
- [x] Init MiniLibX
- [x] Open window (1024x768)
- [x] Init player direction & camera plane based on N/S/E/W
- [x] Load textures with `mlx_xpm_file_to_image`
- [x] Store floor and ceiling colors in RGB format
- [x] Create rendering buffer for fast pixel manipulation

---

## 🚧 Phase 3: Raycasting Engine
- [ ] For each column on screen:
  - [ ] Calculate ray direction
  - [ ] Run DDA to find wall hit
  - [ ] Calculate perpendicular distance
  - [ ] Choose wall texture (NO, SO, EA, WE)
  - [ ] Compute texture x coordinate
  - [ ] Render vertical strip using `mlx_pixel_put` or image buffer
- [ ] Display floor and ceiling

---

## 🚧 Phase 4: Controls and Events
- [ ] WASD movement
- [ ] Left/Right arrow rotation
- [ ] ESC exits cleanly
- [ ] Red cross exit (window close hook)
- [ ] Collision detection (optional if bonus)

---

## 🚧 Phase 5: Rendering Optimization
- [ ] Use `mlx_new_image`, `mlx_get_data_addr`, `mlx_put_image_to_window`
- [ ] Avoid `mlx_pixel_put` for full frame

---

## ✅ Phase 6: Final Touches
- [ ] Error handling for all cases
- [ ] Leak check (valgrind)
- [ ] Norminette OK
- [ ] Proper exit with free()

---

## ⭐ Bonus (only if mandatory is perfect)
- [ ] Wall collision (movement blocked on `1`)
- [ ] Minimap
- [ ] Open/close doors
- [ ] Mouse movement to rotate view
- [ ] Sprites (e.g. fire, objects, enemies)

