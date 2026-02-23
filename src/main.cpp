#include "io.h"
#include "int.h"
#include "pal.h"

[[noreturn]]
int main() {
    init_bg();
    init_interrupts();
    load_palettes();

    for (;;) {}
}