#ifndef FIFO_H
#define FIFO_H

#include <stdint.h>
#include <stdbool.h>

#define FIFO_BUFFER_SIZE 50

typedef struct {
    uint8_t buffer[FIFO_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t count;
} FIFOBuffer;

void initFIFO(FIFOBuffer *fifo);
bool writeFIFO(FIFOBuffer *fifo, uint8_t data);
bool readFIFO(FIFOBuffer *fifo, uint8_t *data);
void printBuffer(FIFOBuffer *fifo);

#endif // FIFO_H
