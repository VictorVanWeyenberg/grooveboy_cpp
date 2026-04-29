#ifndef GROOVEBOY_CURSOR_H
#define GROOVEBOY_CURSOR_H
#include "oam.h"

class Cursor {
public:
    Cursor();

private:
    Object nw; // North West
    Object ne; // North East
    Object sw; // South West
    Object se; // South East
};

#endif //GROOVEBOY_CURSOR_H
