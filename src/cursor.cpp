#include "cursor.h"

Cursor::Cursor() : objs{
    Object(0, 0, 1, 0, false, false),
    Object(0, 0, 1, 0, false, true),
    Object(0, 0, 1, 0, true, false),
    Object(0, 0, 1, 0, true, true)
} {
}

void Cursor::point_to(const Boop &boop) {
    const auto x = boop.get_x();
    const auto y = boop.get_y();
    const auto w = boop.get_w();
    const auto h = boop.get_h();
    this->objs[0].set_location(x - 1, y - 1);
    this->objs[1].set_location(x - 1, y + h + 1);
    this->objs[2].set_location(x + w + 1, y - 1);
    this->objs[3].set_location(x + w + 1, y + h + 1);
}

void Cursor::render() const {
    write_oam(this->objs, 4);
}
