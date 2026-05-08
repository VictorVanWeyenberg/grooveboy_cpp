#ifndef GROOVEBOY_KEY_H
#define GROOVEBOY_KEY_H

#include "io.h"

#define KEYINPUT (*(volatile uint16_t *)(MEM_IO + 0x0130))
#define KEYCNT (*(volatile uint16_t *)(MEM_IO + 0x0132))

#define KEY_A 0x0000
#define KEY_B 0x0001
#define KEY_SELECT 0x0002
#define KEY_START 0x0004
#define KEY_RIGHT 0x0008
#define KEY_LEFT 0x0010
#define KEY_UP 0x0020
#define KEY_DOWN 0x0040
#define KEY_R 0x0080
#define KEY_L 0x0100

enum Keypad {
    A = 0,
    B = 1,
    Select = 8,
    Start = 9,
    Right = 2,
    Left = 3,
    Up = 4,
    Down = 5,
    R = 6,
    L = 7
};

void init_keys();
void register_key_presses();
bool key_pressed(Keypad key);
bool key_held(Keypad key);

#endif //GROOVEBOY_KEY_H
