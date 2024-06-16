#include "fifo.h"

void initFIFO(FIFOBuffer *fifo) {
    fifo->head = 0;
    fifo->tail = 0;
    fifo->count = 0;
}

bool writeFIFO(FIFOBuffer *fifo, uint8_t data) {
    if (fifo->count == FIFO_BUFFER_SIZE) {
        // Buffer is full
        return false;
    }
    fifo->buffer[fifo->head] = data;
    fifo->head = (fifo->head + 1) % FIFO_BUFFER_SIZE;
    fifo->count++;
    return true;
}

bool readFIFO(FIFOBuffer *fifo, uint8_t *data) {
    if (fifo->count == 0) {
        // Buffer is empty
        return false;
    }
    *data = fifo->buffer[fifo->tail];
    fifo->tail = (fifo->tail + 1) % FIFO_BUFFER_SIZE;
    fifo->count--;
    return true;
}
