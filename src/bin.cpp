#include "bin.h"

Binary::Binary(const intptr_t start, const uint16_t size) : start(start), size(size) {
}

intptr_t Binary::get_start() const {
    return this->start;
}

uint16_t Binary::get_size() const {
    return this->size;
}