#ifndef GROOVEBOY_TMR_H
#define GROOVEBOY_TMR_H
#include <cstdint>

struct TM_Channel {
    uint16_t reload;
    uint16_t prescaler: 2;
    uint16_t count_up: 1;
    uint16_t unused: 3;
    uint16_t irq_enabled: 1;
    uint16_t start: 1;
};

#define TMR ((volatile TM_Channel *)0x04000100)

void write_tmr(uint8_t channel, uint16_t reload);
void tmr_interrupt(uint8_t channel);

#endif //GROOVEBOY_TMR_H
