#include "io.h"
#include "int.h"
#include "key.h"
#include "tmr.h"
#include "ui.h"

void handle_keypad() {
    if (will_refresh()) {
        return;
    }
    if (key_pressed(Up) || key_held(Up)) {
        move_cursor(N);
    }
    if (key_pressed(Down) || key_held(Down)) {
        move_cursor(S);
    }
    if (key_pressed(Left) || key_held(Left)) {
        move_cursor(W);
    }
    if (key_pressed(Right) || key_held(Right)) {
        move_cursor(E);
    }
}

[[noreturn]]
int main() {
    init_bg();
    init_keys();
    init_interrupts();
    write_tmr(2, 65536.0 * .980); // 20 ms
    init_ui();

    for (;;) {
        handle_keypad();
    }
}