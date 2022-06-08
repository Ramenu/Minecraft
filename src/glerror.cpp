#include "minecraft/glerror/glerror.hpp"
#include "glad/glad.h"
#include <iostream>
#include "misc/color.h"

namespace GLError
{
    /**
     * Prints an error message to stderr before
     * terminating the program. This function
     * should only be called if the program 
     * cannot recover from the error in any way.
     */
    void error_message(std::string_view error) noexcept // cppcheck-suppress passedByValue
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

            std::cout << "---------------\nDebug message (" << id << "): " <<  message << '\n';

            switch (source)
            {
                case GL_DEBUG_SOURCE_API:             std::cout << "Source: API\n"; break;
                case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System\n"; break;
                case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler\n"; break;
                case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party\n"; break;
                case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application\n"; break;
                case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other\n"; break;
            } 

            switch (type)
            {
                case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error\n"; break;
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour\n"; break;
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour\n"; break; 
                case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability\n"; break;
                case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance\n"; break;
                case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker\n"; break;
                case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group\n"; break;
                case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group\n"; break;
                case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other\n"; break;
            } 
            
            switch (severity)
            {
                case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: HIGH\n\n"; break;
                case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: MEDIUM\n\n"; break;
                case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: LOW\n\n"; break;
                case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: NOTIFICATION\n\n"; break;
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