#include "init.h"

#include "src/base/graphics/graphics.h"
#include "src/base/window/window.h"
#include <stdlib.h>

int run() {
    Context* ctx = initContext();
    if (!ctx) {
        return -1;
    }
    if (!initWindow(ctx)) {
        return -1;
    }
    if (!initGraphics(ctx)) {
        return -1;
    }
    if (!startWindow(ctx, drawing)) {
        return -1;
    }
    if (!destroyWindow(ctx)) {
        return -1;
    }
    free(ctx);
    return 1;
}
