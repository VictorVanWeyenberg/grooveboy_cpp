#ifndef GROOVEBOY_DMA_H
#define GROOVEBOY_DMA_H

#include <cstdint>
#include <deque>

#include "bin.h"

class DMA_Entry {
public:
    Binary data;
    void *dst = nullptr;
};

static std::deque<DMA_Entry *> make_pool() {
    std::deque<DMA_Entry *> pool;
    for (size_t index = 0; index < 8; ++index) {
        pool.push_back(new DMA_Entry());
    }
    return pool;
}

class DMA_Controller {
public:
    void push(uint8_t channel, Binary data, void *dst);

    void cycle(uint8_t channel);

    void interrupt(uint8_t channel);

private:
    std::deque<DMA_Entry *> queues[4];
    DMA_Entry *busies[4] = {nullptr};
    std::deque<DMA_Entry *> unused = make_pool();
};

class DMA_Channel {
public:
    volatile uint32_t src;
    volatile uint32_t dst;
    volatile uint16_t cnt_l;
    volatile uint16_t cnt_h;
};

#define DMA ((volatile DMA_Channel *)0x040000B0)

#define DMA_REPEAT  (1 << 9)
#define TRANSFER_32 (1 << 10)
#define SPECIAL_START (3 << 12)
#define DMA_INT (1 << 14)
#define DMA_ON (1 << 15)

void dma_push(uint8_t channel, Binary data, void *dst);

#endif //GROOVEBOY_DMA_H
