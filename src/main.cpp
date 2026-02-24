#include "io.h"
#include "int.h"
#include "ui.h"

[[noreturn]]
int main() {
    init_bg();
    init_interrupts();
    edit_ui().render();

    for (;;) {}
}