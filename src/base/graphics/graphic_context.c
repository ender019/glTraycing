#include "graphic_context.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct GraphicFormat {
    void (*g_free)(void*);
} GraphicFormat;

typedef struct GraphicCtx {
    GLuint program;
    unsigned int vao, vbo;
    void* mode_ctx;
} GraphicCtx;

// ================= КОНСТРУКТОР =================

GraphicCtx* initGraphicCtx() {
    GraphicCtx* ctx = malloc(sizeof(GraphicCtx));
    if (!ctx) {
        fprintf(stderr, "[ERROR] %s: Failed to allocate memory for GraphicCtx\n", __func__);
        return NULL;
    }
    
    ctx->program = 0;
    ctx->vao = 0;
    ctx->vbo = 0;
    ctx->mode_ctx = NULL;
    
    return ctx;
}

// ================= ГЕТТЕРЫ =================

GLuint getVAO(GraphicCtx* ctx) {
    if (!ctx) {
        fprintf(stderr, "[ERROR] %s: NULL GraphicCtx pointer provided\n", __func__);
        return 0;
    }
    return ctx->vao;
}

GLuint getVBO(GraphicCtx* ctx) {
    if (!ctx) {
        fprintf(stderr, "[ERROR] %s: NULL GraphicCtx pointer provided\n", __func__);
        return 0;
    }
    return ctx->vbo;
}

GLuint getProgram(GraphicCtx* ctx) {
    if (!ctx) {
        fprintf(stderr, "[ERROR] %s: NULL GraphicCtx pointer provided\n", __func__);
        return 0;
    }
    return ctx->program;
}

// ================= СЕТТЕРЫ =================

void setVAO(GraphicCtx* ctx, unsigned int vao) {
    if (!ctx) {
        fprintf(stderr, "[ERROR] %s: NULL GraphicCtx pointer provided\n", __func__);
        return;
    }
    ctx->vao = vao;
}

void setVBO(GraphicCtx* ctx, unsigned int vbo) {
    if (!ctx) {
        fprintf(stderr, "[ERROR] %s: NULL GraphicCtx pointer provided\n", __func__);
        return;
    }
    ctx->vbo = vbo;
}

void setProgram(GraphicCtx* ctx, GLuint program) {
    if (!ctx) {
        fprintf(stderr, "[ERROR] %s: NULL GraphicCtx pointer provided\n", __func__);
        return;
    }
    ctx->program = program;
}

void setGraphicMode(GraphicCtx* ctx, void* mode) {
    if (!ctx) {
        fprintf(stderr, "[ERROR] %s: NULL GraphicCtx pointer provided\n", __func__);
        return; 
    }
    
    // Освобождаем старый режим, если он был
    if (ctx->mode_ctx) {
        GraphicFormat* g_ctx = (GraphicFormat*)(ctx->mode_ctx);
        if (g_ctx && g_ctx->g_free) {
            g_ctx->g_free(ctx->mode_ctx);
        } else {
            fprintf(stderr, "[WARNING] %s: Previous mode_ctx lacks a valid g_free function pointer\n", __func__);
        }
    }
    
    ctx->mode_ctx = mode;
}

// ================= ДЕСТРУКТОР =================

void freeGraphicCtx(GraphicCtx* ctx) {
    if (!ctx) {
        fprintf(stderr, "[ERROR] %s: NULL GraphicCtx pointer provided\n", __func__);
        return;
    }
    
    if (ctx->mode_ctx) {
        GraphicFormat* g_ctx = (GraphicFormat*)(ctx->mode_ctx);
        if (g_ctx && g_ctx->g_free) {
            g_ctx->g_free(ctx->mode_ctx);
        } else {
            fprintf(stderr, "[WARNING] %s: mode_ctx lacks a valid g_free function pointer\n", __func__);
        }
    }
    
    free(ctx);
}
