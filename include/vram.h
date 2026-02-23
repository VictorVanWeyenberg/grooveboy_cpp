#ifndef GROOVEBOY_VRAM_H
#define GROOVEBOY_VRAM_H

#include <cstdint>

#define MEM_VRAM 0x06000000

#define BG0_SCREEN_BASE 29
#define BG1_SCREEN_BASE 30

#define MEM_BG0_SCREEN_BLOCK ((uint16_t*)(MEM_VRAM + BG0_SCREEN_BASE * 0x800))
#define MEM_BG1_SCREEN_BLOCK ((uint16_t*)(MEM_VRAM + BG1_SCREEN_BASE * 0x800))

#define BG0_CHARACTER_BASE 0
#define BG1_CHARACTER_BASE 1

#define MEM_BG0_CHARACTER_BLOCK ((uint16_t*)(MEM_VRAM + BG0_CHARACTER_BASE * 0x4000))
#define MEM_BG1_CHARACTER_BLOCK ((uint16_t*)(MEM_VRAM + BG1_CHARACTER_BASE * 0x4000))

#define OBJ_CHARACTER_BLOCK ((uint16_t*)(MEM_VRAM + 0x10000))

void set_character_data(uint8_t bg, void* start, uint16_t size);
void set_screen_data(uint8_t bg, void* start, uint16_t size);

#endif //GROOVEBOY_VRAM_H