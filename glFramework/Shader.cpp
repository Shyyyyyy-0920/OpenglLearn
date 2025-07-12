#include "Shader.h"
#include "../wrapper/checkError.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    // 声明装入shader代码字符串的两个string
    std::string vertexCode;
    std::string fragmentCode;
    // 声明用于读取vs跟fs文件的inFileStream
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // 保证ifstream遇到问题的时候可以抛出异常
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // 打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        // 将文件输入流中的字符串输入到stringStream里面
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // 关闭文件
        vShaderFile.close();
        fShaderFile.close();
        // 将字符串从stringstream当中读取出来，转化到codestring当中
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure &e)
    {
        std::cout << "SHADER FILE ERROR: " << e.what()
                  << "\nVertex Path: " << vertexPath
                  << "\nFragment Path: " << fragmentPath << '\n';
    }

    const char *vertexShaderSource = vertexCode.c_str();
    const char *fragmentShaderSource = fragmentCode.c_str();

    GLuint vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertex, 1, &vertexShaderSource, NULL);
    glShaderSource(fragment, 1, &fragmentShaderSource, NULL);

    // int success = 0;
    // char infoLog[1024];

    glCompileShader(vertex);
    checkShaderErrors(vertex, "COMPILE");

    glCompileShader(fragment);
    checkShaderErrors(fragment, "COMPILE");

    mProgram = glCreateProgram();

    glAttachShader(mProgram, vertex);
    glAttachShader(mProgram, fragment);

    glLinkProgram(mProgram);
    checkShaderErrors(mProgram, "LINK");

    // 不要忘记清理，因为这两个已经与program链接了，只留下program即可
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader()
{
}

void Shader::begin()
{
    GL_CALL(glUseProgram(mProgram));
}

void Shader::end()
{
    GL_CALL(glUseProgram(0));
}

void Shader::checkShaderErrors(GLuint target, std::string type)
{
    int success = 0;
    char infoLog[1024];

    if (type == "COMPILE")
    {
        glGetShaderiv(target, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(target, 1024, NULL, infoLog);
            std::cout << "Error: SHADER COMPILE ERROR" << "\n"
                      << infoLog << std::endl;
        }
    }
    else if (type == "LINK")
    {
        glGetProgramiv(target, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(target, 1024, NULL, infoLog);
            std::cout << "Error: SHADER LINK ERROR " << "\n"
                      << infoLog << std::endl;
        }
    }
    else
    {
        std::cout << "Error: Check shader errors Type is wrong" << std::endl;
    }
}