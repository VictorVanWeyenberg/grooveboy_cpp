#include "int.h"

void init_interrupts() {
    REG_IME = 0x00;
    REG_INTERRUPT = interrupt_handler;
    REG_IE  = INT_DMA0;
    REG_IME = 0x01;
}

void interrupt_handler() {
    if (REG_IF & INT_DMA0) {
        REG_IF |= INT_DMA0;
        dma_interrupt(0);
    }
    if (REG_IF & INT_DMA1) {
        REG_IF |= INT_DMA1;
        dma_interrupt(1);
    }
    if (REG_IF & INT_DMA2) {
        REG_IF |= INT_DMA2;
        dma_interrupt(2);
    }
    if (REG_IF & INT_DMA3) {
        REG_IF |= INT_DMA3;
        dma_interrupt(3);
    }
}