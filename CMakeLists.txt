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
link_directories("./lib")

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
-Wextra
-ffunction-sections
-fdata-sections
-fstrict-enums
-fsanitize=leak
-Wctor-dtor-privacy
-Wnon-virtual-dtor
-Wmismatched-tags
-Wextra-semi
-Wsuggest-final-types
-Wsuggest-final-methods
-Wsuggest-override
-Wuseless-cast
-Wdouble-promotion
-Wimplicit-fallthrough
-Wmissing-include-dirs
-Wformat=2
#-Wconversion
-Wduplicated-branches
-Wduplicated-cond
-Wshadow
-Wfloat-equal
-Wcast-qual
-Wcast-align
-Wnull-dereference
-Winvalid-pch
-Winline
-Wunsafe-loop-optimizations
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
    -ffast-math
    -flto
    -fprofile-generate=./profile # This executes the binary a few times for sample analysis (Replace with "fprofile-use=PATH" once complete)
    -fprofile-partial-training
    -march=native)
    target_link_options(main PUBLIC -flto -s)
    target_link_libraries(main PUBLIC gcov)
endif (CMAKE_BUILD_TYPE STREQUAL "Release")

# Linker flags
target_link_options(main PUBLIC ../icons/icon.res -Wl,--gc-sections)

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(TARGET main PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

# Include directories
target_include_directories(main PUBLIC "./include")


# Link libraries
target_link_libraries(main PUBLIC 
glad
glfw3
sfml-system-3
sfml-audio-3
timer)




