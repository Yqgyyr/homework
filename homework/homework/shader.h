#pragma once


#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
//#include <glm/glm.hpp>
//#include <glm/gtc/type_ptr.hpp>

class  Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        ShaderProgram = glCreateProgram();
        CompileShaderFromFile(vertexPath, GL_VERTEX_SHADER);
        CompileShaderFromFile(fragmentPath, GL_FRAGMENT_SHADER);

    }
    ~Shader()
    {
        glDeleteProgram(ShaderProgram);
    }
    void UseProgram()
    {
        glUseProgram(ShaderProgram);
    }
private:
    GLuint ShaderProgram;
    void CompileShaderFromFile(const char* path, GLenum shaderType)
    {
        std::string code;
        std::ifstream shaderFile;
        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            shaderFile.open(path);
            std::stringstream shaderStream;
            shaderStream << shaderFile.rdbuf();
            shaderFile.close();
            code = shaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULU_READ:" << e.what() << std::endl;
        }
        const GLchar* shaderCode = code.c_str();
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderCode, NULL);
        glCompileShader(shader);
        CheckErrors(shader, "SHADER", GL_COMPILE_STATUS);
        glAttachShader(ShaderProgram, shader);
        glDeleteShader(shader);
    }
    void CheckErrors(GLuint obj, std::string type, GLenum checkStatus)
    {
        GLint success;
        if (type == "SHADER")
        {
            glGetShaderiv(obj, checkStatus, &success);
            if (!success)
            {
                GLchar infoLog[1024];
                glGetShaderInfoLog(obj, 1024, NULL, infoLog);
                std::cout << "ERROE::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
                exit(-1);
            }

        }

        else if (type == "PROGRAM")
        {
            glGetProgramiv(obj, checkStatus, &success);
            if (!success)
            {
                GLchar infoLog[1024];
                glGetProgramInfoLog(obj, 1024, NULL, infoLog);
                std::cout << "ERROE::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
                exit(-1);
            }

        }
    }
};