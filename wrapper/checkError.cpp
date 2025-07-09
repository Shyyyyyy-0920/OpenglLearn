#include "checkError.h"

void checkError()
{
    GLenum errorCode = glGetError();
    std::string errorstring = "";
    if (errorCode != GL_NO_ERROR)
    {
        switch (errorCode)
        {
        case GL_INVALID_ENUM:
            errorstring = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            errorstring = "INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            errorstring = "INVALID_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            errorstring = "OUT_OF_MEMORY";
            break;
        default:
            errorstring = "UNKNOWN_ERROR";
            break;
        }
        std::cout << errorstring << std::endl;
        assert(false);
    }
}