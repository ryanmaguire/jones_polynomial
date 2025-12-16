# CMakeList.txt : CMake project for load_balanced, include source and define
# project specific logic here.
#

cmake_minimum_required(VERSION 3.12)

project(load_balanced LANGUAGES C)

if (MSVC)
    add_compile_options(/O2 /W4)
else()
    add_compile_options(-O3 -flto -Wall -Wextra -Wpedantic)
endif()

# Add source to this project's executable.
file(GLOB SRC_FILES ./*.c)
add_executable(load_balanced ${SRC_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET load_balanced PROPERTY C_STANDARD 17)
endif()

# TODO: Add tests and install targets if needed.