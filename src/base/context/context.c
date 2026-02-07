#include "context.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>

struct Context {
    GLFWwindow* window;
};

Context* initContext(){
    Context* ctx = malloc(sizeof(Context));
    if (!ctx) {
        return NULL;
    }
    return ctx;
}

GLFWwindow* getCtxWindow(Context* ctx) {
    return ctx->window;
}

int setCtxWindow(Context* ctx, GLFWwindow* window) {
    if (window == NULL) {
        return -1; 
    }
    if (ctx->window != NULL) {
        free(ctx->window); 
    }
    ctx->window = window;
    return 1;
}
