cmake_minimum_required(VERSION 3.16)
project(WaitlistSystem CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/gui_main.cpp")
  add_executable(waitlist_gui gui_main.cpp)
  target_link_libraries(waitlist_gui PRIVATE registration_core imgui glfw GL dl pthread)
endif()

# Optional unit test (simple executable; no test framework assumed)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_waitlistpq.cpp")
  add_executable(test_waitlistpq tests/test_waitlistpq.cpp)
  target_link_libraries(test_waitlistpq PRIVATE waitlistpq)
endif()


