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
- [x] **BONUS: Clean structure consolidation** - Merged all sub-structures into one clean `t_game` struct

---

## ✅ Phase 3: Raycasting Engine (COMPLETED - MANDATORY REQUIREMENT)
**THIS IS YOUR MAIN FOCUS - Without this, the project fails completely**
- [x] **Core Algorithm Implementation:**
  - [x] For each screen column (x = 0 to WIDTH):
    - [x] Calculate ray direction from player position
    - [x] Run simple stepping algorithm to find wall hit
    - [x] Calculate distance to avoid fisheye effect ✅ **FIXED!**
    - [x] Determine wall height on screen
    - [x] Choose correct wall texture (NO/SO/EA/WE based on hit side)
    - [x] Calculate texture x-coordinate
    - [x] Render textured vertical strip pixel by pixel
- [x] **Wall Texture Rendering:**
  - [x] Extract texture pixel data from loaded images
  - [x] Apply correct texture based on wall orientation
  - [x] Handle texture scaling and positioning
- [x] **Performance:**
  - [x] Use image buffer instead of mlx_pixel_put for speed
  - [x] Render ceiling and floor efficiently
- [x] **Fixed Issues:**
  - [x] Segmentation faults in raycast and player movement ✅
  - [x] Empty spaces in irregular maps (jagged.cub) ✅
  - [x] Fisheye effect correction ✅
  - [x] Code simplification and optimization ✅

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

### ✅ **1. Structure Cleanup (COMPLETED!)**
Successfully consolidated all structures into one clean `t_game` struct:
- ❌ Removed: `t_vector`, `t_player`, `t_map`, `t_textures`, `t_mlx`
- ✅ Now: Single clean `t_game` structure with direct access
- ✅ All compilation errors fixed
- ✅ Program compiles and runs successfully

### 🔥 **2. Implement Basic Raycasting (CRITICAL - START HERE)**
Create a new file `src/raycasting.c` with:
- Ray direction calculation
- DDA algorithm implementation
- Wall hit detection
- Distance calculation
- Basic wall rendering

### 🔥 **3. Add Movement Controls (REQUIRED)**
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

