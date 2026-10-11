# Run Chicken

## Game Summary

**Run Chicken** is a 2D pixel-art endless runner/platformer created with C++, OpenGL, and FreeGLUT. The player controls a chicken that automatically runs through a barnyard environment while avoiding fences, hay obstacles, pits, and flying birds.

The player can jump and double-jump, collect golden eggs, and earn a chick companion after every five eggs. Chicks act as additional protection: when the chicken or a chick is hit by an obstacle, one chick can be lost before the run ends. The game gradually increases its running speed to make the level more challenging.

The game also includes:

- An animated barn opening sequence
- Scrolling mountains, trees, clouds, and water
- Animated chicken wings, running legs, chicks, and birds
- Procedurally generated obstacle and platform patterns
- Score, egg, speed, and best-score HUD displays
- Start, pause, and game-over screens
- Interactive pixel-art wooden plank buttons
- Fullscreen display with keyboard and mouse controls

## Controls

- **Space / W**: Start the run from the start screen or jump during gameplay
- **P**: Pause or resume the game
- **R**: Restart the game
- **Escape**: Exit the game
- **Left mouse button**: Select menu buttons or jump from the lower-left gameplay area

## Requirements

- Windows
- C++17-compatible MinGW compiler
- OpenGL and GLU libraries
- FreeGLUT
- GLEW

The project includes the runtime DLL files required by the compiled executable. The build script searches for the bundled project toolchain first and falls back to the MSYS2 MinGW installation at `C:\msys64\mingw32`.

## Compilation

The script compiles `RunChicken.cpp`, links the OpenGL, FreeGLUT, GLEW, Windows multimedia, and graphics libraries, and places the resulting executable in the `CS0045_MIDTERM_EBRON` folder. It also copies matching runtime DLL files beside the executable when they are available in the selected toolchain.

## Running the Game

After compilation, run the executable from the project root:

```powershell
.\CS0045_MIDTERM_EBRON\RunChicken.exe
```

The game opens in fullscreen mode. Click **PLAY** or press **Space** to begin. During the opening transition, repeated Space or W presses are ignored so the animation can finish smoothly.

## Visual and Technical Notes

The game uses reusable OpenGL drawing functions for rectangles, triangles, circles, gradients, and pixel text. Game objects such as platforms, obstacles, eggs, birds, and chicks are stored in vectors so they can be generated, updated, and removed dynamically. A timer updates physics, scrolling, collisions, score progression, and animation before requesting the next frame.
