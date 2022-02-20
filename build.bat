:: This script compiles and links the C++ files into
:: an executable. If the '-all' parameter is given, it
:: will compile and link all of the .cpp files present
:: in the ./src directory. Otherwise, it will only compile
:: and link up to the number of files given as arguments.

@echo off
setlocal enabledelayedexpansion

set argCount=0

:: Insert arguments into array
for %%x in (%*) do (
    set /A argCount+=1
    set "argVec[!argCount!]=%%~x"
)

:: Append string with all the arguments
for /l %%a in (1,1,%argCount%) do call set "files=%%files%% !argVec[%%a]!"

set pathtodir=C:/Users/ramen/Projects/Minecraft/

:: Compiles all of the files in the ./src directory
if "%1" == "-all" (
    timer.bat ccache g++ -fdiagnostics-color=always -g -Wall -Werror -Wextra -Wpedantic -fstrict-enums -std=c++17 -Wctor-dtor-privacy ^
    -Wmismatched-tags -Wextra-semi -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -Wuseless-cast -Wdouble-promotion ^
    -Wimplicit-fallthrough -Wmissing-include-dirs -Wduplicated-cond -Wshadow -Wcast-qual -Wdangling-else -Winvalid-pch ^
    -Wlogical-op -Wno-aggressive-loop-optimizations -Wdisabled-optimization ^
    -IC:/Users/ramen/Projects/Minecraft/include ^
    -IC:/Users/ramen/Clibrary ^
    %pathtodir%src/main.cpp ^
    %pathtodir%src/game.cpp ^
    %pathtodir%src/window.cpp ^
    %pathtodir%src/shader.cpp ^
    %pathtodir%src/texture.cpp ^
    %pathtodir%src/camera.cpp ^
    %pathtodir%src/attribute.cpp ^
    %pathtodir%src/buffer.cpp ^
    %pathtodir%src/block.cpp ^
    %pathtodir%src/subtexture.cpp ^
    %pathtodir%src/renderer.cpp ^
    %pathtodir%src/lighting.cpp ^
    %pathtodir%src/ray.cpp ^
    %pathtodir%src/glmath.cpp ^
    %pathtodir%src/material.cpp ^
    %pathtodir%src/glerror.cpp ^
    -c 
    mv %pathtodir%/*.o %pathtodir%/obj>NUL 2>&1 
    g++ -flinker-output=exec %pathtodir%/obj/*.o -o main.exe ^
    C:/Users/ramen/Clibrary/public/libterminal.a C:/Users/ramen/Clibrary/public/OpenGL/lib/*.a ^
    %pathtodir%icons/icon.res
) else (

    if "%files%" == "" (
        echo Please pass a name of one or more files as arguments.
    ) else (
        timer.bat g++ -g -Wall -Werror -Wextra -Wpedantic -fstrict-enums -std=c++17 -I./include -IC:/Users/ramen/Clibrary -Wctor-dtor-privacy ^
        -Wmismatched-tags -Wextra-semi -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -Wuseless-cast -Wdouble-promotion ^
        -Wimplicit-fallthrough -Wmissing-include-dirs -Wduplicated-cond -Wshadow -Wcast-qual -Wdangling-else -Winvalid-pch ^
        -Wlogical-op -Wno-aggressive-loop-optimizations -Wdisabled-optimization ^
        %files:~1% -c 
        mv %pathtodir%.o ./obj>NUL 2>&1
        g++ ./obj/*.o -o main.exe C:/Users/ramen/Clibrary/public/libterminal.a C:/Users/ramen/Clibrary/public/OpenGL/lib/*.a ^
        C:/Users/ramen/Projects/Minecraft/icons/icon.res
    )
)