
![screenshot](./screenshots/Screenshot_2022-07-01_11-53-44.png)
![screenshot](./screenshots/Screenshot_2022-07-01_11-57-48.png)

RELEASE V1.1
------------
- Fixed slow chunk initialization on startup, chunks load all at once when the program starts up
- Fixed excessively high memory usage as more and more chunks are loaded, it is now extremely stable and lightweight!
- Optimize chunk creation
- Some minor shader tweaks


For building the program, refer to the documentation.


FEATURES
--------
- Procedurally generated world
- Up to 3 different biomes (plains, forest, desert), with each biome having its own unique terrain generation features
- Many different ore blocks can be found underground (almost all of the same ones in Minecraft)
- Destroy blocks and place them, with up to 8 different blocks that can be picked and placed
- Unique sound effects that are distinctly different from the original game
- Custom 8x8 textures made by me


TO BE RESOLVED
--------------
- Blocks are still highlighted even when the player has stopped looking at them

LIBRARIES/TOOLS/PROGRAMS USED
-----------------------------
https://www.glfw.org/ (Window and event handling library)<br>
https://github.com/Dav1dde/glad (Provides OpenGL loader generator, and more.)<br>
https://github.com/SFML/SFML (I use it for audio, but they support graphics, networks, and a whole lot of other stuff)<br>
https://github.com/kthohr/gcem (Compile-time math library)<br>
https://github.com/nothings/stb (For image processing)<br>
https://sfbgames.itch.io/chiptone (Created the sound effects using this)<br>


I'm also using other tools to help make the code look cleaner, and hopefully 'safer'. Hope you find them interesting:
https://github.com/danmar/cppcheck<br>
https://clang.llvm.org/extra/clang-tidy/<br>
https://drmemory.org/index.html<br>
https://valgrind.org<br>




