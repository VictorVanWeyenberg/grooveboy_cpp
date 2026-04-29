#include "io.h"
#include "int.h"
#include "tmr.h"
#include "ui.h"

[[noreturn]]
int main() {
    init_bg();
    init_interrupts();
    write_tmr(2, 0);
    init_ui();

    for (;;) {}
}