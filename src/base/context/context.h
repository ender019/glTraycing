#ifndef CONTEXT_H
#define CONTEXT_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>

typedef struct Context Context;

Context* initContext();

GLint getVAO(Context* ctx);
GLint getVBO(Context* ctx);
GLint getEBO(Context* ctx);
GLint getProgram(Context* ctx);
void setVAO(Context* ctx, unsigned int vao);
void setVBO(Context* ctx, unsigned int vbo);
void setEBO(Context* ctx, unsigned int ebo);
void setProgram(Context* ctx, GLint program);

GLFWwindow* getCtxWindow(Context* ctx);
int setCtxWindow(Context* ctx, GLFWwindow* window);

#endif
