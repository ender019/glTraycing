#include "context.h"

#include <stdlib.h>

struct Context {
    unsigned int vao, vbo, ebo;
    GLuint program;
//    ObjectCtx* objectCtx;
    GLFWwindow* window;
};

Context* initContext(){
    Context* ctx = malloc(sizeof(Context));
    if (!ctx) {
        return NULL;
    }
//     ctx->objectCtx = initObjectCtx();
    return ctx;
}

GLint getVAO(Context* ctx) {
    return ctx->vao;
}

GLint getVBO(Context* ctx) {
    return ctx->vbo;
}

GLint getEBO(Context* ctx) {
    return ctx->ebo;
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

void setEBO(Context* ctx, unsigned int ebo) {
    ctx->ebo = ebo;
}

void setProgram(Context* ctx, GLint program) {
    ctx->program = program;
}


// ObjectCtx* getObjectCtx(Context* ctx) {
//     return ctx->objectCtx;
// }

GLFWwindow* getCtxWindow(Context* ctx) {
    return ctx->window;
}

int setCtxWindow(Context* ctx, GLFWwindow* window) {
    if (window == NULL) {
        return 0; 
    }
    if (ctx->window != NULL) {
        free(ctx->window); 
    }
    ctx->window = window;
    return 1;
}

void freeContext(Context* ctx) {
//     freeObjectCtx(ctx->objectCtx);
    free(ctx);
}

