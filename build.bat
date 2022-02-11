@echo off
setlocal enabledelayedexpansion

if "%1" == "-all" (
    timer.bat g++ -fdiagnostics-color -g -Wall -std=c++17  -I./include -IC:/Users/ramen/Clibrary ^
    ./src/main.cpp ./src/ray.cpp ./src/renderer.cpp ./src/shader.cpp ./src/subtexture.cpp ^
    ./src/texture.cpp ./src/window.cpp ./src/lighting.cpp ./src/glmath.cpp ./src/game.cpp ^
    ./src/camera.cpp ./src/buffer.cpp ./src/block.cpp ./src/attribute.cpp ./src/material.cpp -c 
    move ./*.o ./obj>NUL 2>&1
    g++ ./obj/*.o -o main.exe C:/Users/ramen/Clibrary/public/OpenGL/lib/*.a ^
    ./icons/icon.res
) else (
    set argCount=0
    for %%x in (%*) do (
    set /A argCount+=1
    set "argVec[!argCount!]=%%~x"
    )

    for /l %%a in (1,1,%argCount%) do call set "files=%%files%% !argVec[%%a]!"

    if "%files%" == "" (
        echo Please pass a name of one or more files as arguments.
    ) else (
        timer.bat g++ -g -Wall -std=c++17 -I./include -IC:/Users/ramen/Clibrary ^
        %files:~1% -c 
        move *.o ./obj>NUL 2>&1
        g++ ./obj/*.o -o main.exe C:/Users/ramen/Clibrary/public/OpenGL/lib/*.a ^
        ${workspaceFolder}/icons/icon.res
    )
)