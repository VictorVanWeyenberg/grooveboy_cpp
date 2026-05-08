#include "key.h"

#include <cstdint>

constexpr uint64_t CHUNK_MSB_MASK = 0x8080808080808080ULL;
constexpr uint64_t CHUNK_MSB_SUPPRESS = ~CHUNK_MSB_MASK;

volatile uint64_t history;
constexpr Keypad tracked_keys[8] = {A, B, Right, Left, Up, Down, R, L};

void init_keys() {
    KEYCNT = 0x0000;
    history = 0;
}

inline uint64_t spread_bits(const uint64_t x) {
    return
            (x & 0x001) << 0 | // bit 0 → position 0
            (x & 0x002) << 7 | // bit 1 → position 8
            (x & 0x004) << 14 | // bit 2 → position 16
            (x & 0x008) << 21 | // bit 3 → position 24
            (x & 0x010) << 28 | // bit 4 → position 32
            (x & 0x020) << 35 | // bit 5 → position 40
            (x & 0x040) << 42 | // bit 6 → position 48
            (x & 0x080) << 49;  // bit 7 → position 56
}

inline uint8_t get_history(const Keypad key) {
    return history >> key * 8;
}

inline void clear_history(const Keypad key) {
    history &= ~(static_cast<uint64_t>(0xff) << (key * 8));
}

void register_key_presses() {
    const uint16_t key_input = ~KEYINPUT & 0x01ff;
    const uint64_t tracked_input = (key_input & 0xfff3) >> 2 | (key_input & 3); // All except start and select.
    const uint64_t spread = spread_bits(tracked_input);
    history = (history & CHUNK_MSB_SUPPRESS) << 1 | spread;
}

bool key_pressed(const Keypad key) {
    const uint8_t key_history = get_history(key);
    const auto pressed = key_history != 0 && (key_history & 0x81) == 0;
    if (pressed) {
        clear_history(key);
    }
    return pressed;
}

bool key_held(const Keypad key) {
    return get_history(key) == 0xff;
}
