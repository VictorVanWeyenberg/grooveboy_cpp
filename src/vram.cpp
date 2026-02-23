#include "dma.h"
#include "vram.h"

void set_character_data(const uint8_t bg, void *start, const uint16_t size) {
    switch (bg) {
        case 0:
            dma_push(0, start, MEM_BG0_CHARACTER_BLOCK, size);
            break;
        case 1:
            dma_push(0, start, MEM_BG1_CHARACTER_BLOCK, size);
            break;
        default: break;
    }
}

void set_screen_data(const uint8_t bg, void *start, const uint16_t size) {
    switch (bg) {
        case 0:
            dma_push(0, start, MEM_BG0_SCREEN_BLOCK, size);
            break;
        case 1:
            dma_push(0, start, MEM_BG1_SCREEN_BLOCK, size);
            break;
        default: break;
    }
}
