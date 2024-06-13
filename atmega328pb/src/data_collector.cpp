#include "data_collector.hpp"
#include <SPI.h>
#include <Arduino.h> // Für die Pin-Funktionen
#include <Arduino_JSON.h> // JSON-Bibliothek
#include <DHT.h>

DataCollector::DataCollector() {
    m_dht1 = &DHT(HUM1, DHT22); 
    m_dht2 = &DHT(HUM1, DHT22);
}

void DataCollector::begin() {
    m_dht1->begin();
    m_dht2->begin();
    SPI.begin();
    pinMode(LEDA, OUTPUT); // Setzt den LED-Pin als Ausgang
}

void DataCollector::collectData() {
    digitalWrite(LEDA, HIGH); // LED einschalten

    readAnalogValues();
    readDHTValues();
    processData();

    digitalWrite(LEDA, LOW); // LED ausschalten
}

void DataCollector::transmitData() {
    // JSON-Dokument erstellen
    JSONVar jsonDoc;
    jsonDoc["analogValue1"] = m_analogValue1;
    jsonDoc["analogValue2"] = m_analogValue2;
    jsonDoc["analogValue3"] = m_analogValue3;
    jsonDoc["temperature1"] = m_temperature1;
    jsonDoc["humidity1"] = m_humidity1;
    jsonDoc["temperature2"] = m_temperature2;
    jsonDoc["humidity2"] = m_humidity2;

    // JSON-String serialisieren
    String jsonString = JSON.stringify(jsonDoc);

    // JSON-String über SPI senden
    sendJsonString(jsonString);
}

void DataCollector::sendJsonString(const String& jsonString) {
    for (size_t i = 0; i < jsonString.length(); ++i) {
        SPI.transfer(jsonString[i]);
    }
    // Nullterminator senden, um das Ende des Strings zu markieren
    SPI.transfer('\0');
}

void DataCollector::readAnalogValues() {
    m_analogValue1 = analogRead(SOIL1);
    m_analogValue2 = analogRead(SOIL2);
    m_analogValue3 = analogRead(SOIL3);
}

void DataCollector::readDHTValues() {
    m_temperature1 = m_dht1->readTemperature();
    m_humidity1 = m_dht1->readHumidity();
    m_temperature2 = m_dht2->readTemperature();
    m_humidity2 = m_dht2->readHumidity();
}

void DataCollector::processData() {
    // Verrechnung der Analogwerte oder andere spezifische Berechnungen
    // Zum Beispiel eine einfache Multiplikation der Werte:
    m_analogValue1 = m_analogValue1 * 2;
    m_analogValue2 = m_analogValue2 * 3;
    m_analogValue3 = m_analogValue3 * 4;
}
