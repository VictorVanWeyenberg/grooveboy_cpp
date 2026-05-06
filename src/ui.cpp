#include "ui.h"

#include "cursor.h"
#include "pal.h"
#include "vram.h"

UI ACTIVE_UI = edit_ui();

UI::UI(
    const Binary background_palette,
    const Binary character_data[2],
    const Binary screen_data[2],
    const Binary object_palette,
    const Binary object_character_data,
    const Boops boops
) : background_palette(background_palette),
    character_data{character_data[0], character_data[1]},
    screen_data{screen_data[0], screen_data[1]},
    object_palette(object_palette),
    object_character_data(object_character_data),
    boops(boops) {
    this->cursor = Cursor();
    cursor.point_to(boops.get_current_boop());
    this->refresh = false;
}

void UI::render_all() const {
    write_background_palette(this->background_palette);
    write_character_data(0, this->character_data[0]);
    write_character_data(1, this->character_data[1]);
    write_screen_data(0, this->screen_data[0]);
    write_screen_data(1, this->screen_data[1]);
    write_object_palette(this->object_palette);
    write_object_character_data(this->object_character_data);
    this->cursor.render();
}

void UI::render() {
    if (this->refresh) {
        write_screen_data(1, this->screen_data[1]);
        this->cursor.render();
        this->refresh = false;
    }
}

void UI::move_cursor(const Direction direction) {
    if (this->boops.move(direction)) {
        this->cursor.point_to(this->boops.get_current_boop());
        this->refresh = true;
    }
}

bool UI::will_refresh() const {
    return this->refresh;
}

void move_cursor(const Direction direction) {
    ACTIVE_UI.move_cursor(direction);
}

void vblank_interrupt() {
    ACTIVE_UI.render();
}

void init_ui() {
    ACTIVE_UI.render_all();
}

bool will_refresh() {
    return ACTIVE_UI.will_refresh();
}
