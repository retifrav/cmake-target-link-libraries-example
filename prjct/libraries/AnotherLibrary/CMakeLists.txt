cmake_minimum_required(VERSION 3.22)

project(
    "AnotherLibrary"
    VERSION ${CMAKE_PROJECT_VERSION}
    DESCRIPTION "Another library"
)

set(THINGY_LINKING "PRIVATE" CACHE STRING "How Thingy library was linked in AnotherLibrary")

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        src/another.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

find_package(Thingy CONFIG REQUIRED)

# first set the target property
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        THINGY_LINKING_VARIANT ${THINGY_LINKING}
)
# and then make it available for other projects when they import this target
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        EXPORT_PROPERTIES THINGY_LINKING_VARIANT
)

if(THINGY_LINKING STREQUAL PRIVATE)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            dpndnc::Thingy
    )
elseif(THINGY_LINKING STREQUAL PUBLIC)
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
            dpndnc::Thingy
    )
else() # that will take any value, defaulting to INTERFACE
    target_link_libraries(${PROJECT_NAME}
        INTERFACE
            dpndnc::Thingy
    )
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
            THINGY_INTERFACE
    )
endif()

# without it public headers won't get installed
set(public_headers
    include/another.h
)

# to guard against against undefined BUILD_SHARED_LIBS inside Config.cmake.in,
# because without that check you will get a malformed condition
# when this variable is undefined (which it is by default)
set(BUILD_SHARED_LIBS_VALUE 0)
if(DEFINED BUILD_SHARED_LIBS AND BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS_VALUE 1)
endif()
include(Installing)
