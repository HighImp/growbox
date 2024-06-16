
#include <Arduino.h>
#include "data_collector.hpp"
#include "hardware.hpp"
#include <SPI.h>
extern "C" {
  #include "spi_slave.h"
}


uint8_t count;
uint8_t sleep_time = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDB, OUTPUT); // Setzt den LED-Pin als Ausgang
  init_slave_spi();
  SPI.attachInterrupt();  //allows SPI interrupt
  pinMode(MISO, OUTPUT);
}

void loop() {
  
  //digitalWrite(MISO, (digitalRead(MOSI)));
  
  char* text = "Finaly Done";
  
  write_spi(strlen(text), (uint8_t*)text);

  while (!write_spi(1, &count)){
      digitalWrite(LEDB, LOW);
  }

  digitalWrite(LEDB, LOW);
  delay(10);
  digitalWrite(LEDB, HIGH);
  delay(1000); 
  count++;
}
