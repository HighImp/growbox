#ifndef DATA_COLLECTOR_H
#define DATA_COLLECTOR_H

#include <DHT.h>
#include "hardware.hpp"

class DataCollector {
public:
    DataCollector();
    void begin();
    void collectData();
    void transmitData();

private:
    int m_analogValue1;
    int m_analogValue2;
    int m_analogValue3;
    float m_temperature1;
    float m_humidity1;
    float m_temperature2;
    float m_humidity2;
    DHT *m_dht1;
    DHT *m_dht2;

    void readAnalogValues();
    void readDHTValues();
    void processData();
    void sendJsonString(const String& jsonString);
};

#endif
