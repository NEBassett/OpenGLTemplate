#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

typedef struct {
  GLsizei count;
  GLuint vao;
} vaoObject;

typedef struct {
  vaoObject data;
  mat4 transform;
} renderObject;

void drawObject(const renderObject *obj);

#endif
