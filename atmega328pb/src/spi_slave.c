#include "fifo.h"
#include <Arduino.h>



FIFOBuffer spi_rx_fifo;
FIFOBuffer spi_tx_fifo;


void init_slave_spi(){
    pinMode(SS, INPUT);
    pinMode(MISO, OUTPUT);
    pinMode(MOSI, INPUT);
    pinMode(SCK, INPUT);
    SPCR |= _BV(SPE);
    initFIFO(&spi_rx_fifo);
    initFIFO(&spi_tx_fifo);
}

uint8_t write_spi(uint8_t size, uint8_t* data){
    int i;
    for(i=0; i<size; i++){
        if(!writeFIFO(&spi_tx_fifo, data[i])){
            //fifo was full during write
            return false;
        }
    }
    return true;
}

uint8_t read_spi(uint8_t max_size, uint8_t* data){
    uint8_t read_count = 0;
    while (read_count < max_size)
    {
        if(!readFIFO(&spi_rx_fifo, data[read_count])){
            return read_count;
        }
        read_count++;
    }
    return read_count;
}


ISR (SPI_STC_vect)   //Interrput routine function
{
  uint8_t data = SPDR;
  writeFIFO(&spi_rx_fifo, data);
  if(readFIFO(&spi_tx_fifo, &data)){
    SPDR = data;
  }
}

