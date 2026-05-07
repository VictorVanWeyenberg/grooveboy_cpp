#include "oam.h"

#include <cstdlib>

#include "dma.h"

void Object::set_location(const uint8_t x, const uint8_t y) {
    this->x = x;
    this->y = y;
}

void write_oam(const Object *objects, const uint8_t objects_length) {
    const Binary objects_binary(reinterpret_cast<intptr_t>(objects), objects_length * sizeof(Object));
    dma_push(0, objects_binary, MEM_OAM);
}
