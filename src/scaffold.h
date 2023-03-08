#ifndef SCAFFOLD_H
#define SCAFFOLD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void GLAPIENTRY messageCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar *message,
    const void *userParam);


int initContext(GLFWwindow *window);

int compileProgramFromPaths(GLuint *prog, const char *vsSource, const char *fsSource);

#endif
