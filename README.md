<!--Copyright 2022 ramen

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.-->



CLASSIC V1.9
------------
- Mainly an optimization update, there are a lot of things that have changed
- Blocks are no longer rendered individually (instead rendered 16x16x16 in one draw call). This will significantly reduce CPU work and will help later on when more chunks will have to be rendered.
- Block placing and destroying have been removed, though will be added in the next update. 


KNOWN BUGS:
- There is an annoying bug where sometimes the ray will highlight two blocks instead of one. I am planning to fix this sometime in the future.
- Camera will make weird turns 
- Pressing 'Q' may enable wireframe mode really fast, which will cause it to go off and on (may depend on hardware platform)

Some links to the libraries I use, they are really great, go check them out:<br>
https://github.com/SFML/SFML (I use it for audio, but they support graphics, networks, and a whole lot of other stuff.)

I'm also using other tools to help make the code look cleaner, and hopefully 'safer'. Hope you find them interesting:
https://github.com/danmar/cppcheck<br>
https://clang.llvm.org/extra/clang-tidy/<br>

HOW TO BUILD:
-------------

> Coming soon...



