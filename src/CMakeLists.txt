# CMakeList.txt : CMake project for jfGL, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (${PROJECT_NAME}
"jfGL.cpp" "jfGL.h"
"Timing.cpp" "Timing.h"
"WindowL.cpp" "WindowL.h"
"Render.cpp" "Render.h")

# TODO: Add tests and install targets if needed.
find_package(X11 REQUIRED)
message(STATUS "X11_FOUND = ${X11_FOUND}")
message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")
include_directories(${X11_INCLUDE_DIR})
link_directories(${X11_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})

target_compile_options (${PROJECT_NAME} PRIVATE -Wno-narrowing)