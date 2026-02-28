#include "dma.h"
#include "int.h"

#include <cstdlib>

static DMA_Controller DMAC;

void DMA_Controller::push(const uint8_t channel, const Binary data, intptr_t dst) {
    if (unused.empty()) {
        return;
    }
    DMA_Entry *entry = unused.front();
    unused.pop_front();
    entry->data = data;
    entry->dst = dst;
    entry->inc_src = true;
    this->queues[channel].push_back(entry);
    if (!this->busies[channel]) {
        cycle(channel);
    }
}

void DMA_Controller::zero(const uint8_t channel, const uint16_t size, const intptr_t dst) {
    if (unused.empty()) {
        return;
    }
    DMA_Entry *entry = unused.front();
    unused.pop_front();
    entry->data = Binary(nullptr, size);
    entry->dst = dst;
    entry->inc_src = false;
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
    DMA[channel].src = reinterpret_cast<intptr_t>(entry->data.start);
    DMA[channel].dst = entry->dst;
    DMA[channel].cnt_l = entry->data.size >> 1; // TRANSFER_16
    if (entry->inc_src) {
        DMA[channel].cnt_h |= DMA_SRC_INC;
    }
    DMA[channel].cnt_h |= DMA_INT | DMA_ON;
}

void DMA_Controller::interrupt(const uint8_t channel) {
    if (!this->busies[channel]) {
        return;
    }
    this->unused.push_back(this->busies[channel]);
    this->busies[channel] = nullptr;
    cycle(channel);
}

void dma_push(const uint8_t channel, const Binary data, const intptr_t dst) {
    DMAC.push(channel, data, dst);
}

void dma_zero(const uint8_t channel, const uint16_t size, const intptr_t dst) {
    DMAC.zero(channel, size, dst);
}

void dma_interrupt(const uint8_t channel) {
    DMAC.interrupt(channel);
}
