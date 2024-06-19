#ifndef SENSORDATA_HPP
#define SENSORDATA_HPP

#include <ArduinoJson.h>

class SensorData {
  public:
    float m_moisture1;
    float m_moisture2;
    float m_moisture3;

    // Konstruktor
    SensorData();

    // Methode zum Initialisieren der Sensoren
    void begin();

    // Methode zum Lesen der Sensoren
    void readSensors();

    // Methode zur Serialisierung in JSON
    String toJSON();

  private:
    void readAnalogSensors();
};

#endif // SENSORDATA_HPP
