Classic v1.2:
- Replaced individual textures with a texture atlas instead which should result in a considerable performance increase (at least later on)
- Mouse cannot go out of bounds of window
- Made SubTexture class to handle subtexture coordinates within the atlas
- Made Renderer class to handle all things related to rendering objects
- Blocks can now be made with an ENUM in the constructor which should make things easier for general-use
- Updated GLAD to v4.6 (latest OpenGL version) from v3.3 because there was a feature that I didn't end up implementing (because of texture
  bleeding) which required v4.0+ 

For such little progress, this update took quite some time. Most of the time, if not all, was spent trying to make the texture
optimizations, even though it wasn't necessary right now, I still wanted to get it over with. I was also contemplating whether to use
a texture atlas or a texture array. I ended up going with the former because it was easier.