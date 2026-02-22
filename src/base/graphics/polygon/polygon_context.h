#ifndef POLYGON_CONTEXT_H
#define POLYGON_CONTEXT_H

typedef struct PolygonCtx PolygonCtx;

PolygonCtx* initPolygonCtx();

// ================= ГЕТТЕРЫ =================

unsigned int getEBO(const struct PolygonCtx* ctx);
float* getVertices(const struct PolygonCtx* ctx);
unsigned int* getIndices(const struct PolygonCtx* ctx);

// ================= СЕТТЕРЫ =================

void setEBO(struct PolygonCtx* ctx, unsigned int ebo);
void setVertices(struct PolygonCtx* ctx, float* vertices);
void setIndices(struct PolygonCtx* ctx, unsigned int* indices);

void freePolygonCtx(void* g_ctx);

#endif
