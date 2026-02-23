#include "io.h"
#include "vram.h"

extern uint16_t *BG00_character_data_start;
extern uint16_t BG00_character_data_size;

extern uint16_t *BG01_character_data_start;
extern uint16_t BG01_character_data_size;

extern uint16_t *empty_art_BG00_screen_data_start;
extern uint16_t empty_art_BG00_screen_data_size;

extern uint16_t *empty_art_BG01_screen_data_start;
extern uint16_t empty_art_BG01_screen_data_size;

void init_bg() {
    REG_DISPLAY = BG_MODE_0 | SCREEN_DISPLAY_BG0 | SCREEN_DISPLAY_BG1 |
                  SCREEN_DISPLAY_OBJ | ONE_DIMENSIONAL_OBJ_CHARACTER_VRAM_MAPPING;
    BG1CNT = 0 | BGCNT_SCREEN_SIZE_0 | BG1_CHARACTER_BASE << 2 | BG1_SCREEN_BASE << 8 | 1;
    BG0CNT = 0 | BGCNT_SCREEN_SIZE_0 | BG0_CHARACTER_BASE << 2 | BG0_SCREEN_BASE << 8 | 0;

    set_character_data(0, &BG00_character_data_start, BG00_character_data_size);
    set_character_data(1, &BG01_character_data_start, BG01_character_data_size);

    set_screen_data(0, &empty_art_BG00_screen_data_start, empty_art_BG00_screen_data_size);
    set_screen_data(1, &empty_art_BG01_screen_data_start, empty_art_BG01_screen_data_size);
}