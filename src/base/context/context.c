#include "context.h"

#include <stdlib.h>

struct Context {
    GraphicCtx* graphicCtx;
//    ObjectCtx* objectCtx;
    GLFWwindow* window;
};

Context* initContext(){
    Context* ctx = malloc(sizeof(Context));
    if (!ctx) {
        return NULL;
    }
    ctx->graphicCtx = NULL;
    ctx->window = NULL;
//     ctx->objectCtx = initObjectCtx();
    return ctx;
}

GraphicCtx* getGraphicCtx(Context* ctx) {
    if(!ctx) {
        return NULL;
    }
    return ctx->graphicCtx;
}

void setGraphicCtx(Context* ctx, GraphicCtx* g_ctx) {
    if(!ctx) {
        return;
    }
    ctx->graphicCtx = g_ctx;
}

// ObjectCtx* getObjectCtx(Context* ctx) {
//     return ctx->objectCtx;
// }

GLFWwindow* getCtxWindow(Context* ctx) {
    if (!ctx) {
        return NULL;
    }
    return ctx->window;
}

int setCtxWindow(Context* ctx, GLFWwindow* window) {
    if(!ctx) {
        return 0;
    }
    free(ctx->window); 
    ctx->window = window;
    return 1;
}

void freeContext(Context* ctx) {
//     freeObjectCtx(ctx->objectCtx);
    free(ctx);
}

