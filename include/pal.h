#ifndef PAL_H
#define PAL_H

#define MEM_PAL 0x05000000

class Color {
    unsigned short r: 5;
    unsigned short g: 5;
    unsigned short b: 5;

public:
    Color(const unsigned int r, const unsigned int g, const unsigned int b) : r(r), g(g), b(b) {
    }
};

#define MEM_BG_PAL ((Color *)(MEM_PAL))
#define MEM_OBJ_PAL ((Color *)(MEM_PAL + 0x200))

void load_palettes();

#endif
