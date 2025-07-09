#include "Application.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

using namespace shyspace;

// 初始化Application的静态变量
Application *Application::mInstance = nullptr;

Application *Application::getInstance()
{
    // 如果mInstance已经实例化了，（new出来了）,就直接返回
    // 否则需要先new出来，再反悔
    if (mInstance == nullptr)
    {
        mInstance = new Application();
    }
    return mInstance;
}

Application::Application()
{
}
Application::~Application()
{
}

bool Application::init(const int &width, const int &height)
{
    mWidth = width;
    mHeight = height;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGLLearn", NULL, NULL);
    if (mWindow == NULL)
        return false;

    glfwMakeContextCurrent(mWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);

    glfwSetKeyCallback(mWindow, keyCallback);
    // this就是当前全局唯一的Application对象
    glfwSetWindowUserPointer(mWindow, this);

    return true;
}
void Application::frameBufferSizeCallback(GLFWwindow *window, int width, int height)
{
    Application *self = (Application *)glfwGetWindowUserPointer(window);
    if (self->mResizeCallback != nullptr)
    {
        self->mResizeCallback(width, height);
    }
}
void Application::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Application *self = (Application *)glfwGetWindowUserPointer(window);
    if (self->mKeyBoardCallback != nullptr)
    {
        self->mKeyBoardCallback(key, action, mods);
    }
}

bool Application::update()
{
    if (glfwWindowShouldClose(mWindow))
    {
        return false;
    }
    glfwPollEvents();
    glfwSwapBuffers(mWindow);
    return true;
}
void Application::destroy()
{
    glfwTerminate();
}