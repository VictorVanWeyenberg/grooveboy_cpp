#ifndef GROOVEBOY_CURSOR_H
#define GROOVEBOY_CURSOR_H
#include "oam.h"
#include "boop.h"

class Cursor {
public:
    Cursor();
    void point_to(const Boop &boop);
    void render();

private:
    Object objs[4];
};

#endif //GROOVEBOY_CURSOR_H
