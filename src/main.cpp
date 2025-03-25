#include <Servo.h>
#include <Wire.h>
#include <OPT3101.h>
#include <Arduino.h>

// === PIN-KONFIGURATION ===
#define L_EN 8    
#define R_EN 7   
#define L_PWM 5   
#define R_PWM 6   
#define SERVO_PIN 9

// === OBJEKT ===
Servo steeringServo;
OPT3101 sensor;

// === KONSTANTER ===
const int targetDistance = 400;     // önskat avstånd till sargen
const int tolerance = 20;           // tillåtet fel (mm)
const int maxDeviation = 200;       // max fel vi bryr oss om
const int maxSpeed = 51;            // max PWM till motor
const int minSpeed = 50;            // min PWM

void setup() {
    Serial.begin(9600);             // starta serial monitor
    Wire.begin();                   // starta I2C

    sensor.init();                  // initiera sensorn
    sensor.configureDefault();      // standardinställningar

    steeringServo.attach(SERVO_PIN); 
    steeringServo.write(85);        // mittläge på servo

    pinMode(L_EN, OUTPUT);
    pinMode(R_EN, OUTPUT);
    pinMode(L_PWM, OUTPUT);
    pinMode(R_PWM, OUTPUT);

    digitalWrite(L_EN, HIGH);       // slå på motorerna
    digitalWrite(R_EN, HIGH);
}

void loop() {
    // === MÄT MED OTP3101 ===
    sensor.startSample();

    while (!sensor.isSampleDone()) delay(1);
    sensor.readOutputRegs();
    int distance = sensor.distanceMillimeters;

    Serial.print("Avstånd: ");
    Serial.println(distance);

    // === BERÄKNA FEL OCH SERVOSTYRNING ===
    int error = targetDistance - distance;
    int angle = 85;  // rakt fram

    if (abs(error) < tolerance) {
        angle = 85;
    } else if (error > 0) {
        // för långt från väggen → styr vänster
        angle = 85 + map(constrain(error, 0, maxDeviation), 0, maxDeviation, 0, 25);
    } else {
        // för nära väggen → styr höger
        angle = 85 - map(constrain(-error, 0, maxDeviation), 0, maxDeviation, 0, 25);
    }

    angle = constrain(angle, 50, 120); // begränsa servo
    steeringServo.write(angle);       // skicka till servon

    // === BERÄKNA HASTIGHET BASERAT PÅ FEL ===
    int absError = abs(error);
    absError = constrain(absError, 0, maxDeviation);
    int speed = map(absError, 0, maxDeviation, maxSpeed, minSpeed);
    speed = constrain(speed, minSpeed, maxSpeed);

    analogWrite(R_PWM, speed);
    analogWrite(L_PWM, 0);  // bara höger motor går
}
