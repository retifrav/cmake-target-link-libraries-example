cmake_minimum_required(VERSION 3.22)

set(namespace "prjct")
project(
    "some-sdk"
    DESCRIPTION "A silly SDK with a couple of libraries"
    VERSION 1.2.3
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

# where to find our CMake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# global debug postfix for libraries (executables still need to set it)
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Filename postfix for libraries under DEBUG configuration")

add_subdirectory(libraries)
