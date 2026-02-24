#include "ui.h"
#include "pal.h"
#include "vram.h"

void UI::render() const {
    write_background_palette(this->background_palette);
    write_object_palette(this->object_palette);
    write_character_data(0, this->character_data[0]);
    write_character_data(1, this->character_data[1]);
    write_screen_data(0, this->screen_data[0]);
    write_screen_data(1, this->screen_data[1]);
}
