#ifndef CONTEXT_H
#define CONTEXT_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "src/base/graphics/graphic_context.h"

typedef struct Context Context;

Context* initContext();

// ObjectCtx* getObjectCtx(Context* ctx);
GraphicCtx* getGraphicCtx(Context* ctx);
void setGraphicCtx(Context* ctx, GraphicCtx* g_ctx);

GLFWwindow* getCtxWindow(Context* ctx);
int setCtxWindow(Context* ctx, GLFWwindow* window);

void freeContext(Context* ctx);

#endif
