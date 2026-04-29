#include "boop.h"

uint8_t Boop::get_x() const {
    return this->data.x;
}

uint8_t Boop::get_y() const {
    return this->data.y;
}

uint8_t Boop::get_w() const {
    return this->data.w;
}

uint8_t Boop::get_h() const {
    return this->data.h;
}

std::optional<uint8_t> Boop::get_north() {
    if (this->data.north == 255) {
        return std::nullopt;
    }
    return std::optional(this->data.north);
}

std::optional<uint8_t> Boop::get_east() {
    if (this->data.east == 255) {
        return std::nullopt;
    }
    return std::optional(this->data.east);
}

std::optional<uint8_t> Boop::get_south() {
    if (this->data.south == 255) {
        return std::nullopt;
    }
    return std::optional(this->data.south);
}

std::optional<uint8_t> Boop::get_west() {
    if (this->data.west == 255) {
        return std::nullopt;
    }
    return std::optional(this->data.west);
}

std::optional<uint8_t> Boop::get_callback() {
    if (this->data.callback == 255) {
        return std::nullopt;
    }
    return std::optional(this->data.callback);
}

uint8_t Boop::get_args_index() const {
    return this->data.args_index;
}

uint8_t Boop::get_args_len() const {
    return this->data.args_len;
}
