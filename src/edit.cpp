#include "edit.h"
#include "ui.h"

extern uint16_t background_palette_start[];
extern uint16_t background_palette_size;

extern uint16_t object_palette_start[];
extern uint16_t object_palette_size;

extern uint16_t BG00_character_data_start[];
extern uint16_t BG00_character_data_size;

extern uint16_t BG01_character_data_start[];
extern uint16_t BG01_character_data_size;

extern uint16_t empty_art_BG00_screen_data_start[];
extern uint16_t empty_art_BG00_screen_data_size;

extern uint16_t empty_art_BG01_screen_data_start[];
extern uint16_t empty_art_BG01_screen_data_size;

UI edit_ui() {
    const Binary background_palette { background_palette_start, background_palette_size };
    const Binary object_palette { object_palette_start, object_palette_size };
    const Binary bg0_character_data { BG00_character_data_start, BG00_character_data_size };
    const Binary bg1_character_data { BG01_character_data_start, BG01_character_data_size };
    const Binary bg0_screen_data { empty_art_BG00_screen_data_start, empty_art_BG00_screen_data_size };
    const Binary bg1_screen_data { empty_art_BG01_screen_data_start, empty_art_BG01_screen_data_size };
    return UI {
        background_palette,
        object_palette,
        bg0_character_data,
        bg1_character_data,
        bg0_screen_data,
        bg1_screen_data
    };
}