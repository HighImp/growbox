
#include <Arduino.h>
#include "data_collector.hpp"
#include "hardware.hpp"



void setup() {
  // put your setup code here, to run once:
  pinMode(LEDB, OUTPUT); // Setzt den LED-Pin als Ausgang
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LEDB, LOW);
  delay(100);
  digitalWrite(LEDB, HIGH);
  delay(100); 
}
