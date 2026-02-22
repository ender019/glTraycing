#ifndef BASE_GRAPHIC_H
#define BASE_GRAPHIC_H

#include "src/base/context/context.h"

GLuint compile_shader(GLenum type, const char* source);

int compile_program(GraphicCtx* ctx, GLuint vs, GLuint fs);

int initGraphics(Context* ctx);

int setupRatio(Context* ctx);

#endif
