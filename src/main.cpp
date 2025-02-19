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
    delay(1);  // Vänta en kort stund

    while (!sensor.isSampleDone()) {
        delay(1);  // Vänta tills sensorn är klar
    }

    sensor.readOutputRegs();  // Läs ut mätdata

    int distance = sensor.distanceMillimeters;  // Spara avståndet i en variabel
    Serial.println(distance);  // Skriv ut avståndet

    delay(1);  // Vänta innan nästa mätning
}
