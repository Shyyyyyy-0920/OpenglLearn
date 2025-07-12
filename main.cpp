#include <iostream>
#include <string>
#include <assert.h>
#include "glFramework/Shader.h"
#include "glFramework/core.h"

#include "wrapper/checkError.h"
#include "application/Application.h"

GLuint vao;
Shader *shader = nullptr;
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void keyCallBack(GLFWwindow *window, int key, int scancode, int action, int modes)
{
}

void OnResize(int width, int height)
{
    GL_CALL(glViewport(0, 0, width, height));
    std::cout << "text" << std::endl;
}
void OnKey(int key, int action, int mods)
{
    std::cout << "key: " << key << std::endl;
}

void prepareVBO()
{
    GLuint vbo = 0;
    GL_CALL(glGenBuffers(1, &vbo));

    GL_CALL(glDeleteBuffers(1, &vbo));

    GLuint vboAry[] = {0, 0, 0};
    GL_CALL(glGenBuffers(3, vboAry));

    GL_CALL(glDeleteBuffers(3, vboAry));
}

void prepareVAO()
{
    float positions[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    float colors[] =
        {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f};

    unsigned int indices[] =
        {
            0, 1, 2};

    GLuint posvbo = 0;
    GL_CALL(glGenBuffers(1, &posvbo));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posvbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

    GLuint colorvbo = 0;
    GL_CALL(glGenBuffers(1, &colorvbo));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorvbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));

    GLuint ebo = 0;
    GL_CALL(glGenBuffers(1, &ebo));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    GL_CALL(glGenVertexArrays(1, &vao));
    GL_CALL(glBindVertexArray(vao));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posvbo));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorvbo));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr));

    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));

    GL_CALL(glBindVertexArray(0));
}

void prepareSingleBuffer()
{
    float positions[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.8f, 0.8f, 0.0f,
        0.8f, 0.0f, 0.0f};
    float colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f};
    GLuint posvbo = 0;
    GL_CALL(glGenBuffers(1, &posvbo));
    GLuint colorvbo = 0;
    GL_CALL(glGenBuffers(1, &colorvbo));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posvbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorvbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, posvbo); // 只有绑定了posvbp，下面的属性描述才会与vbo相关
    glEnableVertexAttribArray(0);          // 先激活0号位
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, colorvbo);
    glEnableVertexAttribArray(1); // 再激活1 号位
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    glBindVertexArray(0);
}

void prepareShader()
{
    shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

void render()
{
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
    shader->begin();
    GL_CALL(glBindVertexArray(vao));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    shader->end();
}

int main()
{
    if (!shyspace::app->init(800, 600))
    {
        return -1;
    }
    shyspace::app->setResizeCallback(OnResize);
    shyspace::app->setKeyBoardCallback(OnKey);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    GL_CALL(glViewport(0, 0, 800, 600));
    GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

    // prepareSingleBuffer();
    prepareShader();
    prepareVAO();

    // glfwSetKeyCallback(window, keyCallBack);
    while (shyspace::app->update())
    {
        render();
    }
    shyspace::app->destroy();
    return 0;
}