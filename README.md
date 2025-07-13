# Retro Launcher - 80/90s-Style Menu for Single Board Computers

A 90s-style launcher for Single Board Computers, designed to run directly in the console (no X11). Compatible with keyboard and USB/SNES controllers.

## Features
At this moment is just a prototype, so milestones are:

- **Retro look** (pixel art, VGA colors, DOS fonts).
- **Navigation** with keyboard/SNES controller.
- **Options**:
    - TODO (configurable)

## Requirements
- Raspberry Pi 4 (or similar SBC).
- SDL 1.2 and SDL_ttf installed.
- Monitor/TV compatible with low resolutions (at this moment it's prepared for 640x480).

## Installation
```bash
# Install dependencies
sudo apt-get install libsdl1.2-dev libsdl-ttf2.0-dev cmake joystick

# Clone and build
git clone https://github.com/bitstuffing/retro_menu.git
cd retro_menu
mkdir build && cd build
cmake .. && make

# Run (from console)
./build/retro_menu
```

## License
Fonts are downloaded from [here](https://www.dafont.com), so it has his license in the original page.
Code is released under GPLv3 by @bitstuffing with love. 