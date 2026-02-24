#ifndef GROOVEBOY_VRAM_H
#define GROOVEBOY_VRAM_H

#include <cstdint>
#include "bin.h"

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

void write_character_data(uint8_t bg, Binary data);
void write_screen_data(uint8_t bg, Binary data);

#endif //GROOVEBOY_VRAM_H