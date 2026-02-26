# Space Invaders

An OpenGL-powered C++ remake of the 1978 arcade classic **Space Invaders**.

![Space Invaders](https://github.com/Seank23/Space_Invaders/assets/10364911/b86c50d6-23a8-432b-90ac-44dfd33eeba3)

## Overview

This repository contains a desktop game built with:

- **C++20**
- **OpenGL** for rendering
- **GLFW + GLAD** for windowing/context/input
- **GLM** for math
- **stb_image** and **spdlog** as supporting libraries
- A custom lightweight game/audio architecture in `Space_Invaders/src`

The project is currently configured for **Windows + Visual Studio 2022** via **Premake** and ships with Visual Studio solution/project files already generated.

## Features

- Classic Space Invaders gameplay loop (waves, score, lives, shields, game over/reset)
- Player movement and shooting with cooldown
- Alien swarm movement, projectiles, and collision handling
- Bonus alien ship events
- Procedural retro-style synthesized audio for gameplay effects and background notes
- On-screen HUD text (score, high-score, lives, credits)

## Repository Structure

```text
.
├── premake5.lua                    # Build configuration (workspace/projects/configs)
├── Space_Invaders.sln              # Visual Studio solution (generated)
├── scripts/
│   └── GenerateProjects.bat        # Regenerate VS project files with Premake
└── Space_Invaders/
    ├── src/
    │   ├── Engine/                 # Rendering, shaders, buffers, sprite systems, timing
    │   ├── Game/                   # Game objects, state management, logic, audio handler
    │   ├── Application.*           # App lifecycle + main entry point
    │   └── Log.* / pch.*
    ├── res/
    │   └── shaders/Basic.shader
    └── vendor/
        ├── GLFW/
        ├── glad/
        ├── glm/
        ├── spdlog/
        └── stb_image/
```

## Prerequisites (Development)

To build from source on Windows:

1. **Visual Studio 2022** with C++ desktop workload
2. **Windows 10/11 SDK**
3. (If regenerating projects) bundled Premake binary at:
   - `vendor/bin/premake/premake5.exe`

> The project uses `PlatformToolset v143`, `x64`, and OpenGL via `opengl32.lib`.

## Build and Run

### Option A: Use existing solution

1. Open `Space_Invaders.sln` in Visual Studio 2022.
2. Select configuration:
   - `Debug | x64`
   - `Release | x64`
   - `Dist | x64`
3. Build the solution.
4. Run `Space_Invaders` as startup project.

### Option B: Regenerate solution with Premake

From repository root:

```bat
cd scripts
GenerateProjects.bat
```

Then open the regenerated `Space_Invaders.sln` and build as above.

### Build Output

Executables are emitted to:

```text
bin/<Configuration>-windows-x86_64/Space_Invaders/Space_Invaders.exe
```

Examples:

- `bin/Debug-windows-x86_64/Space_Invaders/Space_Invaders.exe`
- `bin/Release-windows-x86_64/Space_Invaders/Space_Invaders.exe`

## Controls

| Action | Keys |
|---|---|
| Move left | `A` or `Left Arrow` |
| Move right | `D` or `Right Arrow` |
| Shoot | `Space` or `Up Arrow` |
| Decrease volume | `-` |
| Increase volume | `=` |
| Quit | `Esc` |

## Gameplay Notes

- You start with multiple lives and defensive shields.
- Destroying aliens increases score.
- High score is tracked during runtime.
- The game ends if aliens reach the ground or the player loses all lives.
- After game over, a new round is automatically initialized.

## Release Usage (No Build)

If you only want to play:

1. Download the latest release from the [Releases page](https://github.com/Seank23/Space_Invaders/releases).
2. Extract the archive.
3. Run `Space_Invaders.exe`.

## Technical Notes

- Window/input loop is driven by GLFW in `Application`.
- Projection uses a fixed 2D orthographic game space.
- Game logic is coordinated by `Game` and `GameStateManager`.
- Audio clips are synthesized procedurally in `AudioHandler` (no external sound assets required).

## Troubleshooting

- **Project won’t open/build**: verify Visual Studio 2022 C++ toolchain + Windows SDK are installed.
- **Project files out of sync**: rerun `scripts/GenerateProjects.bat`.
- **Black screen or GL init issues**: ensure your graphics driver supports OpenGL and that required DLLs from build output are present.
- **No audio output**: confirm a valid output audio device is available/enabled on the system.

## License

This project is licensed under the terms of the **GNU GPLv3** license.
