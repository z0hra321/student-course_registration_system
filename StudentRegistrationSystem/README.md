## Student Registration System (C++ / CMake)

This project implements a **student course registration system** with:

- **Students**: register students with `id`, `name`, and `level` (Senior/Junior/Sophomore/Freshman)
- **Courses**: add courses with a capacity
- **Enrollment**:
  - If seats are available → enroll immediately
  - If full → add the student to a **priority waitlist**
  - When someone drops → **auto-enroll** the next student from the waitlist

### Waitlist behavior
The waitlist uses `WaitlistPQ`:
- **Priority**: Senior > Junior > Sophomore > Freshman
- **Tie-break**: FIFO within the same level

### Project layout
- **Core waitlist**: `include/WaitlistPQ.h`, `src/WaitlistPQ.cpp`
- **Registration core**: `include/RegistrationSystem.h`, `src/RegistrationSystem.cpp`
- **CLI demo**: `main.cpp` → builds `waitlist_demo`
- **GUI app (Dear ImGui)**: `gui_main.cpp` → builds `waitlist_gui`
- **Simple unit test**: `tests/test_waitlistpq.cpp` → builds `test_waitlistpq`

### Build (CMake)
From the repo root:

```bash
cmake -S StudentRegistrationSystem -B build
cmake --build build -j
```

### Run
- **CLI demo**:

```bash
./build/waitlist_demo
```

- **GUI app**:

```bash
./build/waitlist_gui
```

### Run the test

```bash
./build/test_waitlistpq
```

