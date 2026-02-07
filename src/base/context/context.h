#ifndef CONTEXT_H
#define CONTEXT_H

#include <GLFW/glfw3.h>

typedef struct Context Context;

Context* initContext();

GLFWwindow* getCtxWindow(Context* ctx);
int setCtxWindow(Context* ctx, GLFWwindow* window);

#endif
