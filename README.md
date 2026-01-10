# Student Registration System

A comprehensive **C++ student course registration system** with priority-based waitlist management and a modern graphical user interface.

## Overview

This system allows educational institutions to manage student course registrations efficiently. It features an intelligent priority waitlist system that automatically enrolls students when seats become available, prioritizing by academic level (Senior > Junior > Sophomore > Freshman).

## Features

- âœ… **Student Management**: Add and manage students with unique IDs, names, and academic levels
- âœ… **Course Management**: Create courses with specified capacities
- âœ… **Smart Enrollment**: Automatic enrollment when seats are available
- âœ… **Priority Waitlist**: Automatic waitlist management with priority-based queuing
  - Priority order: Senior > Junior > Sophomore > Freshman
  - FIFO (First-In-First-Out) tie-breaking within the same level
- âœ… **Auto-Enrollment**: When a student drops a course, the next eligible student from the waitlist is automatically enrolled
- âœ… **Dual Interface**: Both CLI and GUI applications available
  - **CLI Demo** (waitlist_demo): Command-line interface for testing and automation
  - **GUI App** (waitlist_gui): Modern graphical interface built with Dear ImGui

## Project Structure

`
student-registration/
â”œâ”€â”€ StudentRegistrationSystem/       # Main project directory
â”‚   â”œâ”€â”€ include/                     # Header files
â”‚   â”‚   â”œâ”€â”€ RegistrationSystem.h    # Main registration system class
â”‚   â”‚   â””â”€â”€ WaitlistPQ.h            # Priority queue waitlist implementation
â”‚   â”œâ”€â”€ src/                         # Source files
â”‚   â”‚   â”œâ”€â”€ RegistrationSystem.cpp
â”‚   â”‚   â””â”€â”€ WaitlistPQ.cpp
â”‚   â”œâ”€â”€ tests/                       # Unit tests
â”‚   â”‚   â””â”€â”€ test_waitlistpq.cpp
â”‚   â”œâ”€â”€ main.cpp                     # CLI demo application
â”‚   â”œâ”€â”€ gui_main.cpp                 # GUI application (Dear ImGui)
â”‚   â”œâ”€â”€ CMakeLists.txt               # CMake build configuration
â”‚   â””â”€â”€ README.md                    # Detailed build instructions
â”œâ”€â”€ README.md                        # This file
â””â”€â”€ RUNNING_ON_DIFFERENT_OS.md      # OS-specific setup instructions
`

## Requirements

### Build Requirements
- **C++17** compatible compiler (GCC, Clang, or MSVC)
- **CMake** 3.16 or higher
- **Make** or **Ninja** (build system)

### GUI Requirements (Optional)
- **GLFW 3.x** (for windowing)
- **OpenGL** (for rendering)
- **Threads** library

### Operating Systems Supported
- âœ… Linux (Ubuntu/Debian, Fedora)
- âœ… macOS (with Homebrew)
- âœ… Windows (Visual Studio or MSYS2/MinGW)

## Quick Start

### 1. Clone the Repository

`bash
git clone https://github.com/z0hra321/student-registration.git
cd student-registration
`

### 2. Build the Project

From the repository root:

`bash
cmake -S StudentRegistrationSystem -B build
cmake --build build -j
`

### 3. Run the Applications

**CLI Demo:**
`bash
./build/waitlist_demo      # Linux/macOS
.\build\Release\waitlist_demo.exe  # Windows (Release)
`

**GUI Application:**
`bash
./build/waitlist_gui       # Linux/macOS
.\build\Release\waitlist_gui.exe   # Windows (Release)
`

**Run Tests:**
`bash
./build/test_waitlistpq    # Linux/macOS
.\build\Release\test_waitlistpq.exe  # Windows (Release)
`

## Detailed Setup Instructions

For platform-specific installation and build instructions, see:
- **[Running on Different OS](RUNNING_ON_DIFFERENT_OS.md)** - Complete guide for Windows, macOS, and Linux

## How It Works

### Waitlist Priority System

The system uses a priority queue (min-heap) to manage waitlists:

1. **Priority Calculation**: Based on academic level
   - Senior: Priority 1 (highest)
   - Junior: Priority 2
   - Sophomore: Priority 3
   - Freshman: Priority 4 (lowest)

2. **Tie-Breaking**: When multiple students have the same level, the earliest enrollment request gets priority (FIFO).

3. **Auto-Enrollment**: When a seat becomes available:
   - The highest priority student is automatically selected
   - If multiple students have the same priority, the one who registered first is chosen
   - The system automatically enrolls them without manual intervention

### Example Flow

1. **Student Registration**: A senior student enrolls in a full course
   - They are added to the waitlist with priority 1

2. **Course Drop**: A freshman student drops the course
   - The senior student (priority 1) is automatically enrolled
   - If no seniors, the highest priority available student is enrolled

## Usage Examples

### CLI Demo

The CLI application provides an interactive interface for:
- Adding students and courses
- Enrolling students in courses
- Dropping courses (triggers auto-enrollment from waitlist)
- Viewing course enrollment status and waitlist

### GUI Application

The GUI provides a user-friendly interface with:
- Visual representation of students and courses
- Real-time enrollment status
- Waitlist visualization
- Easy management of registrations

## Testing

The project includes unit tests for the waitlist priority queue:

`bash
./build/test_waitlistpq
`

These tests verify:
- Priority ordering (Senior > Junior > Sophomore > Freshman)
- FIFO tie-breaking within the same level
- Correct heap operations

## Build Options

You can customize the build with CMake options:

`bash
# Disable GUI build
cmake -S StudentRegistrationSystem -B build -DBUILD_GUI=OFF

# Disable tests
cmake -S StudentRegistrationSystem -B build -DBUILD_TESTS=OFF
`

## Technical Details

### Architecture

- **WaitlistPQ**: Custom priority queue implementation using a min-heap
- **RegistrationSystem**: High-level system managing students, courses, and enrollments
- **Dear ImGui**: Immediate-mode GUI library for the graphical interface
- **CMake**: Cross-platform build system for easy compilation

### Data Structures

- **Heap-based Priority Queue**: Efficient O(log n) insertion and O(log n) removal
- **Hash Maps**: Fast lookup for students and courses by ID
- **Vectors**: Dynamic arrays for enrollment lists

## Troubleshooting

### GUI doesn't build
- **Linux**: Install GLFW: sudo apt install libglfw3-dev (Ubuntu/Debian) or sudo dnf install glfw-devel (Fedora)
- **macOS**: Install via Homebrew: rew install glfw
- **Windows**: Use vcpkg: cpkg install glfw3, or configure with -DBUILD_GUI=OFF to skip GUI

### Build errors
- Ensure C++17 support is enabled
- Check that CMake 3.16+ is installed
- Verify all dependencies are installed (see [RUNNING_ON_DIFFERENT_OS.md](RUNNING_ON_DIFFERENT_OS.md))

### Headless environment
- Use the CLI demo (waitlist_demo) instead of the GUI
- The GUI requires a display/GPU context

## Contributing

Contributions are welcome! Please ensure your code follows the existing style and includes appropriate tests.

## License

This project uses the Dear ImGui library (MIT License) for the GUI. See StudentRegistrationSystem/third_party/imgui/LICENSE.txt for details.

## Author

**z0hra321**

---

For detailed platform-specific instructions, please refer to [RUNNING_ON_DIFFERENT_OS.md](RUNNING_ON_DIFFERENT_OS.md).
