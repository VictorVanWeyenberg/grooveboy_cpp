#include "bg.h"
#include "dma.h"

extern uint16_t* BG00_character_data_start;
extern uint16_t BG00_character_data_size;

extern uint16_t* BG01_character_data_start;
extern uint16_t BG01_character_data_size;

extern uint16_t* empty_art_BG00_screen_data_start;
extern uint16_t empty_art_BG00_screen_data_size;

extern uint16_t* empty_art_BG01_screen_data_start;
extern uint16_t empty_art_BG01_screen_data_size;

void init_bg() {
    REG_DISPLAY = BG_MODE_0 | SCREEN_DISPLAY_BG0 | SCREEN_DISPLAY_BG1 |
                SCREEN_DISPLAY_BG2 | SCREEN_DISPLAY_OBJ |
                ONE_DIMENSIONAL_OBJ_CHARACTER_VRAM_MAPPING;
    BG0CNT = 0 | BGCNT_SCREEN_SIZE_0 | BG0_CHARACTER_BASE << 2 | BG0_SCREEN_BASE << 8 | 0;
    BG1CNT = 0 | BGCNT_SCREEN_SIZE_0 | BG1_CHARACTER_BASE << 2 | BG1_SCREEN_BASE << 8 | 1;
    BG2CNT = 0 | BGCNT_SCREEN_SIZE_0 | BG2_CHARACTER_BASE << 2 | BG2_SCREEN_BASE << 8 | 2;

    dma_push(0, &BG00_character_data_start, MEM_BG0_CHARACTER_BLOCK, BG00_character_data_size);
    dma_push(0, &BG01_character_data_start, MEM_BG1_CHARACTER_BLOCK, BG01_character_data_size);

    dma_push(0, &empty_art_BG00_screen_data_start, MEM_BG0_SCREEN_BLOCK, empty_art_BG00_screen_data_size);
    dma_push(0, &empty_art_BG01_screen_data_start, MEM_BG1_SCREEN_BLOCK, empty_art_BG01_screen_data_size);
}
