#ifndef GRAPHIC_CONTEXT_H
#define GRAPHIC_CONTEXT_H

#include <glad/gl.h>

typedef struct GraphicCtx GraphicCtx;


GraphicCtx* initGraphicCtx();

GLuint getVAO(GraphicCtx* ctx);
GLuint getVBO(GraphicCtx* ctx);
GLuint getProgram(GraphicCtx* ctx);

void setVAO(GraphicCtx* ctx, unsigned int vao);
void setVBO(GraphicCtx* ctx, unsigned int vbo);
void setProgram(GraphicCtx* ctx, GLuint program);
void setGraphicMode(GraphicCtx* ctx, void* mode);

void freeGraphicCtx(GraphicCtx* ctx);

#endif
