#include "init.h"

#include "src/base/context/context.h"
#include "src/base/window/window.h"

int work(Context* ctx) {
    return ctx != NULL;
}

int run() {
    Context* ctx = initContext();
    if (!ctx) {
        return -1;
    }
    if (!initWindow(ctx)) {
        return -1;
    }
    if (!startWindow(ctx, work)) {
        return -1;
    }
    if (!destroyWindow(ctx)) {
        return -1;
    }
    return 1;
}
