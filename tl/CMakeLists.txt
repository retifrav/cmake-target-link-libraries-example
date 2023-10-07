cmake_minimum_required(VERSION 3.22)

project(
    "some-tool"
    DESCRIPTION "A CLI tool that does something"
    VERSION 0.9.2
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

# where to find our CMake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# global debug postfix for libraries (executables still need to set it)
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Filename postfix for libraries under DEBUG configuration")

# ---

# not a great way to do this, as there is no control over setting more than one option
# option(THINGY_PRIVATE   "The Thingy dependency is linked as PRIVATE"   0)
# option(THINGY_INTERFACE "The Thingy dependency is linked as INTERFACE" 0)
# option(THINGY_PUBLIC    "The Thingy dependency is linked as PUBLIC"    0)
#
# message(STATUS "THINGY PRIVATE/INTERFACE/PUBLIC: ${THINGY_PRIVATE}/${THINGY_INTERFACE}/${THINGY_PUBLIC}")
#
# if(NOT THINGY_PRIVATE AND NOT THINGY_INTERFACE AND NOT THINGY_PUBLIC)
#     message(FATAL_ERROR "You need to set the THINGY option")
# endif()

# this is better than several options, but still not ideal,
# as it is much better to get this value from imported target property (see below)
#set(THINGY_LINKING "PRIVATE" CACHE STRING "How Thingy library was linked in AnotherLibrary")

# ---

# here it's a top-level project, so CMAKE_PROJECT_NAME is fine
add_executable(${CMAKE_PROJECT_NAME})

set_target_properties(${CMAKE_PROJECT_NAME}
    PROPERTIES
        DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
        src/main.cpp
)

find_package(SomeLibrary CONFIG REQUIRED)
find_package(AnotherLibrary CONFIG REQUIRED)

# ---

# that would be for when options are used
# target_compile_definitions(${CMAKE_PROJECT_NAME}
#     PRIVATE
#         $<$<BOOL:${THINGY_PRIVATE}>:THINGY_PRIVATE>
#         $<$<BOOL:${THINGY_INTERFACE}>:THINGY_INTERFACE>
#         $<$<BOOL:${THINGY_PUBLIC}>:THINGY_PUBLIC>
# )

# the way of linking is available in the imported target property
get_target_property(THINGY_LINKING prjct::AnotherLibrary THINGY_LINKING_VARIANT)
message(STATUS "AnotherLibrary linking to Thingy: ${THINGY_LINKING}")

# and this one works for both cache variable and imported target property
target_compile_definitions(${CMAKE_PROJECT_NAME}
    PRIVATE
        $<$<STREQUAL:${THINGY_LINKING},PRIVATE>:THINGY_PRIVATE>
        $<$<STREQUAL:${THINGY_LINKING},INTERFACE>:THINGY_INTERFACE>
        $<$<STREQUAL:${THINGY_LINKING},PUBLIC>:THINGY_PUBLIC>
)

# ---

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        prjct::SomeLibrary
        prjct::AnotherLibrary
)

include(Installing)
