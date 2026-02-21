#include "dma.h"
#include "int.h"

#include <cstdlib>

static DMA_Controller DMAC;

void DMA_Controller::push(const uint8_t channel, void *src, void *dst, const uint16_t cnt) {
    if (unused.empty()) {
        return;
    }
    DMA_Entry *entry = unused.front();
    unused.pop_front();
    entry->src = src;
    entry->dst = dst;
    entry->cnt = cnt;
    this->queues[channel].push_back(entry);
    if (!this->busies[channel]) {
        cycle(channel);
    }
}

void DMA_Controller::cycle(const uint8_t channel) {
    if (this->queues[channel].empty()) {
        return;
    }
    DMA_Entry *entry = this->queues[channel].front();
    this->queues[channel].pop_front();
    this->busies[channel] = entry;
    DMA[channel].cnt_h = 0;
    DMA[channel].src = reinterpret_cast<intptr_t>(entry->src);
    DMA[channel].dst = reinterpret_cast<intptr_t>(entry->dst);
    DMA[channel].cnt_l = entry->cnt >> 1; // TRANSFER_16
    DMA[channel].cnt_h = 0 | DMA_INT | DMA_ON;
}

void DMA_Controller::interrupt(const uint8_t channel) {
    if (!this->busies[channel]) {
        return;
    }
    this->unused.push_back(this->busies[channel]);
    this->busies[channel] = nullptr;
    cycle(channel);
}

void dma_push(const uint8_t channel, void* src, void* dst, const uint16_t cnt) {
    DMAC.push(channel, src, dst, cnt);
}

void dma_interrupt(const uint8_t channel) {
    DMAC.interrupt(channel);
}
