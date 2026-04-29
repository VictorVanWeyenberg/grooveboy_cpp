#ifndef GROOVEBOY_UI_H
#define GROOVEBOY_UI_H

#include "bin.h"
#include "boop.h"
#include "cursor.h"

class UI {
public:
    UI(
        Binary background_palette,
        const Binary character_data[2],
        const Binary screen_data[2],
        Binary object_palette,
        Binary object_character_data,
        Boops boops,
        Cursor cursor
    );

    void render();
private:
    Binary background_palette;
    Binary character_data[2];
    Binary screen_data[2];
    Binary object_palette;
    Binary object_character_data;
    Boops boops;
    Cursor cursor;
};

UI edit_ui();

#endif //GROOVEBOY_UI_H