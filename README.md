# Student Registration System

A production-ready **C++17** course registration system designed for educational institutions, featuring an intelligent priority-based waitlist mechanism and dual-interface support (CLI and GUI) for comprehensive course enrollment management.

---

## Table of Contents

- [Overview](#overview)
- [Key Features](#key-features)
- [Project Architecture](#project-architecture)
- [System Requirements](#system-requirements)
- [Installation and Setup](#installation-and-setup)
- [Algorithm Design](#algorithm-design)
- [Time Complexity Analysis](#time-complexity-analysis)
- [Usage Guide](#usage-guide)
- [Testing and Validation](#testing-and-validation)
- [Build Configuration](#build-configuration)
- [Implementation Details](#implementation-details)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [License](#license)
- [Author Information](#author-information)

---

## Overview

The Student Registration System is a high-performance course enrollment management solution that automates the registration process for educational institutions. The system implements a sophisticated priority queue algorithm that ensures fair course allocation based on academic standing, with automatic enrollment processing when course capacity becomes available.

**Primary Objectives:**
- Streamline student course registration workflows
- Implement fair, priority-based waitlist management
- Provide real-time enrollment status tracking
- Support both programmatic (CLI) and interactive (GUI) interfaces

---

## Key Features

### Core Functionality

**Student Management Module**
- Create and maintain student records with unique identifiers
- Store academic level classifications (Senior, Junior, Sophomore, Freshman)
- Support efficient student lookup and enumeration operations

**Course Management Module**
- Define courses with configurable capacity limits
- Track enrollment statistics and availability in real-time
- Maintain comprehensive course catalogs

**Enrollment Processing**
- **Direct Enrollment**: Immediate registration when course capacity is available
- **Intelligent Waitlisting**: Automatic placement on priority queue when courses are full
- **Auto-Enrollment**: Seamless automatic promotion from waitlist when seats open

**Priority Waitlist System**
- **Level-Based Priority**: Senior (1) > Junior (2) > Sophomore (3) > Freshman (4)
- **FIFO Tie-Breaking**: First-come-first-served within the same academic level
- **Real-Time Processing**: Immediate waitlist updates upon course drops

**Dual Interface Support**
- **Command-Line Interface (CLI)**: `waitlist_demo` executable for automation and testing
- **Graphical User Interface (GUI)**: `waitlist_gui` application built with Dear ImGui for interactive management

---

## Project Architecture

This section outlines the organizational structure of the codebase and the relationships between components.

```
student-registration/
├── StudentRegistrationSystem/           # Core application directory
│   ├── include/                         # Public interface headers
│   │   ├── RegistrationSystem.h        # Main system controller class
│   │   └── WaitlistPQ.h                # Priority queue data structure interface
│   ├── src/                            # Implementation source files
│   │   ├── RegistrationSystem.cpp      # Business logic implementation
│   │   └── WaitlistPQ.cpp              # Heap-based priority queue implementation
│   ├── tests/                          # Unit and integration tests
│   │   └── test_waitlistpq.cpp        # Waitlist priority queue test suite
│   ├── main.cpp                        # CLI application entry point
│   ├── gui_main.cpp                    # GUI application entry point (Dear ImGui)
│   ├── CMakeLists.txt                  # CMake build configuration
│   └── README.md                       # Detailed build and development documentation
├── README.md                           # Project documentation (this file)
└── RUNNING_ON_DIFFERENT_OS.md         # Platform-specific installation guide
```

**Component Relationships:**
- `RegistrationSystem` utilizes `WaitlistPQ` for managing course waitlists
- Both CLI and GUI applications depend on the `RegistrationSystem` class
- Test suite validates the correctness of the priority queue implementation

---

## System Requirements

### Compiler and Build Tools

**Minimum Requirements:**
- **C++ Standard**: C++17 or later
- **Compiler**: GCC 7+, Clang 5+, or MSVC 2017+ with C++17 support
- **Build System**: CMake 3.16 or higher
- **Build Generator**: Make or Ninja

### GUI Dependencies (Optional)

The graphical interface requires the following libraries:

- **GLFW 3.x**: Cross-platform windowing library for window creation and input handling
- **OpenGL**: Graphics rendering API (typically provided by the system)
- **Threading Library**: POSIX threads (pthread) or Windows threads

### Platform Support

**Officially Supported Operating Systems:**
- **Linux**: Ubuntu 18.04+, Debian 10+, Fedora 30+
- **macOS**: macOS 10.13+ (High Sierra or later) with Xcode Command Line Tools
- **Windows**: Windows 10+ with Visual Studio 2017+ or MSYS2/MinGW-w64

### Installation Prerequisites

**Linux (Ubuntu/Debian):**
```bash
sudo apt update
sudo apt install -y build-essential cmake pkg-config libglfw3-dev libgl1-mesa-dev
```

**Linux (Fedora):**
```bash
sudo dnf install -y gcc-c++ cmake pkgconf-pkg-config glfw-devel mesa-libGL-devel
```

**macOS:**
```bash
xcode-select --install
brew install cmake glfw
```

**Windows (vcpkg):**
```powershell
vcpkg install glfw3
```

For detailed platform-specific instructions, refer to [RUNNING_ON_DIFFERENT_OS.md](RUNNING_ON_DIFFERENT_OS.md).

---

## Installation and Setup

### Step 1: Repository Cloning

Clone the repository to your local development environment:

```bash
git clone https://github.com/z0hra321/student-registration.git
cd student-registration
```

### Step 2: Build Configuration

Configure the build system using CMake from the repository root:

```bash
cmake -S StudentRegistrationSystem -B build
```

This command generates build files in the `build/` directory using the configuration specified in `StudentRegistrationSystem/CMakeLists.txt`.

### Step 3: Compilation

Build all targets using parallel compilation:

```bash
cmake --build build -j
```

The `-j` flag enables parallel compilation for faster build times. Omit this flag for single-threaded builds.

### Step 4: Execution

After successful compilation, executables are located in the `build/` directory:

**CLI Application:**
```bash
./build/waitlist_demo              # Linux/macOS
.\build\Release\waitlist_demo.exe  # Windows (Release configuration)
```

**GUI Application:**
```bash
./build/waitlist_gui               # Linux/macOS
.\build\Release\waitlist_gui.exe   # Windows (Release configuration)
```

**Test Suite:**
```bash
./build/test_waitlistpq            # Linux/macOS
.\build\Release\test_waitlistpq.exe # Windows (Release configuration)
```

---

## Algorithm Design

### Waitlist Priority Queue Implementation

The system employs a **min-heap** (binary heap) data structure to implement the priority queue, ensuring efficient insertion and extraction of the highest-priority student entries.

**Priority Calculation:**
- Academic level determines primary priority (lower numeric value = higher priority)
  - Senior: Priority 1
  - Junior: Priority 2
  - Sophomore: Priority 3
  - Freshman: Priority 4

**Tie-Breaking Mechanism:**
- When multiple students share the same academic level priority, the system uses **First-In-First-Out (FIFO)** ordering
- Each waitlist entry is timestamped upon insertion to maintain chronological order
- The student with the earliest timestamp receives priority among peers at the same level

**Heap Operations:**
- **Heapify Up**: Restores heap property after insertion by bubbling up the new element
- **Heapify Down**: Restores heap property after extraction by percolating down the root element

### Enrollment Workflow

**Enrollment Process:**
1. Validate student and course existence
2. Check current enrollment status
3. If course has available capacity:
   - Add student to enrolled list (O(k) where k = current enrollment count)
   - Return success
4. If course is at capacity:
   - Add student to waitlist using priority queue (O(log n))
   - Return waitlist confirmation

**Drop and Auto-Enrollment Process:**
1. Validate student enrollment in the specified course
2. Remove student from enrolled list
3. Check waitlist status
4. If waitlist contains entries:
   - Extract highest-priority student (O(log n))
   - Automatically enroll extracted student (O(1))
   - Update enrollment and waitlist status

---

## Time Complexity Analysis

This section provides a comprehensive analysis of the computational complexity for all major operations in the system.

### Waitlist Priority Queue Operations

| Operation | Time Complexity | Space Complexity | Description |
|-----------|----------------|------------------|-------------|
| `addToWaitlist()` | **O(log n)** | O(1) | Insert student entry and maintain heap property |
| `removeFromWaitlist()` | **O(log n)** | O(1) | Extract minimum-priority entry and restore heap |
| `autoEnroll()` | **O(log n)** | O(1) | Wrapper for `removeFromWaitlist()` |
| `isEmpty()` | **O(1)** | O(1) | Check if waitlist is empty |
| `size()` | **O(1)** | O(1) | Return current waitlist size |

Where **n** is the number of students in the waitlist.

**Rationale:** Heap insertion and extraction require traversing the tree height, which is O(log n) for a balanced binary heap containing n elements.

### Registration System Operations

| Operation | Time Complexity | Space Complexity | Description |
|-----------|----------------|------------------|-------------|
| `addStudent()` | **O(1)** average, O(n) worst | O(1) | Insert student into hash map |
| `getStudent()` | **O(1)** average, O(n) worst | O(1) | Hash map lookup by student ID |
| `listStudents()` | **O(n)** | O(n) | Enumerate all students |
| `addCourse()` | **O(1)** average, O(m) worst | O(1) | Insert course into hash map |
| `getCourse()` | **O(1)** average, O(m) worst | O(1) | Hash map lookup by course code |
| `listCourses()` | **O(m)** | O(m) | Enumerate all courses |
| `enroll()` | **O(k + log n)** worst | O(1) | Enroll student or add to waitlist |
| `drop()` | **O(k + log n)** worst | O(1) | Remove enrollment and process auto-enrollment |
| `coursesOfStudent()` | **O(m · k)** | O(m) | Find all courses for a student |

Where:
- **n** = number of students in the waitlist
- **m** = number of courses in the system
- **k** = number of enrolled students in a course

**Detailed Analysis:**

- **Hash Map Operations**: `std::unordered_map` provides O(1) average-case lookup and insertion. Worst-case O(n) occurs only with hash collisions, which are rare with good hash functions.
- **Enrollment Check**: `vecContains()` performs linear search through enrolled list, O(k) in worst case.
- **Enrollment Removal**: `vecRemove()` requires finding and erasing element, O(k) in worst case.
- **Waitlist Operations**: Priority queue operations are O(log n), where n is the waitlist size.
- **Student Course Query**: `coursesOfStudent()` iterates through all courses and checks enrollment lists, resulting in O(m · k) complexity.

### Overall System Performance

**Best Case Scenarios:**
- Enrollment when course has capacity: **O(1)** - Direct hash map lookup and vector append
- Course drop with empty waitlist: **O(k)** - Linear search and removal from enrollment list

**Worst Case Scenarios:**
- Enrollment to full course: **O(k + log n)** - Check enrollment + waitlist insertion
- Course drop with auto-enrollment: **O(k + log n)** - Remove enrollment + waitlist extraction + new enrollment

**Space Complexity:**
- Overall: **O(n + m · k)** where n = students, m = courses, k = average enrolled students per course
- Waitlist storage: **O(n)** for priority queue
- Course enrollment lists: **O(m · k)** total

---

## Usage Guide

### Command-Line Interface

The CLI application (`waitlist_demo`) provides an interactive terminal-based interface for system administration and testing.

**Available Operations:**
- **Student Management**: Add new students, query student information, list all students
- **Course Management**: Create courses, view course details, list course catalog
- **Enrollment Operations**: Enroll students in courses, drop course registrations
- **Status Queries**: Check enrollment counts, waitlist sizes, student course schedules

**Example Workflow:**
```bash
./build/waitlist_demo
# Follow interactive prompts to:
# 1. Add students with their academic levels
# 2. Create courses with capacity limits
# 3. Enroll students and observe waitlist behavior
# 4. Drop enrollments to trigger auto-enrollment
```

### Graphical User Interface

The GUI application (`waitlist_gui`) offers a modern, intuitive interface built with Dear ImGui for real-time system management.

**GUI Features:**
- **Dashboard View**: Overview of students, courses, and enrollment statistics
- **Interactive Forms**: Add students and courses through form inputs
- **Visual Status Indicators**: Color-coded enrollment status and waitlist information
- **Real-Time Updates**: Dynamic refresh of enrollment data
- **Waitlist Visualization**: Display of priority queue contents and ordering

**Launch Instructions:**
```bash
./build/waitlist_gui
# GUI window opens automatically
# Use interface controls to manage the registration system
```

---

## Testing and Validation

### Unit Test Suite

The project includes comprehensive unit tests for the priority queue implementation located in `tests/test_waitlistpq.cpp`.

**Test Coverage:**

1. **Priority Ordering Verification**
   - Validates correct ordering: Senior > Junior > Sophomore > Freshman
   - Ensures students with higher academic levels receive enrollment priority

2. **FIFO Tie-Breaking Validation**
   - Confirms chronological ordering within the same academic level
   - Verifies timestamp-based tie-breaking mechanism

3. **Heap Property Maintenance**
   - Tests heap structure integrity after insertions
   - Validates heap property preservation after extractions

4. **Edge Case Handling**
   - Empty waitlist operations
   - Single-element waitlist behavior
   - Concurrent insertion and extraction scenarios

### Running Tests

Execute the test suite to verify system correctness:

```bash
./build/test_waitlistpq
```

Expected output includes pass/fail indicators for each test case, with detailed diagnostic information for any failures.

### Manual Testing Recommendations

1. **Enrollment Testing**: Verify direct enrollment and waitlist placement
2. **Auto-Enrollment Testing**: Confirm correct student promotion when seats become available
3. **Priority Validation**: Test priority ordering with mixed academic levels
4. **Tie-Breaking Verification**: Validate FIFO behavior with same-level students
5. **Error Handling**: Test system response to invalid inputs and edge cases

---

## Build Configuration

### CMake Build Options

Customize the build process using CMake configuration options:

**Disable GUI Build:**
```bash
cmake -S StudentRegistrationSystem -B build -DBUILD_GUI=OFF
cmake --build build -j
```

This option is useful for headless server environments or when GUI dependencies are unavailable.

**Disable Test Compilation:**
```bash
cmake -S StudentRegistrationSystem -B build -DBUILD_TESTS=OFF
cmake --build build -j
```

Exclude test executables from the build for production deployments.

**Combined Options:**
```bash
cmake -S StudentRegistrationSystem -B build -DBUILD_GUI=OFF -DBUILD_TESTS=OFF
```

### Build Profiles

**Debug Configuration:**
```bash
cmake -S StudentRegistrationSystem -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
```

Includes debug symbols and disables optimizations for development and debugging.

**Release Configuration (Default on Windows):**
```bash
cmake -S StudentRegistrationSystem -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j --config Release
```

Enables compiler optimizations for production performance.

---

## Implementation Details

### Data Structure Selection

**Priority Queue: Min-Heap**
- **Justification**: Logarithmic insertion and extraction provide optimal performance for dynamic waitlist management
- **Implementation**: Array-based binary heap using `std::vector` for efficient memory usage
- **Advantages**: O(log n) operations, O(1) space overhead, cache-friendly structure

**Student and Course Storage: Hash Map**
- **Data Structure**: `std::unordered_map` for O(1) average-case lookup
- **Key Design**: Student ID and course code serve as unique hash keys
- **Performance**: Constant-time access essential for frequent enrollment queries

**Enrollment Lists: Dynamic Arrays**
- **Data Structure**: `std::vector<std::string>` for student ID storage
- **Trade-offs**: O(k) linear search acceptable for typical course sizes (k < 100)
- **Optimization**: Reserve capacity to minimize reallocations

### Design Patterns and Principles

**Separation of Concerns:**
- `WaitlistPQ`: Focused solely on priority queue operations
- `RegistrationSystem`: High-level business logic and state management
- GUI/CLI: Presentation layer separated from core functionality

**Encapsulation:**
- Private heap operations (heapifyUp, heapifyDown) hidden from external access
- Public interface provides only necessary operations for system integration

**Extensibility:**
- Modular design allows easy addition of new features (e.g., course prerequisites, enrollment limits per student)
- Abstracted waitlist implementation enables alternative priority schemes

### Performance Optimizations

1. **Reserve Vector Capacity**: Pre-allocate memory for student and course lists to reduce reallocations
2. **Move Semantics**: Use move constructors to minimize string copying in Entry creation
3. **Hash Map Efficiency**: Leverage fast hash-based lookups instead of linear searches
4. **In-Place Heap Operations**: Minimize temporary object creation during heap restructuring

---

## Troubleshooting

### Common Build Issues

**Issue: GUI Build Fails - GLFW Not Found**

**Linux Solution:**
```bash
# Ubuntu/Debian
sudo apt install libglfw3-dev libgl1-mesa-dev

# Fedora
sudo dnf install glfw-devel mesa-libGL-devel
```

**macOS Solution:**
```bash
brew install glfw
```

**Windows Solution:**
```powershell
vcpkg install glfw3
# Configure CMake with vcpkg toolchain:
cmake -S StudentRegistrationSystem -B build -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
```

**Workaround:** Build without GUI:
```bash
cmake -S StudentRegistrationSystem -B build -DBUILD_GUI=OFF
```

---

**Issue: C++17 Features Not Recognized**

**Solution:** Ensure compiler supports C++17:
- GCC: Version 7.0 or higher
- Clang: Version 5.0 or higher
- MSVC: Visual Studio 2017 or higher

Verify compiler version:
```bash
g++ --version
clang++ --version
```

---

**Issue: Build Errors - Missing Dependencies**

**Solution:** Verify all system dependencies are installed (see [System Requirements](#system-requirements)).

Check CMake configuration output for missing package indicators.

---

### Runtime Issues

**Issue: GUI Application Doesn't Launch**

**Possible Causes:**
- Missing display server (Linux headless environment)
- GPU drivers not properly configured
- GLFW initialization failure

**Solution:**
- Use CLI application in headless environments: `./build/waitlist_demo`
- Verify OpenGL support: `glxinfo | grep "OpenGL version"` (Linux)
- Check GUI dependencies are correctly installed

---

**Issue: Segmentation Fault or Crash**

**Debugging Steps:**
1. Rebuild with debug symbols:
   ```bash
   cmake -S StudentRegistrationSystem -B build -DCMAKE_BUILD_TYPE=Debug
   cmake --build build -j
   ```
2. Run with debugger (GDB/LLDB):
   ```bash
   gdb ./build/waitlist_demo
   ```
3. Check for null pointer dereferences or out-of-bounds access
4. Verify input validation (empty strings, invalid IDs)

---

**Issue: Incorrect Waitlist Ordering**

**Verification:**
1. Run unit tests: `./build/test_waitlistpq`
2. Check academic level assignments (Senior=1, Junior=2, etc.)
3. Verify timestamp generation in `addToWaitlist()` function
4. Inspect heap property maintenance in heapify operations

---

### Performance Concerns

**Issue: Slow Enrollment Operations**

**Optimization Strategies:**
- For courses with large enrollment lists (k > 100), consider using `std::unordered_set` instead of `std::vector` for O(1) lookup
- Pre-reserve vector capacity based on expected course sizes
- Profile code to identify specific bottlenecks

---

## Contributing

We welcome contributions to improve the Student Registration System! Please follow these guidelines:

### Development Workflow

1. **Fork the Repository**: Create your own fork for development
2. **Create Feature Branch**: Use descriptive branch names (e.g., `feature/add-prerequisites`)
3. **Follow Code Style**: Maintain consistent formatting and naming conventions
4. **Write Tests**: Include unit tests for new functionality
5. **Update Documentation**: Keep README and code comments current
6. **Submit Pull Request**: Provide clear description of changes

### Code Standards

- **C++17 Standards**: Use modern C++ features appropriately
- **Naming Conventions**: camelCase for variables, PascalCase for classes
- **Comments**: Document complex algorithms and non-obvious logic
- **Error Handling**: Validate inputs and provide meaningful error messages

### Testing Requirements

- All new features must include corresponding unit tests
- Ensure existing tests continue to pass
- Test edge cases and error conditions

---

## License

This project utilizes the **Dear ImGui** library, which is licensed under the **MIT License**.

**Dear ImGui License:**
- Copyright (c) 2014-2023 Omar Cornut and ImGui contributors
- Full license text available at: `StudentRegistrationSystem/third_party/imgui/LICENSE.txt`

**Project License:**
This codebase is provided for educational and development purposes. Please review license terms for specific usage requirements.

---

## Author Information

**Developer:** z0hra321

**Repository:** [https://github.com/z0hra321/student-registration](https://github.com/z0hra321/student-registration)

**Contact:** For questions, issues, or contributions, please use the GitHub issue tracker.

---

## Additional Resources

- **Platform-Specific Setup**: [RUNNING_ON_DIFFERENT_OS.md](RUNNING_ON_DIFFERENT_OS.md) - Detailed installation instructions for Windows, macOS, and Linux
- **Project README**: `StudentRegistrationSystem/README.md` - In-depth build and development documentation
- **Dear ImGui Documentation**: [https://github.com/ocornut/imgui](https://github.com/ocornut/imgui) - GUI library documentation and examples

---

**Last Updated:** See git commit history for latest changes and modifications.
