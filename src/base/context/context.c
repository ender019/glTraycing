#include "context.h"

#include <stdlib.h>

struct Context {
    unsigned int vao, vbo;
    GLuint program;
    GLFWwindow* window;
};

Context* initContext(){
    Context* ctx = malloc(sizeof(Context));
    if (!ctx) {
        return NULL;
    }
    return ctx;
}

GLint getVAO(Context* ctx) {
    return ctx->vao;
}

GLint getVBO(Context* ctx) {
    return ctx->vbo;
}

GLint getProgram(Context* ctx) {
    return ctx->program;
}

void setVAO(Context* ctx, unsigned int vao) {
    ctx->vao = vao;
}

void setVBO(Context* ctx, unsigned int vbo) {
    ctx->vbo = vbo;
}

void setProgram(Context* ctx, GLint program) {
    ctx->program = program;
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
