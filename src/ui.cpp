#include "ui.h"

#include "cursor.h"
#include "pal.h"
#include "vram.h"

UI::UI(
    const Binary background_palette,
    const Binary character_data[2],
    const Binary screen_data[2],
    const Binary object_palette,
    const Binary object_character_data,
    const Boops boops,
    Cursor cursor
) : background_palette(background_palette),
    character_data{character_data[0], character_data[1]},
    screen_data{screen_data[0], screen_data[1]},
    object_palette(object_palette),
    object_character_data(object_character_data),
    boops(boops),
    cursor(cursor) {
}

void UI::render() {
    write_background_palette(this->background_palette);
    write_character_data(0, this->character_data[0]);
    write_character_data(1, this->character_data[1]);
    write_screen_data(0, this->screen_data[0]);
    write_screen_data(1, this->screen_data[1]);
    write_object_palette(this->object_palette);
    write_object_character_data(this->object_character_data);
    this->cursor.render();
}
