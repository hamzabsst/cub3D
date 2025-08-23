# 🎮 Cub3D - 3D Raycasting Game Engine

## 🎮 What Can Cub3D Do?

**Current Status**: Cub3D is a 3D raycasting game engine in active development. It currently provides a solid foundation for parsing game maps and will eventually render a full 3D first-person experience.

### 📋 **Quick Answer**
Right now, cub3D can:
1. ✅ **Parse and validate** complex `.cub` map files
2. ✅ **Load textures** and validate game assets  
3. ✅ **Initialize graphics** systems and game state
4. ✅ **Detect and report** configuration errors
5. 🚧 **Render 3D environments** (in development)
6. 🚧 **Handle player movement** (in development)

When complete, it will be a fully playable 3D maze game similar to Wolfenstein 3D!

## 🚀 Current Capabilities

### ✅ **Completed Features**

#### **Map Parsing & Validation**
- Parse `.cub` configuration files
- Extract texture paths for all 4 walls (North, South, East, West)
- Parse floor and ceiling colors (RGB format)
- Validate map structure and contents
- Ensure maps are properly enclosed by walls
- Find and validate player starting position and direction

#### **Game State Initialization**
- Initialize MiniLibX graphics library
- Set up game window (1024x768)
- Load wall textures from XPM files
- Initialize player position and camera direction
- Create rendering buffer for fast pixel manipulation

#### **File Format Support**
- Supports `.cub` configuration files with the format:
  ```
  NO ./textures/north_wall.xpm
  SO ./textures/south_wall.xpm  
  WE ./textures/west_wall.xpm
  EA ./textures/east_wall.xpm
  
  F 220,100,0
  C 225,225,225
  
  111111111111
  100000000001
  100000N00001
  111111111111
  ```

### 🚧 **In Development**

#### **Raycasting Engine** (Phase 3)
- Calculate ray directions for each screen column
- Implement DDA (Digital Differential Analyzer) algorithm
- Find wall intersections and calculate distances
- Select appropriate wall textures based on hit direction
- Render vertical wall strips

#### **Player Controls** (Phase 4)
- WASD movement system
- Left/Right arrow key rotation
- ESC key for clean exit
- Window close button handling
- Wall collision detection

#### **Rendering Optimization** (Phase 5)
- Image buffer manipulation for better performance
- Avoid pixel-by-pixel rendering for full frames
- Efficient texture mapping

## 🎯 **Planned Features**

### **Core Functionality**
- Real-time 3D rendering using raycasting
- Textured walls with different textures per direction
- Colored floors and ceilings
- Smooth player movement and rotation
- Collision detection with walls

### **Bonus Features** ⭐
- Interactive minimap
- Wall collision (movement blocking)
- Openable/closable doors
- Mouse-controlled camera rotation
- Animated sprites (fire, objects, enemies)

## 🛠 **How to Use**

### **Prerequisites**
- Linux system with X11 development libraries
- GCC compiler
- Make

### **Installation**
```bash
# Install dependencies (Ubuntu/Debian)
sudo apt install libx11-dev libxext-dev

# Clone and build
git clone <repository_url>
cd cub3D
make

# Run with a map file
./cub3D maps/valid_map.cub
```

### **Current Output**
The program currently parses map files and displays information about:
- Loaded texture paths
- Floor and ceiling colors
- Map dimensions
- Player starting position and direction
- Map preview

Example output with a valid map:
```
$ ./cub3D maps/valid_map.cub
NO: ./textures/north_wall.xpm
SO: ./textures/south_wall.xpm
WE: ./textures/west_wall.xpm
EA: ./textures/east_wall.xpm
F: 220,100,0
C: 225,225,225
Map size: 24x14
Player at (1.0,1.0) facing N
Map preview (first 5 lines):
'111111111111111111111111'
'100000000110000000000001'
'101100000111000000000001'
'100100000000000000000001'
'111111111011000001110001'
```

Error handling example:
```
$ ./cub3D maps/test_invalid.cub
Map not closed - walkable area at border
Parsing failed

$ ./cub3D
Usage: ./cub3D map.cub
```

## 📁 **Project Structure**

```
cub3D/
├── src/           # Source code
│   ├── main.c     # Main program entry
│   ├── parsing/   # Map and config parsing
│   └── utils.c    # Utility functions
├── inc/           # Header files
├── maps/          # Sample map files
├── textures/      # Wall texture files (XPM format)
├── minilibx/      # Graphics library
├── mylib/         # Custom utility library
└── roadmap.md     # Development roadmap
```

## 🎮 **Map Format**

Maps use a simple text format:
- `1` = Wall
- `0` = Empty space (floor)
- `N/S/E/W` = Player starting position and direction
- Spaces = Void (outside playable area)

## 🔧 **Development Status**

According to the project roadmap:
- **Phase 1** ✅ **COMPLETED**: File parsing and validation
- **Phase 2** ✅ **COMPLETED**: Game state initialization  
- **Phase 3** 🚧 **IN PROGRESS**: Raycasting engine
- **Phase 4** 🚧 **IN PROGRESS**: Controls and events
- **Phase 5** 🚧 **IN PROGRESS**: Rendering optimization
- **Phase 6** 🚧 **IN PROGRESS**: Final touches and cleanup

## 🎯 **What Cub3D Will Be Able To Do (When Complete)**

1. **Render Real-Time 3D Environments**: Transform 2D maps into immersive 3D experiences
2. **Provide Interactive Gameplay**: Allow players to navigate through 3D mazes
3. **Display Textured Graphics**: Show different wall textures based on direction
4. **Handle User Input**: Respond to keyboard and potentially mouse controls
5. **Maintain Performance**: Deliver smooth gameplay through optimized rendering
6. **Support Custom Maps**: Load and display user-created map files

This project demonstrates fundamental 3D graphics concepts including raycasting, texture mapping, and real-time rendering - all core techniques used in early 3D games and still relevant in modern game development.