#include "sensordata.hpp"
#include <Arduino.h>

// Konstruktor
SensorData::SensorData() {}

// Methode zum Initialisieren der Sensoren
void SensorData::begin() {
  // Nichts zu initialisieren für analoge Sensoren
}

// Methode zum Lesen der Sensoren
void SensorData::readSensors() {
  readAnalogSensors();
}

// Methode zur Serialisierung in JSON
String SensorData::toJSON() {
  StaticJsonDocument<200> doc;
  doc["moisture1"] = m_moisture1;
  doc["moisture2"] = m_moisture2;
  doc["moisture3"] = m_moisture3;

  String json;
  serializeJson(doc, json);
  return json;
}

// Private Methode zum Lesen der analogen Sensoren
void SensorData::readAnalogSensors() {
  m_moisture1 = analogRead(A0);
  m_moisture2 = analogRead(A1);
  m_moisture3 = analogRead(A2);
}
