
#include <Arduino.h>
#include "data_collector.hpp"
#include "hardware.hpp"
extern "C" {
  #include "twislave.h"
}


void setup() {
  // put your setup code here, to run once:
  pinMode(LEDB, OUTPUT); // Setzt den LED-Pin als Ausgang
  init_twi_slave((uint8_t)30);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LEDB, LOW);
  delay(100);
  digitalWrite(LEDB, HIGH);
  delay(100); 
}
