#include "init.h"

#include "src/base/graphics/polygon_graphic.h"
#include "src/base/window/window.h"

int run() {
    Context* ctx = initContext();
    if (!ctx) {
        return 0;
    }
    if (!initWindow(ctx)) {
        return 0;
    }
    if (!initPolygon(ctx)) {
        return 0;
    }
    if (!startWindow(ctx, drawPolygon)) {
        return 0;
    }
    if (!destroyWindow(ctx)) {
        return 0;
    }
    freeContext(ctx);
    return 1;
}
