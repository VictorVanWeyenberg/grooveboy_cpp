#ifndef GROOVEBOY_BG_H
#define GROOVEBOY_BG_H

#include <cstdint>

#define MEM_IO 0x04000000
#define BG0CNT (*((volatile uint16_t *)(MEM_IO + 0x8)))
#define BG1CNT (*((volatile uint16_t *)(MEM_IO + 0xA)))
#define BG2CNT (*((volatile uint16_t *)(MEM_IO + 0xC)))
#define BG3CNT (*((volatile uint16_t *)(MEM_IO + 0xE)))

#define REG_DISPLAY   (*((volatile uint16_t *)(MEM_IO)))
#define REG_VCOUNT    (*(volatile uint16_t *)0x04000006)

#define BG_MODE_0 0
#define BG_MODE_1 1
#define BG_MODE_2 2
#define BG_MODE_3 3
#define BG_MODE_4 4
#define BG_MODE_5 5

#define SCREEN_DISPLAY_BG0 1 << 8
#define SCREEN_DISPLAY_BG1 1 << 9
#define SCREEN_DISPLAY_BG2 1 << 10
#define SCREEN_DISPLAY_BG3 1 << 11
#define SCREEN_DISPLAY_OBJ 1 << 12

#define ONE_DIMENSIONAL_OBJ_CHARACTER_VRAM_MAPPING 1 << 6

#define BGCNT_SCREEN_SIZE_0 0 << 14
#define BGCNT_SCREEN_SIZE_1 1 << 14
#define BGCNT_SCREEN_SIZE_2 2 << 14
#define BGCNT_SCREEN_SIZE_3 3 << 14

#define BGCNT_256_COLORS 1 << 7
#define BGCNT_MOSAIC_ENABLE 1 << 6

#define BGCNT_PRIORITY_0 0
#define BGCNT_PRIORITY_1 1
#define BGCNT_PRIORITY_2 2
#define BGCNT_PRIORITY_3 3

#define MEM_VRAM 0x06000000

#define BG0_SCREEN_BASE 29
#define BG1_SCREEN_BASE 30
#define BG2_SCREEN_BASE 31

#define MEM_BG0_SCREEN_BLOCK ((uint16_t*)(MEM_VRAM + BG0_SCREEN_BASE * 0x800))
#define MEM_BG1_SCREEN_BLOCK ((uint16_t*)(MEM_VRAM + BG1_SCREEN_BASE * 0x800))
#define MEM_BG2_SCREEN_BLOCK ((uint16_t*)(MEM_VRAM + BG2_SCREEN_BASE * 0x800))

#define BG0_CHARACTER_BASE 0
#define BG1_CHARACTER_BASE 1
#define BG2_CHARACTER_BASE 2

#define MEM_BG0_CHARACTER_BLOCK ((uint16_t*)(MEM_VRAM + BG0_CHARACTER_BASE * 0x4000))
#define MEM_BG1_CHARACTER_BLOCK ((uint16_t*)(MEM_VRAM + BG1_CHARACTER_BASE * 0x4000))
#define MEM_BG2_CHARACTER_BLOCK ((uint16_t*)(MEM_VRAM + BG2_CHARACTER_BASE * 0x4000))

#define OBJ_CHARACTER_BLOCK ((uint16_t*)(MEM_VRAM + 0x10000))

void init_bg();

#endif //GROOVEBOY_BG_H