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
    if (REG_IF & INT_DMA0) {
        REG_IF |= INT_DMA0;
        dma_interrupt(0);
    }
    if (REG_IF & INT_TIMER2) {
        REG_IF |= INT_TIMER2;
        tmr_interrupt(2);
    }
    if (REG_IF & INT_VBLANK) {
        REG_IF |= INT_VBLANK;
        vblank_interrupt();
    }
}