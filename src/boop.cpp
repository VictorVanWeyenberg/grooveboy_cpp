#include "boop.h"

Boops::Boops(Boop* boops, uint8_t* args) : boops(boops), args(args) {
}

Boop &Boops::get_current_boop() const {
    return this->boops[this->index];
}

bool Boops::move(const Direction direction) {
    switch (direction) {
        case N:
            if (const auto north = this->get_current_boop().get_north()) {
                this->index = *north;
                return true;
            }
            break;
        case E:
            if (const auto east = this->get_current_boop().get_east()) {
                this->index = *east;
                return true;
            }
            break;
        case S:
            if (const auto south = this->get_current_boop().get_south()) {
                this->index = *south;
                return true;
            }
            break;
        case W:
            if (const auto west = this->get_current_boop().get_west()) {
                this->index = *west;
                return true;
            }
            break;
    }
    return false;
}

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
    return this->data.north;
}

std::optional<uint8_t> Boop::get_east() {
    if (this->data.east == 255) {
        return std::nullopt;
    }
    return this->data.east;
}

std::optional<uint8_t> Boop::get_south() {
    if (this->data.south == 255) {
        return std::nullopt;
    }
    return this->data.south;
}

std::optional<uint8_t> Boop::get_west() {
    if (this->data.west == 255) {
        return std::nullopt;
    }
    return this->data.west;
}

std::optional<uint8_t> Boop::get_callback() {
    if (this->data.callback == 255) {
        return std::nullopt;
    }
    return this->data.callback;
}

uint8_t Boop::get_args_index() const {
    return this->data.args_index;
}

uint8_t Boop::get_args_len() const {
    return this->data.args_len;
}
