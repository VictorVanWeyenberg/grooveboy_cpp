#include "oam.h"

#include <cstdlib>

#include "dma.h"

volatile OAM_Controller OAMC;

OBJ Object::to_oam() const {
    return OBJ {
        // Attribute 0
        .y = static_cast<uint8_t>(this->y),
        .rotation_scaling_flag = 0,
        .enable = 1,
        .obj_mode = 0,
        .obj_mosaic = 0,
        .palette_mode = 0,
        .shape = 0,

        // Attribute 1
        .x = this->x,
        .not_used = 0,
        .horizontal_flip = this->horizontal_flip,
        .vertical_flip = this->vertical_flip,
        .size = 0,

        // Attribute 2
        .character = this->character_data,
        .priority = 0,
        .palette_number = this->palette_number,

        // Rotation/Scaling Parameters
        .rotation_scaling_parameters = 0
    };
}

bool OAM_Controller::cache(const Object *buffer_, const uint8_t buffer_length_) volatile {
    if (buffer_length_ == 0) {
        free(this->buffer);
        this->buffer = nullptr;
        this->buffer_length = buffer_length_;
        return true;
    }

    bool shrunk = false;
    if (buffer_length_ != this->buffer_length) {
        free(this->buffer);
        shrunk = this->buffer_length > buffer_length_;
        this->buffer = static_cast<OBJ *>(calloc(buffer_length_, sizeof(OBJ)));
        this->buffer_length = buffer_length_;
    }

    for (uint8_t index = 0; index < buffer_length_; ++index) {
        this->buffer[index] = buffer_[index].to_oam();
    }

    return shrunk;
}

OBJ * OAM_Controller::get_buffer() const volatile {
    return this->buffer;
}

uint8_t OAM_Controller::get_buffer_length() const volatile {
    return this->buffer_length;
}

void write_oam(const Object *objects, const uint8_t objects_length) {
    if (objects_length > 128) {
        return;
    }

    const bool shrunk = OAMC.cache(objects, objects_length);

    dma_push(0, Binary(OAMC.get_buffer(), OAMC.get_buffer_length() * sizeof(OBJ)), MEM_OAM);

    if (shrunk) {
        dma_zero(0, (128 - objects_length) * sizeof(OBJ), MEM_OAM + sizeof(OBJ) * objects_length);
    }
}
