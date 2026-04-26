# Project README

## Overview
This project is a 2D Engine written in C. It provides basic functionalities for creating, updating, and deleting graphical objects on a 2D canvas.

## Features
- Creating a window with specified dimensions.
- Setting up a main loop to handle updates.
- Basic event handling (not explicitly supported in the provided code but can be added).
- Drawing simple shapes by projecting 2D coordinates.

## Project Structure

### Prerequisites
- C/C++ Compiler and Debugger (GCC, Clang)
- Make utility
- Standard development tools
- Libraries needed:
  - X11 for Linux (`libX11-dev`)
  - Winmm and GDI32 for Windows (`mingw-w64` on Linux to compile for Windows)
  - SDL2 for WebAssembly (if needed)

## Build & Run

### Building for Linux
```bash
cd <Project>
make -f Makefile.linux all
```

#### Clean and Rebuild
To clean the build directory and rebuild:
```bash
make -f Makefile.linux clean
make -f Makefile.linux all
```

### Running on Linux
After building, you can run the application with:
```bash
make -f Makefile.linux exe
```

### Building for Windows
```bash
cd <Project>
make -f Makefile.windows all
```

#### Clean and Rebuild
To clean the build directory and rebuild:
```bash
make -f Makefile.windows clean
make -f Makefile.windows all
```

### Running on Windows
After building, you can run the application with:
```bash
make -f Makefile.windows exe
```

### Building for Wine (Linux Cross Compile for Windows)
```bash
cd <Project>
make -f Makefile.wine all
```

#### Clean and Rebuild
To clean the build directory and rebuild:
```bash
make -f Makefile.wine clean
make -f Makefile.wine all
```

### Running on Wine
After building, you can run the application with:
```bash
make -f Makefile.wine exe
```

### Building for WebAssembly (Emscripten)
```bash
cd <Project>
make -f Makefile.web all
```

#### Clean and Rebuild
To clean the build directory and rebuild:
```bash
make -f Makefile.web clean
make -f Makefile.web all
```

### Running on WebAssembly
After building, you can run the application with:
```bash
make -f Makefile.web exe
```

This README provides a clear overview of the project, its features, and how to build and run it for different platforms.