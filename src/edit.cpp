#include "edit.h"
#include "ui.h"

extern uint16_t background_palette_start[];
extern uint16_t background_palette_size;

extern uint16_t empty_art_bg0_characters_start[];
extern uint16_t empty_art_bg0_characters_size;

extern uint16_t empty_art_bg1_characters_start[];
extern uint16_t empty_art_bg1_characters_size;

extern uint16_t empty_art_bg0_screen_start[];
extern uint16_t empty_art_bg0_screen_size;

extern uint16_t empty_art_bg1_screen_start[];
extern uint16_t empty_art_bg1_screen_size;

extern uint16_t object_palette_start[];
extern uint16_t object_palette_size;

extern uint16_t object_characters_start[];
extern uint16_t object_characters_size;

UI edit_ui() {
    const Binary background_palette { background_palette_start, background_palette_size };
    const Binary bg0_character_data { empty_art_bg0_characters_start, empty_art_bg0_characters_size };
    const Binary bg1_character_data { empty_art_bg1_characters_start, empty_art_bg1_characters_size };
    const Binary bg0_screen_data { empty_art_bg0_screen_start, empty_art_bg0_screen_size };
    const Binary bg1_screen_data { empty_art_bg1_screen_start, empty_art_bg1_screen_size };
    const Binary object_palette { object_palette_start, object_palette_size };
    const Binary object_characters { object_characters_start, object_characters_size };
    return UI {
        background_palette,
        bg0_character_data,
        bg1_character_data,
        bg0_screen_data,
        bg1_screen_data,
        object_palette,
        object_characters
    };
}