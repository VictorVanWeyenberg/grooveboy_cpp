#include "tmr.h"

#include "ui.h"

void write_tmr(const uint8_t channel, const uint16_t reload) {
    TMR[channel].start = false;
    TMR[channel].reload = reload;
    TMR[channel].prescaler = 2;
    TMR[channel].count_up = 0;
    TMR[channel].irq_enabled = true;
    TMR[channel].start = true;
}

void tmr_interrupt(uint8_t channel) {
    move_cursor(S);
}
