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
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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
./src/window.cpp)

link_directories(C:/Users/ramen/Clibrary/public)
link_directories(C:/Users/ramen/Clibrary/OpenGL/lib)

# Compile options
target_compile_options(main PRIVATE 
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

# Linker options
target_link_options(main PUBLIC
-LC:/Users/ramen/Clibrary/public/OpenGL/lib
-LC:/Users/ramen/Clibrary/public
../icons/icon.res
)

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



