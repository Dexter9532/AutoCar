#include <Wire.h>
#include <OPT3101.h>
#include <Arduino.h>

// Skapa ett sensorobjekt
OPT3101 sensor;

void setup() {
    Serial.begin(9600);
    Wire.begin();

    sensor.init();
    sensor.configureDefault();
}

void loop() {
    sensor.startSample();  // Starta en ny mätning
    delay(10);  // Vänta en kort stund

    while (!sensor.isSampleDone()) {
        delay(10);  // Vänta tills sensorn är klar
    }

    sensor.readOutputRegs();  // Läs ut mätdata

    Serial.println(sensor.distanceMillimeters);  // Endast avstånd skrivs ut

    delay(50);  // Vänta innan nästa mätning
}
