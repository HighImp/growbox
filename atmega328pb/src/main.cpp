
#include <Arduino.h>
#include "hardware.hpp"
#include <SPI.h>
#include "sensordata.hpp"
extern "C" {
  #include "spi_slave.h"
  #include "fifo.h"
}


uint8_t count;
uint8_t sleep_time = 10;
JsonDocument doc;
char char_buffer[FIFO_BUFFER_SIZE];
SensorData sensorData;

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDB, OUTPUT); // Setzt den LED-Pin als Ausgang
  init_slave_spi();
  SPI.attachInterrupt();  //allows SPI interrupt
  pinMode(MISO, OUTPUT);
}


void loop() {
    sprintf(char_buffer, "%d", analogRead(A0));
    write_spi(strlen(char_buffer)+1, (uint8_t*)char_buffer);
    digitalWrite(LEDB, HIGH); 
    delay(300);
    digitalWrite(LEDB, LOW);
    delay(300);
}
