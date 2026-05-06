#include "int.h"

#include "tmr.h"
#include "ui.h"

void init_interrupts() {
    REG_IME = 0x00;
    REG_INTERRUPT = interrupt_handler;
    REG_IE  = INT_DMA0 | INT_TIMER2 | INT_VBLANK;
    REG_IME = 0x01;
}

void interrupt_handler() {
    const uint16_t flags = REG_IF & REG_IE;
    REG_IF = flags; // Acknowledgement.

    if (flags & INT_DMA0) {
        dma_interrupt(0);
    }
    if (flags & INT_TIMER2) {
        tmr_interrupt(2);
    }
    if (flags & INT_VBLANK) {
        vblank_interrupt();
    }
}