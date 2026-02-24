#include "dma.h"
#include "pal.h"

void write_background_palette(const Binary data) {
    dma_push(0, data, MEM_BG_PAL);
}

void write_object_palette(const Binary data) {
    dma_push(0, data, MEM_OBJ_PAL);
}
