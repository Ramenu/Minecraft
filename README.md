Classic v1.31:
- Made error handling slightly better:
  * Have red text whenever a fatal error occurs (Currently Windows only)
  * Moved error handling function into a new file "glerror.cpp", granted some errors do not belong to OpenGL but I don't think its a big deal at the moment

- Window file has namespace for better organization and clarity
- Switched from using traditional integers to type aliases for better portability

