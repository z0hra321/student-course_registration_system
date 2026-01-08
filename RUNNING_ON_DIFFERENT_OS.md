## Running on Different Operating Systems

This project uses **CMake** and **C++17** and provides:
- `waitlist_demo` (CLI)
- `waitlist_gui` (GUI: Dear ImGui + GLFW + OpenGL)
- `test_waitlistpq` (simple test executable)

### Common build steps (all OS)
From the repo root:

```bash
cmake -S StudentRegistrationSystem -B build
cmake --build build -j
```

### Linux (Ubuntu/Debian)
Install dependencies:

```bash
sudo apt update
sudo apt install -y build-essential cmake pkg-config libglfw3-dev libgl1-mesa-dev
```

Build + run:

```bash
cmake -S StudentRegistrationSystem -B build
cmake --build build -j
./build/waitlist_demo
./build/waitlist_gui
./build/test_waitlistpq
```

### Linux (Fedora)

```bash
sudo dnf install -y gcc-c++ cmake pkgconf-pkg-config glfw-devel mesa-libGL-devel
cmake -S StudentRegistrationSystem -B build
cmake --build build -j
./build/waitlist_gui
```

### macOS (Homebrew)
Install:

```bash
xcode-select --install
brew install cmake glfw
```

Build + run:

```bash
cmake -S StudentRegistrationSystem -B build
cmake --build build -j
./build/waitlist_gui
```

### Windows
You have two common options.

#### Option A: Visual Studio + vcpkg (recommended)
1) Install Visual Studio (Desktop development with C++)  
2) Install vcpkg and then:

```powershell
vcpkg install glfw3
```

3) Configure + build (replace the toolchain path with your vcpkg path):

```powershell
cmake -S StudentRegistrationSystem -B build -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
```

Run:

```powershell
.\build\Release\waitlist_demo.exe
.\build\Release\waitlist_gui.exe
.\build\Release\test_waitlistpq.exe
```

#### Option B: MSYS2 (MinGW)
1) Install MSYS2  
2) In the **MSYS2 MinGW 64-bit** shell:

```bash
pacman -S --noconfirm mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake mingw-w64-x86_64-glfw
cmake -S StudentRegistrationSystem -B build
cmake --build build -j
./build/waitlist_gui.exe
```

### Troubleshooting
- **GUI doesn’t build (GLFW not found)**: install GLFW (Linux: `libglfw3-dev`, macOS: `brew glfw`, Windows: `vcpkg glfw3`) or configure with:

```bash
cmake -S StudentRegistrationSystem -B build -DBUILD_GUI=OFF
```

- **Running in a headless environment**: the GUI needs a working display / GPU context. Use the CLI demo (`waitlist_demo`) on headless servers.


