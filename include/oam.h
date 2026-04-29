#ifndef GROOVEBOY_OAM_H
#define GROOVEBOY_OAM_H

#include <cstdint>

#define MEM_OAM 0x07000000

typedef struct OBJ {
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
} OBJ;

class Object {
    uint32_t x: 8;
    uint32_t y: 9;
    uint32_t character_data: 10;
    uint32_t palette_number: 4;
    bool enable = true;
    bool horizontal_flip;
    bool vertical_flip;

public:
    Object(
        const uint8_t x,
        const uint16_t y,
        const uint16_t character_data,
        const uint8_t palette_number,
        const bool horizontal_flip,
        const bool vertical_flip
    ) : x(x),
        y(y),
        character_data(character_data),
        palette_number(palette_number),
        horizontal_flip(horizontal_flip),
        vertical_flip(vertical_flip) {
    }

    [[nodiscard]] OBJ to_oam() const;
};

class OAM_Controller {
    OBJ* buffer = nullptr;
    uint8_t buffer_length = 0;

public:
    bool cache(const Object* buffer_, uint8_t buffer_length_) volatile;
    [[nodiscard]] OBJ* get_buffer() const volatile;
    [[nodiscard]] uint8_t get_buffer_length() const volatile;
};

void write_oam(Object* objects, uint8_t objects_length);

#endif //GROOVEBOY_OAM_H
