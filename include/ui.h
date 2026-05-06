#ifndef GROOVEBOY_UI_H
#define GROOVEBOY_UI_H

#include <memory>

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
        Boops boops
    );

    void render_all() const;
    void render();
    void move_cursor(Direction direction);
    [[nodiscard]] bool will_refresh() const;
private:
    const Binary background_palette;
    const Binary character_data[2];
    const Binary screen_data[2];
    const Binary object_palette;
    const Binary object_character_data;

    Boops boops;
    Cursor cursor;
    bool refresh;
};

void init_ui();
UI edit_ui();
void move_cursor(Direction direction);
void vblank_interrupt();
bool will_refresh();

#endif //GROOVEBOY_UI_H