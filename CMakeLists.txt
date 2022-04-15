cmake_minimum_required(VERSION 3.10)

# Set the build to debug mode
set(CMAKE_BUILD_TYPE "Debug")

# Set compiler
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

# Executable directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)

project(Minecraft)

# Use C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Directories to search for libraries
link_directories(C:/Users/ramen/Clibrary/public)
link_directories(C:/Users/ramen/Clibrary/public/OpenGL/lib)
link_directories(C:/Users/ramen/Clibrary/public/SFML/lib/shared)

add_executable(main
./src/camera.cpp
./src/chunk.cpp
./src/game.cpp
./src/glerror.cpp
./src/glmath.cpp
./src/lighting.cpp
./src/main.cpp
./src/renderer.cpp
./src/shader.cpp
./src/sound.cpp
./src/sounddata.cpp
./src/texture.cpp
./src/window.cpp)


# Compiler flags
target_compile_options(main PRIVATE 
-fdiagnostics-color
-Wall
-Werror
-Wpedantic
-fstrict-enums
-fsanitize=leak
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
-Winvalid-pch
-Wlogical-op
-Wdisabled-optimization
-Wvirtual-inheritance
-fno-exceptions
)


# Options for release build
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Running release build")
    target_compile_options(main PRIVATE
    -O3
    -ffast-math)
    target_link_options(main PUBLIC -flto -s)
endif (CMAKE_BUILD_TYPE STREQUAL "Release")

# Linker flags
target_link_options(main PUBLIC ../icons/icon.res)

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(TARGET main PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

# Include directories
target_include_directories(main PUBLIC 
"./include"
"C:/Users/ramen/Clibrary/public/OpenGL"
"C:/Users/ramen/Clibrary/public/SFML"
"C:/Users/ramen/Clibrary/public"
)


# Link libraries
target_link_libraries(main PUBLIC 
terminal
glad
glfw3
sfml-system-3
sfml-audio-3
timer)




