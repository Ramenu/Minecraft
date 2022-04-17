#include "minecraft/glerror/glerror.hpp"
#include "glad/glad.h"
#include <iostream>
extern "C" 
{
    #include "misc/color.h"
}

namespace GLError
{
    /**
     * Prints an error message to stderr before
     * terminating the program. This function
     * should only be called if the program 
     * cannot recover from the error in any way.
     */
    void error_message(std::string_view error) noexcept
    {
        std::cerr << COLOR_RED << "\nFATAL ERROR: " << COLOR_RESET << error << '\n';
        exit(EXIT_FAILURE);
    }

    #ifdef MC_DEBUG_BUILD
        /**
         * Callback function for debugging OpenGL.
         */
        void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, 
                                    GLsizei, const char *message, const void *){

            // ignore non-significant error/warning codes
            switch (id)
            {
                case 131169: return;
                case 131185: return;
                case 131218: return;
                case 131204: return;
            }

            std::cerr << "---------------\nDebug message (" << id << "): " <<  message << '\n';

            switch (source)
            {
                case GL_DEBUG_SOURCE_API:             std::cerr << "Source: API\n"; break;
                case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cerr << "Source: Window System\n"; break;
                case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cerr << "Source: Shader Compiler\n"; break;
                case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cerr << "Source: Third Party\n"; break;
                case GL_DEBUG_SOURCE_APPLICATION:     std::cerr << "Source: Application\n"; break;
                case GL_DEBUG_SOURCE_OTHER:           std::cerr << "Source: Other\n"; break;
            } 

            switch (type)
            {
                case GL_DEBUG_TYPE_ERROR:               std::cerr << "Type: Error\n"; break;
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cerr << "Type: Deprecated Behaviour\n"; break;
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cerr << "Type: Undefined Behaviour\n"; break; 
                case GL_DEBUG_TYPE_PORTABILITY:         std::cerr << "Type: Portability\n"; break;
                case GL_DEBUG_TYPE_PERFORMANCE:         std::cerr << "Type: Performance\n"; break;
                case GL_DEBUG_TYPE_MARKER:              std::cerr << "Type: Marker\n"; break;
                case GL_DEBUG_TYPE_PUSH_GROUP:          std::cerr << "Type: Push Group\n"; break;
                case GL_DEBUG_TYPE_POP_GROUP:           std::cerr << "Type: Pop Group\n"; break;
                case GL_DEBUG_TYPE_OTHER:               std::cerr << "Type: Other\n"; break;
            } 
            
            switch (severity)
            {
                case GL_DEBUG_SEVERITY_HIGH:         std::cerr << "Severity: HIGH\n\n"; break;
                case GL_DEBUG_SEVERITY_MEDIUM:       std::cerr << "Severity: MEDIUM\n\n"; break;
                case GL_DEBUG_SEVERITY_LOW:          std::cerr << "Severity: LOW\n\n"; break;
                case GL_DEBUG_SEVERITY_NOTIFICATION: std::cerr << "Severity: NOTIFICATION\n\n"; break;
            } 
        }

        /**
        * Enables OpenGL's debugging output.
        */
        void enableGLDebugCallBack()
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(glDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }
    #endif
} 