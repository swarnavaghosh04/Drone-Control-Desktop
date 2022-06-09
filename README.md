Dependencies required to be seperately installed:
- SDL2

Build Dependencies:
- CMake

Depencies automatically handled by CMake:
- ImGui

Build Process:
```
mkdir build && cd build
cmake ..
cmake --build .
cmake --install . --prefix <path_to_install_location>
```