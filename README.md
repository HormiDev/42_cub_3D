*This project has been created as part of the 42 curriculum by ide-dieg, ismherna.*

## Description

**cub3D** is a raycasting 3D graphics engine project that creates an immersive first-person perspective view of a maze-like environment using texture-mapped walls. The project implements fundamental computer graphics concepts including raycasting algorithms, coordinate transformations, collision detection, and real-time rendering.

### Project Goal

The objective is to create a functional 3D game engine using the raycasting technique (similar to classic games like Wolfenstein 3D) where:
- Players navigate through a textured maze environment
- Walls are rendered with realistic textures and perspective correction
- The system handles collision detection and player movement physics
- A minimap provides top-down navigation view
- Various bonus features enhance the gaming experience

### Key Features

**Core Features:**
- Raycasting-based 3D rendering engine
- Texture mapping on walls (4 directions: North, South, East, West)
- First-person perspective camera with smooth rotation and movement
- Player collision detection with walls and obstacles
- Customizable wall and floor/ceiling colors
- Map parsing from `.cub` configuration files
- Real-time performance with optimized rendering

**Bonus Features:**
- Interactive menu system with settings
- Audio system for immersive gameplay
- Gamepad/controller support
- Sprite/object rendering system with depth sorting
- Interactive doors
- Multiple resolution support
- Advanced visual effects (fisheye correction, vector clouds)
- Flamethrower weapon mechanics

## Instructions

### Requirements

- **Operating System**: Linux (with X11 support)
- **Compiler**: GCC or Clang with C99 or later
- **Build Tool**: Make
- **Libraries**: 
  - X11 development libraries
  - Math library (libm)
  - Graphics libraries (Xext)

### Installation & Compilation

#### 1. Clone the Repository

```bash
git clone <repository-url>
cd cub3D
```

#### 2. Install System Dependencies

For Debian/Ubuntu:
```bash
sudo apt-get install gcc make libx11-dev libxext-dev
```

For Fedora/RHEL:
```bash
sudo dnf install gcc make libX11-devel libXext-devel
```

For Arch:
```bash
sudo pacman -S gcc make libx11 libxext
```

#### 3. Compile the Project

**Standard version:**
```bash
make
```

**Bonus version (with extended features):**
```bash
make bonus
```

**Recompile from scratch:**
```bash
make re          # Standard version
make rebonus     # Bonus version
```

**Clean build artifacts:**
```bash
make clean       # Remove object files
make fclean      # Remove all generated files
```

### Execution

#### Running the Standard Version

```bash
./cub3D maps/example1.cub
```

#### Running the Bonus Version

```bash
./cub3D_bonus maps/example1.cub
```

#### Map File Format

Maps must be `.cub` files with the following structure:

```
# Texture paths (North, South, East, West)
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm

# Ceiling and Floor colors (R,G,B format: 0-255)
C 220,216,0
F 50,50,50

# Map layout
# 1 = wall, 0 = empty space, N/S/E/W = player start position and direction
1111111111
1000000001
1001000001
100100S001
1001000001
1000000001
1111111111
```

#### Game Controls

| Key | Action |
|-----|--------|
| `W` / `↑` | Move forward |
| `A` / `←` | Move left |
| `S` / `↓` | Move backward |
| `D` / `→` | Move right |
| `Left Arrow` | Rotate camera left |
| `Right Arrow` | Rotate camera right |
| `Shift` | Run (faster movement) |
| `M` | Toggle minimap display |
| `ESC` | Exit game |

**Bonus Controls:**
| Key | Action |
|-----|--------|
| `E` | Interact with objects/doors |
| `SPACE` | Weapon activation (bonus) |
| `Mouse Movement` | Camera rotation (bonus) |

### Example Maps

The project includes several pre-made maps in the `maps/` directory:
- `example1.cub` to `example8.cub` - Various maze configurations for testing

### Build Targets Summary

```bash
make all        # Compile standard version (default)
make bonus      # Compile bonus version
make clean      # Remove object files only
make fclean     # Remove all compiled files
make re         # Full rebuild (standard)
make rebonus    # Full rebuild (bonus)
```

## Resources

### Core Concepts & Algorithms

- **Raycasting Algorithm**: "Raycasting Graphics in C" - Implementation of ray-wall intersection detection
  - Used in: Entire rendering pipeline (`src/raycast/`)
  - Useful for: Understanding 3D projection from 2D map data

- **3D Graphics Mathematics**: "What Every Programmer Should Know About 3D Graphics" by Morgan McGuire
  - Used in: Player positioning, collision detection, texture mapping
  - Relevant code: `src/utils/ft_angle_utils.c`, `src/render/ft_paint.c`

- **Texture Mapping**: Fast texture filtering and perspective-correct mapping
  - Used in: Wall rendering and color blending
  - Relevant code: `src/ft_mix_color.c`, `src/ft_scale_t_image.c`

### Libraries & Frameworks

- **MiniLibX** (minilibx-linux): Simple graphics library for X11
  - GitHub: https://github.com/42Paris/minilibx-linux
  - Documentation: Included in `minilibx-linux/man/`
  - Used for: Window management, image rendering, event handling

- **libft**: 42 School's custom C utility library
  - Functions used: Memory allocation, string manipulation, list operations
  - Location: `42_Libft/` directory
  - Documentation: `42_Libft/README.md`

### Performance Optimization

- **Precalculation Techniques**: Precomputed sine/cosine tables and image scaling
  - Files: `src/ft_sin_cos.c`, `src/ft_scale_t_image_precalc.c`
  
- **Memory Management**: HD_Alloc custom allocator for efficient resource handling
  - Location: `42_Libft/HD_alloc/`

### Related References

- **Wolfenstein 3D**: Classic raycasting game that inspired the project
- **Game Loop Architecture**: Event-driven rendering with delta-time calculations
  - Reference file: `src/ft_get_time.c`, `src/ft_update.c`

- **Collision Detection**: Point-in-polygon testing for player-wall interactions
  - Implementation: `src/parse/ft_walls_closed.c`, game collision handling in controls

- **Coordinate Systems**: Converting between world space, screen space, and texture space
  - Mathematical operations: `src/utils/ft_angle_utils.c`

### Debugging & Testing

- **Map Validation**: The parser validates map structure, texture availability, and player spawn position
  - Files: `src/parse/ft_check_map.c`, `src/parse/ft_check_args.c`

- **Debug Visualization**: Optional debug textures and map overlay features
  - Location: `src/DEBUG/ft_debug_textures.c`

### 42 Specific Resources

- **42 Intra**: Official project guidelines and requirements
- **Norm Rules**: Code style compliance (`make norm` for checking)
- **Peer Evaluation**: Mandatory in 42 curriculum

## Additional Technical Information

### Project Structure

```
cub3D/
├── src/                 # Standard version source files
│   ├── parse/          # Map and config file parsing
│   ├── raycast/        # Raycasting algorithm implementation
│   ├── render/         # Rendering pipeline
│   └── game/           # Game logic and controls
├── src_bonus/          # Bonus version with extra features
├── includes/           # Header files
├── 42_Libft/           # Custom C standard library
├── minilibx-linux/     # Graphics library
├── maps/               # Example map files (.cub format)
├── textures/           # XPM texture files
└── Makefile            # Build configuration
```

### Performance Notes

- The rendering system is optimized for real-time gameplay on standard Linux systems
- Resolution can be configured at compile-time or runtime (bonus version)
- Frame rate depends on raycasting resolution and system performance
- Recommended minimum screen resolution: 1280x720

### Compilation Flags

- `-Wall -Wextra -Werror`: Strict compilation to catch potential issues
- All warnings must be resolved for successful build
- Math library linked with `-lm` for trigonometric functions
