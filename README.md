# Intel 8080 Space Invaders Emulator

A Space Invaders emulator written in C++ that emulates the original Intel 8080 arcade hardware. The emulator supports full gameplay including both one-player and two-player modes, accurate CPU behavior, correct video memory decoding, and real-time input through SDL3. Audio has not yet been implemented.

## Features

- Full Intel 8080 CPU emulation
- Compatible with the original Space Invaders ROM layout
- SDL3-based rendering and input handling
- One-player and two-player gameplay support
- Correct interrupt and timing behavior
- Authentic monochrome display output

## Controls

| Action               | Key        |
|----------------------|------------|
| Insert Coin          | C          |
| Player 1 Start       | Enter      |
| Player 2 Start       | 2          |
| Player 1 Fire        | Space      |
| Player 1 Move Left   | Left Arrow |
| Player 1 Move Right  | Right Arrow|
| Player 2 Fire        | Left Shift |
| Player 2 Move Left   | A          |
| Player 2 Move Right  | D          |
| Tilt                 | T          |

## Requirements

- Visual Studio Code
- C++ compiler supporting C++20
- SDL3 (installed and linked)
- Space Invaders ROM files (not included)

## Building and Running

This project was built and run directly through Visual Studio Code using its built-in Run and Debug functionality, without CMake or external build systems.

Steps:
1. Open the project folder in Visual Studio Code
2. Ensure the C++ extension and build tools are installed (MSVC or equivalent)
3. Configure SDL3 include and library paths in the build configuration
4. Press **Run** or **Start Debugging** inside VS Code
5. Place the ROM files in the expected ROM directory and start the game

## Screenshots
<img width="338" height="407" alt="image" src="https://github.com/user-attachments/assets/67e2e9ea-71d1-49c9-a56f-8e29e7c2df27" />
<img width="338" height="407" alt="image" src="https://github.com/user-attachments/assets/0ef88ba2-5103-4362-95a5-942cb1323023" />
<img width="338" height="407" alt="image" src="https://github.com/user-attachments/assets/8743d8c4-a5b6-47d1-ae7e-a4be8f036ac9" />

## Acknowledgements

- Intel 8080 architectural documentation
- Community Test Roms

