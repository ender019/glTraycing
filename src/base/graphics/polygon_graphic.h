#ifndef POLYGON_GRAPHIC_H
#define POLYGON_GRAPHIC_H

#include "src/base/context/context.h"

typedef struct PolygonCtx PolygonCtx;

int initPolygon(Context* ctx);

int uploadPolygonBuffer(
        Context* ctx,
        const float *vertices, size_t vsize,
        const unsigned int *indices, size_t isize
);

int drawPolygon(Context* ctx);

#endif
