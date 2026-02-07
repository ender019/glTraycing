#ifndef WINDOW_H
#define WINDOW_H

#include "src/base/context/context.h"

int initWindow(Context* ctx);

int setWindowResizeCallback(Context* ctx, void(func)(GLFWwindow* window, int width, int height));

int startWindow(Context* ctx, int(work)(Context*));

int destroyWindow(Context* ctx);

#endif

