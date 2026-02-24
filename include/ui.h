#ifndef GROOVEBOY_UI_H
#define GROOVEBOY_UI_H

#include "bin.h"

class UI {
public:
    UI(
        const Binary background_palette,
        const Binary object_palette,
        const Binary bg0_character_data,
        const Binary bg1_character_data,
        const Binary bg0_screen_data,
        const Binary bg1_screen_data
    ) : background_palette(background_palette),
    object_palette(object_palette),
    character_data { bg0_character_data, bg1_character_data },
    screen_data { bg0_screen_data, bg1_screen_data } {}

    void render() const;
private:
    Binary background_palette;
    Binary object_palette;
    Binary character_data[2];
    Binary screen_data[2];
};

UI edit_ui();

#endif //GROOVEBOY_UI_H