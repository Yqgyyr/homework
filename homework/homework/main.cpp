#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"

#define ERRORLOG(message) std::cout << message << std::endl;glfwTerminate();return -1;


GLuint VAO, VBO;
static void RenderScreen(GLFWwindow* window)
{
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 9);
    glBindVertexArray(0);
    glfwSwapBuffers(window);
}

static void CreateVertexBuffer()
{
    GLfloat vertices[] = { 0.0f,-1.0f,0.0f,
                           0.5f,1.0f,0.0f,
                           1.0f,-1.0f,0.0f,
                           -1.0f,1.0f,0.0f,
                           -1.0f,0.0f,0.0f,
                           0.0f,1.0f,0.0f,
                           -1.0f,0.0f,0.0f,
                           0.0f,0.0f,0.0f,
                           0.0f,1.0f,0.0f };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

static void SetViewport(GLFWwindow* window)
{
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLTutorial1", NULL, NULL);
    if (window == NULL) { ERRORLOG("Failed to create GLFW window") }
    glfwMakeContextCurrent(window);

    if (GLEW_OK != glewInit()) { ERRORLOG("Failed to init glew") }
    CreateVertexBuffer();
    Shader shader = Shader("res/shaders/core.vs", "res/shaders/core.fs");
    while (!glfwWindowShouldClose(window))
    {
        SetViewport(window);
        glfwPollEvents();
        shader.UseProgram();
        RenderScreen(window);
    }
    glfwTerminate();
    return 1;
}