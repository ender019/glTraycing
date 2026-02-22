#include "polygon_context.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct PolygonCtx {
    void (*g_free)(void*);
    unsigned int ebo;
    float* vertices;
    unsigned int* indices;
} PolygonCtx;

// ================= КОНСТРУКТОР =================

PolygonCtx* initPolygonCtx() {
    PolygonCtx* ctx = malloc(sizeof(PolygonCtx));
    if (!ctx) {
        fprintf(stderr, "[ERROR] %s: Failed to allocate memory for PolygonCtx\n", __func__);
        return NULL;
    }
    
    ctx->g_free = freePolygonCtx;
    ctx->ebo = 0;
    ctx->vertices = NULL;
    ctx->indices = NULL;
    
    return ctx;
}

// ================= ГЕТТЕРЫ =================

unsigned int getEBO(const PolygonCtx* ctx) {
    if (!ctx) {
        fprintf(stderr, "[ERROR] %s: NULL PolygonCtx pointer provided\n", __func__);
        return 0;
    }
    return ctx->ebo;
}

float* getVertices(const PolygonCtx* ctx) {
    if (!ctx) {
        fprintf(stderr, "[ERROR] %s: NULL PolygonCtx pointer provided\n", __func__);
        return NULL;
    }
    return ctx->vertices;
}

unsigned int* getIndices(const PolygonCtx* ctx) {
    if (!ctx) {
        fprintf(stderr, "[ERROR] %s: NULL PolygonCtx pointer provided\n", __func__);
        return NULL;
    }
    return ctx->indices;
}

// ================= СЕТТЕРЫ =================

void setEBO(PolygonCtx* ctx, unsigned int ebo) {
    if (!ctx) {
        fprintf(stderr, "[ERROR] %s: NULL PolygonCtx pointer provided\n", __func__);
        return; // Добавлен пропущенный return
    }
    ctx->ebo = ebo;
}

void setVertices(PolygonCtx* ctx, float* vertices) {
    if (!ctx) {
        fprintf(stderr, "[ERROR] %s: NULL PolygonCtx pointer provided\n", __func__);
        return;
    }
    ctx->vertices = vertices;
}

void setIndices(PolygonCtx* ctx, unsigned int* indices) {
    if (!ctx) {
        fprintf(stderr, "[ERROR] %s: NULL PolygonCtx pointer provided\n", __func__);
        return;
    }
    ctx->indices = indices;
}

// ================= ДЕСТРУКТОР =================

void freePolygonCtx(void* g_ctx) {
    if (!g_ctx) {
        fprintf(stderr, "[ERROR] %s: NULL pointer provided\n", __func__);
        return;
    }
    
    PolygonCtx* ctx = (PolygonCtx*)g_ctx;
    
    // Освобождаем память (free(NULL) безопасно в Си, поэтому доп. проверки не нужны)
    free(ctx->vertices);
    free(ctx->indices);
    free(ctx);
}
