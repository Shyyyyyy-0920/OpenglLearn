#include <string>
#include <assert.h>
#include <glad/glad.h>
#include <iostream>
#ifdef DEBUG
#define GL_CALL(func) \
    func;             \
    checkError();
#else
#define GL_CALL(func)
#endif
void checkError();
