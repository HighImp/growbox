#ifndef SPI_SLAVE_H
#define SPI_SLAVE_H

#include <stdint.h>


void init_slave_spi();
uint8_t write_spi(uint8_t size, uint8_t* data);
uint8_t read_spi(uint8_t max_size, uint8_t* data);


#endif // SPI_SLAVE_H
