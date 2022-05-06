#ifndef GLM_NOERR_HPP
#define GLM_NOERR_HPP

#if defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW64__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wduplicated-branches"
    #include "glm/glm.hpp"
    #pragma GCC diagnostic pop
#else
    #include "glm/glm.hpp"
#endif

#endif // GLM_NOERR_HPP
