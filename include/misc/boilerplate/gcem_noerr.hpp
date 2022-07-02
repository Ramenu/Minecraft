#ifndef MC_GCEM_NOERR_HPP
#define MC_GCEM_NOERR_HPP

#if (defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW64__)) && (!defined(__llvm__) && !defined(__INTEL_COMPILER))
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wfloat-equal"
    #include "gcem/gcem.hpp"
    #pragma GCC diagnostic pop
#else
    #include "gcem/gcem.hpp"
#endif

#endif // GCEM_NOERR_HPP