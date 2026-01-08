cmake_minimum_required(VERSION 3.16)
project(StudentRegistrationSystem CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_GUI "Build the Dear ImGui GUI application" ON)
option(BUILD_TESTS "Build simple test executables" ON)

# Core waitlist library
add_library(waitlistpq
  src/WaitlistPQ.cpp
)

target_include_directories(waitlistpq
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(registration_core
  src/RegistrationSystem.cpp
)
target_include_directories(registration_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(registration_core PUBLIC waitlistpq)

# Dear ImGui (vendored)
add_library(imgui
  third_party/imgui/imgui.cpp
  third_party/imgui/imgui_demo.cpp
  third_party/imgui/imgui_draw.cpp
  third_party/imgui/imgui_tables.cpp
  third_party/imgui/imgui_widgets.cpp
  third_party/imgui/backends/imgui_impl_glfw.cpp
  third_party/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui/backends
)

# Demo/driver for WaitlistPQ (this repo contains it)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
  add_executable(waitlist_demo main.cpp)
  target_link_libraries(waitlist_demo PRIVATE waitlistpq)
endif()

# GUI app (Dear ImGui)
if(BUILD_GUI AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/gui_main.cpp")
  find_package(Threads REQUIRED)
  find_package(OpenGL REQUIRED)

  # GLFW (prefer config package; fallback to pkg-config / find_library)
  set(_glfw_target "")
  find_package(glfw3 CONFIG QUIET)
  if(TARGET glfw)
    set(_glfw_target glfw)
  elseif(TARGET glfw3::glfw)
    set(_glfw_target glfw3::glfw)
  endif()

  if(NOT _glfw_target)
    find_package(PkgConfig QUIET)
    if(PKG_CONFIG_FOUND)
      pkg_check_modules(GLFW QUIET glfw3)
      if(GLFW_FOUND)
        add_library(glfw_pkg INTERFACE)
        target_include_directories(glfw_pkg INTERFACE ${GLFW_INCLUDE_DIRS})
        target_link_directories(glfw_pkg INTERFACE ${GLFW_LIBRARY_DIRS})
        target_link_libraries(glfw_pkg INTERFACE ${GLFW_LIBRARIES})
        set(_glfw_target glfw_pkg)
      endif()
    endif()
  endif()

  if(NOT _glfw_target)
    find_library(GLFW_LIBRARY NAMES glfw3 glfw)
    if(GLFW_LIBRARY)
      add_library(glfw_lib UNKNOWN IMPORTED)
      set_target_properties(glfw_lib PROPERTIES IMPORTED_LOCATION "${GLFW_LIBRARY}")
      set(_glfw_target glfw_lib)
    endif()
  endif()

  if(NOT _glfw_target)
    message(FATAL_ERROR "GLFW was not found. Install it (e.g. libglfw3-dev / brew glfw / vcpkg glfw3) or configure with -DBUILD_GUI=OFF.")
  endif()

  add_executable(waitlist_gui gui_main.cpp)
  target_link_libraries(waitlist_gui PRIVATE registration_core imgui ${_glfw_target} OpenGL::GL Threads::Threads ${CMAKE_DL_LIBS})
endif()

# Optional unit test (simple executable; no test framework assumed)
if(BUILD_TESTS AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_waitlistpq.cpp")
  add_executable(test_waitlistpq tests/test_waitlistpq.cpp)
  target_link_libraries(test_waitlistpq PRIVATE waitlistpq)
endif()


