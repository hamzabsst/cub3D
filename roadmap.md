# 🧭 Cub3D Roadmap - Updated Based on Subject Requirements

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

---

## ✅ Phase 2: Init Game State (COMPLETED)
- [x] Init MiniLibX
- [x] Open window (1024x768)
- [x] Init player direction & camera plane based on N/S/E/W
- [x] Load textures with `mlx_xpm_file_to_image`
- [x] Store floor and ceiling colors in RGB format
- [x] Create rendering buffer for fast pixel manipulation

---

## 🚧 Phase 3: Raycasting Engine (CRITICAL - MANDATORY REQUIREMENT)
**THIS IS YOUR MAIN FOCUS - Without this, the project fails completely**
- [ ] **Core Algorithm Implementation:**
  - [ ] For each screen column (x = 0 to WIDTH):
    - [ ] Calculate ray direction from player position
    - [ ] Run DDA (Digital Differential Analyzer) to find wall hit
    - [ ] Calculate perpendicular distance to avoid fisheye effect
    - [ ] Determine wall height on screen
    - [ ] Choose correct wall texture (NO/SO/EA/WE based on hit side)
    - [ ] Calculate texture x-coordinate
    - [ ] Render textured vertical strip pixel by pixel
- [ ] **Wall Texture Rendering:**
  - [ ] Extract texture pixel data from loaded images
  - [ ] Apply correct texture based on wall orientation
  - [ ] Handle texture scaling and positioning
- [ ] **Performance:**
  - [ ] Use image buffer instead of mlx_pixel_put for speed
  - [ ] Render ceiling and floor efficiently

---

## 🚧 Phase 4: Controls and Events (MANDATORY REQUIREMENT)
**Required by subject - Must be implemented before submission**
- [ ] **Movement Controls (WASD):**
  - [ ] W: Move forward in direction vector
  - [ ] S: Move backward
  - [ ] A: Strafe left (perpendicular to direction)
  - [ ] D: Strafe right
- [ ] **Camera Rotation (Arrow Keys):**
  - [ ] Left Arrow: Rotate camera left
  - [ ] Right Arrow: Rotate camera right
  - [ ] Update both direction vector and camera plane
- [ ] **Exit Controls:**
  - [ ] ESC key: Close window and exit cleanly
  - [ ] Red cross (X): Close window and exit cleanly
- [ ] **Smooth Movement:**
  - [ ] Handle multiple key presses
  - [ ] Consistent movement speed

---

## 🚧 Phase 5: Rendering Optimization (MANDATORY REQUIREMENT)
**Required for proper performance**
- [ ] **Image Buffer Usage:**
  - [ ] Use mlx_new_image, mlx_get_data_addr, mlx_put_image_to_window
  - [ ] Avoid mlx_pixel_put for full frame rendering
  - [ ] Double buffering for smooth display
- [ ] **Window Management:**
  - [ ] Smooth window switching, minimizing, etc.
  - [ ] Proper event handling

---

## ✅ Phase 6: Final Touches (MANDATORY REQUIREMENT)
**Required for project submission**
- [ ] **Error Handling:**
  - [ ] All error cases return "Error\n" + message
  - [ ] Proper file validation
  - [ ] Handle invalid maps, textures, colors
- [ ] **Memory Management:**
  - [ ] No memory leaks (valgrind clean)
  - [ ] Proper cleanup on exit
  - [ ] Free all allocated resources
- [ ] **Code Quality:**
  - [ ] Norminette compliance
  - [ ] Makefile with all, clean, fclean, re rules
  - [ ] Proper error exit codes

---

## 🎯 **IMMEDIATE PRIORITY (Next Steps):**

### 1. **Fix Camera Plane Setup (URGENT)**
Your current `set_direction` function has incorrect camera plane calculations:
- East/West directions need perpendicular camera planes
- The plane should always be perpendicular to direction vector

### 2. **Implement Basic Raycasting (CRITICAL)**
Create a new file `src/raycasting.c` with:
- Ray direction calculation
- DDA algorithm implementation
- Wall hit detection
- Distance calculation
- Basic wall rendering

### 3. **Add Movement Controls (REQUIRED)**
Update your game loop to handle:
- Key press events for WASD movement
- Arrow key rotation
- Update player position and direction

---

## ⭐ Bonus (ONLY after mandatory is 100% complete)
- [ ] Wall collision (movement blocked on `1`)
- [ ] Minimap
- [ ] Open/close doors
- [ ] Mouse movement to rotate view
- [ ] Animated sprites

**⚠️ WARNING: Bonuses are IGNORED if mandatory part is not perfect!**

