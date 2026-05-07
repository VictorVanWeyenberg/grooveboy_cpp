#ifndef GROOVEBOY_OAM_H
#define GROOVEBOY_OAM_H

#include <cstdint>

#define MEM_OAM 0x07000000

class Object {
    // Attribute 0
    uint8_t y: 8;
    uint8_t rotation_scaling_flag: 1;
    uint8_t enable: 1;
    uint8_t obj_mode: 2;
    uint8_t obj_mosaic: 1;
    uint8_t palette_mode: 1;
    uint8_t shape: 2;

    // Attribute 1
    uint16_t x: 9;
    uint16_t not_used: 3;
    uint16_t horizontal_flip: 1;
    uint16_t vertical_flip: 1;
    uint16_t size: 2;

    // Attribute 2
    uint16_t character: 10;
    uint16_t priority: 2;
    uint16_t palette_number: 4;

    // Rotation/Scaling Parameters
    uint16_t rotation_scaling_parameters: 16;

public:
    Object(
        const uint8_t x,
        const uint8_t y,
        const uint16_t character,
        const uint8_t palette_number,
        const bool horizontal_flip,
        const bool vertical_flip
    ) {
        this->y = y;
        this->rotation_scaling_flag = 0;
        this->enable = 0;
        this->obj_mode = 0;
        this->obj_mosaic = 0;
        this->palette_mode = 0;
        this->shape = 0;
        this->x = x;
        this->not_used = 0;
        this->horizontal_flip = horizontal_flip;
        this->vertical_flip = vertical_flip;
        this->size = 0;
        this->character = character;
        this->priority = 0;
        this->palette_number = palette_number;
        this->rotation_scaling_parameters = 0;
    }

    void set_location(uint8_t x, uint8_t y);
};

void write_oam(const Object *objects, uint8_t objects_length);

#endif //GROOVEBOY_OAM_H
