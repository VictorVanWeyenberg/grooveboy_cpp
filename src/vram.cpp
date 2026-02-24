#include "dma.h"
#include "vram.h"

void write_character_data(const uint8_t bg, const Binary data) {
    switch (bg) {
        case 0:
            dma_push(0, data, MEM_BG0_CHARACTER_BLOCK);
            break;
        case 1:
            dma_push(0, data, MEM_BG1_CHARACTER_BLOCK);
            break;
        default: break;
    }
}

void write_screen_data(const uint8_t bg, const Binary data) {
    switch (bg) {
        case 0:
            dma_push(0, data, MEM_BG0_SCREEN_BLOCK);
            break;
        case 1:
            dma_push(0, data, MEM_BG1_SCREEN_BLOCK);
            break;
        default: break;
    }
}
