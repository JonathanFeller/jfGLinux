# CMakeList.txt : CMake project for jfGL, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
file (GLOB source_files "*.h" "*.cpp")
add_executable (${PROJECT_NAME} ${source_files})

# TODO: Add tests and install targets if needed.
if((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR (CMAKE_CXX_COMPILER_ID MATCHES "GNU"))
    find_package(X11 REQUIRED)
    message(STATUS "X11_FOUND = ${X11_FOUND}")
    message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
    message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")
    include_directories(${X11_INCLUDE_DIR})
    link_directories(${X11_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})
endif()

target_compile_options (${PROJECT_NAME} PRIVATE -Wno-narrowing)