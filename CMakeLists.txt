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


add_executable(main
./src/camera.cpp
./src/chunk.cpp
./src/frustum.cpp
./src/game.cpp
./src/glerror.cpp
./src/glmath.cpp
./src/main.cpp
./src/perlin.cpp
./src/renderer.cpp
./src/worldgen.cpp
./src/shader.cpp
./src/sound.cpp
./src/texture.cpp
./src/window.cpp)


# Compiler flags
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(main PRIVATE 
    -fdiagnostics-color
    -Wall
    -Werror
    -Wpedantic
    -Wextra
    -ffunction-sections
    -fdata-sections
    #-fsanitize=address
    -fstrict-enums
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
    -Wold-style-cast
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
    -Wno-unused-function
    -fno-exceptions
    )


    # Options for release build
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        message(STATUS "Running release build")
        target_compile_options(main PRIVATE
        -DNDEBUG
        -O3
        -ffast-math
        -flto
        -fprofile-generate=./profile # This executes the binary a few times for sample analysis (Replace with "fprofile-use=PATH" once complete)
        -fprofile-partial-training
        -march=native)
        target_link_options(main PUBLIC -flto -s)
        target_link_libraries(main PUBLIC gcov)
    endif (CMAKE_BUILD_TYPE STREQUAL "Release")

endif()
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(main PRIVATE
    -fdiagnostics-color
    -Wextra-tokens
    -Wall
    -Wextra
    -Wpedantic
    -Wabstract-final-class
    -Wbad-function-cast
    -Wbitfield-enum-conversion
    -Wcast-align
    -Wcast-qual
    -Wcomma
    -Wdate-time
    -Wdelete-non-virtual-dtor
    -Wdelimited-escape-sequence-extension
    -Wdeprecated
    -Wdouble-promotion
    -Wduplicate-decl-specifier
    -Wembedded-directive
    -Wempty-translation-unit
    -Wenum-conversion
    -Wfloat-conversion
    -Wfloat-equal
    -Wfloat-overflow-conversion
    -Wgcc-compat
    -Wgnu
    -Wheader-hygiene
    -Wimplicit
    -Wkeyword-macro
    -Wlanguage-extension-token
    -Wmethod-signatures
    -Wmicrosoft
    -Wold-style-cast
    -Wover-aligned
    -Woverloaded-virtual
    -Wpragmas
    -Wretained-language-linkage
    -Wself-move
    -Wshadow-all
    -Wshift-sign-overflow
    -Wsuggest-override
    -Wsuggest-destructor-override
    -Wsuper-class-method-mismatch
    -Wthread-safety
    -Wundefined-internal-type
    -Wunneeded-internal-declaration
    -Wunneeded-member-function
    -Wunreachable-code-aggressive
    -Wunused
    -Wvector-conversion
    )
endif()

# Include directories
target_include_directories(main PUBLIC "./include")
target_link_directories(main PUBLIC "./lib")

# Link libraries
if (WIN32)

    # Linker flags
    target_link_options(main PUBLIC ../icons/icon.res -Wl,--gc-sections)

    target_link_libraries(main PUBLIC 
    glfw3
    sfml-system-3
    sfml-audio-3
    timer)
elseif(UNIX)
    target_link_libraries(main PUBLIC
    glad
    glfw
    sfml-system
    sfml-audio
    timer
    )
endif()

