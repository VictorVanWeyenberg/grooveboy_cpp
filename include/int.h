#ifndef GROOVEBOY_INT_H
#define GROOVEBOY_INT_H

#include <cstdint>

typedef void (*fnptr)();

#define REG_DISPSTAT (*((unsigned short *)(0x04000004)))

#define REG_IE (*((unsigned short *)(0x04000200)))
#define REG_IF (*((unsigned short *)(0x04000202)))
#define REG_IME (*((unsigned short *)(0x04000208)))
#define REG_INTERRUPT (*(void (**)())(0x03007FFC))
#define REG_IFBIOS (*((unsigned short *)(0x3007FF8)))

/* Defines for Interrupts */
/* There are 14 Interrupts that we can register with REG_IE */
#define INT_VBLANK 0x0001
#define INT_HBLANK 0x0002
#define INT_VCOUNT 0x0004
#define INT_TIMER0 0x0008
#define INT_TIMER1 0x0010
#define INT_TIMER2 0x0020
#define INT_TIMER3 0x0040
#define INT_COM 0x0080
#define INT_DMA0 0x0100
#define INT_DMA1 0x0200
#define INT_DMA2 0x0400
#define INT_DMA3 0x0800
#define INT_BUTTON 0x1000
#define INT_CART 0x2000

void init_interrupts();
void interrupt_handler();
void dma_interrupt(uint8_t channel);

#endif //GROOVEBOY_INT_H