cmake_minimum_required(VERSION 3.10)

# Launch compiler with ccache
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

# Set compiler
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

# Executable directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)

project(Minecraft)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Directories to search for libraries
link_directories(C:/Users/ramen/Clibrary/public C:/Users/ramen/Clibrary/public/OpenGL/lib)

add_executable(main
./src/attribute.cpp
./src/block.cpp
./src/buffer.cpp
./src/camera.cpp
./src/game.cpp
./src/glerror.cpp
./src/glmath.cpp
./src/lighting.cpp
./src/main.cpp
./src/material.cpp
./src/ray.cpp
./src/renderer.cpp
./src/shader.cpp
./src/subtexture.cpp
./src/texture.cpp
./src/vertices.cpp
./src/window.cpp)


# Compiler flags
target_compile_options(main PRIVATE 
-fdiagnostics-color
-g
-Wall
-Werror
-Wpedantic
-fstrict-enums
-Wctor-dtor-privacy
-Wmismatched-tags
-Wextra-semi
-Wsuggest-final-types
-Wsuggest-final-methods
-Wsuggest-override
-Wuseless-cast
-Wdouble-promotion
-Wimplicit-fallthrough
-Wmissing-include-dirs
-Wduplicated-cond
-Wshadow
-Wcast-qual
-Wdangling-else
-Winvalid-pch
-Wlogical-op
-Wno-aggressive-loop-optimizations
-Wdisabled-optimization
-fexceptions)

# Linker flags
target_link_options(main PUBLIC ../icons/icon.res)

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(TARGET main PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

# Include directories
target_include_directories(main PUBLIC "./include")
target_include_directories(main PUBLIC "C:/Users/ramen/Clibrary/public/OpenGL")
target_include_directories(main PUBLIC "C:/Users/ramen/Clibrary")


# Link libraries
target_link_libraries(main PUBLIC terminal)
target_link_libraries(main PUBLIC glad)
target_link_libraries(main PUBLIC glfw3)
target_link_libraries(main PUBLIC gdi32)



