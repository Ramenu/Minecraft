
CLASSIC V2.63
------------
- Added CMake support for GNU/Linux systems, although you'll have to make a lib directory and put all of the libraries in there. Currently the CMakeLists.txt is a mess, but for the release build I will be sure to get a portable build system running
- Changed license to GPL
- Fixed a Linux-exclusive segfault, apparently OpenGL functions cannot be called after GLFW has been terminated. Not sure why this isn't the case on Windows? 
- Use the release version of SFML libraries instead of the latest 

Sidenote: I have noticed that the program runs slower on GNU/Linux but I'm not sure why. Here are my best guesses:<br>
1) GCC's stdlib is less efficient than MinGW GCC's stdlib (highly doubt it, I would assume that they are mostly the same)<br>
2) GCC does not compile code as efficiently as MinGW's GCC (highly doubt this)<br>
3) External programs being run by the kernel slow the system down as compared to Windows (highly doubt this)<br>
4) The compiled libraries are not optimized for Linux as compared to Windows (I could see this being true for GLAD, but I am still skeptical)<br>
5) Something to do with the drivers (this seems more probable)<br>
6) A combination of a few or all of these reasons<br>

Regardless, I will try my best to have this issue fixed at some point.<br>

Some links to the libraries I use, they are really great, go check them out:<br>
https://www.glfw.org/ (Window and event handling library)<br>
https://github.com/Dav1dde/glad (Provides OpenGL loader generator, and more.)<br>
https://github.com/SFML/SFML (I use it for audio, but they support graphics, networks, and a whole lot of other stuff)<br>
https://github.com/kthohr/gcem (Compile-time math library)<br>
https://github.com/nothings/stb (For image processing)<br>

I'm also using other tools to help make the code look cleaner, and hopefully 'safer'. Hope you find them interesting:
https://github.com/danmar/cppcheck<br>
https://clang.llvm.org/extra/clang-tidy/<br>
https://drmemory.org/index.html<br>
https://valgrind.org<br>

The SFX does not belong to me, and is used for private purposes by me only. When the game is released,
I will add my own SFX.

HOW TO BUILD:
-------------

> Coming soon...



