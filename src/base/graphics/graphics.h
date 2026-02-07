#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "src/base/context/context.h"

int initGraphics(Context* ctx);

int drawing(Context* ctx);

int uploadBuffer(float* buf);

#endif
