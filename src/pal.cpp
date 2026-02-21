#include "dma.h"
#include "pal.h"

extern Color* background_palette_start;
extern uint16_t background_palette_size;
extern Color* object_palette_start;
extern uint16_t object_palette_size;

void load_palettes() {
    dma_push(0, &background_palette_start, MEM_BG_PAL, background_palette_size);
    dma_push(0, &object_palette_start, MEM_OBJ_PAL, object_palette_size);
}
