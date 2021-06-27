# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("jfGL")

if((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR (CMAKE_CXX_COMPILER_ID MATCHES "GNU"))
    add_compile_options(-Ofast)
    add_compile_options(-funsafe-math-optimizations)
    add_compile_options(-funroll-loops)
    message("-Ofast -funsafe-math-optimizations -funroll-loops")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/fp:fast)
    message("/fp:fast")
endif()

# Include sub-projects.
add_subdirectory ("src")