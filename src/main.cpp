#include <Arduino.h>

// Definiera motorstyrning
#define L_EN 8    // Aktivera vänster kanal
#define R_EN 7   // Aktivera höger kanal
#define L_PWM 5   // PWM för vänster rotation (bakåt)
#define R_PWM 6   // PWM för höger rotation (framåt)

void setup() {
    // Ställ in motorpinnar
    pinMode(L_EN, OUTPUT);
    pinMode(R_EN, OUTPUT);
    pinMode(L_PWM, OUTPUT);
    pinMode(R_PWM, OUTPUT);

    // Aktivera båda kanalerna
    digitalWrite(L_EN, HIGH);
    digitalWrite(R_EN, HIGH);
}

void loop() {
    int speed = 50; // PWM-hastighet (0-255)

    // Kör framåt i 3 sekunder
    analogWrite(R_PWM, speed);
    analogWrite(L_PWM, 0);
    delay(3000);

    // Stanna i 1 sekund
    analogWrite(R_PWM, 0);
    analogWrite(L_PWM, 0);
    delay(1000);

    // Kör bakåt i 3 sekunder
    analogWrite(R_PWM, 0);
    analogWrite(L_PWM, speed);
    delay(3000);

    // Stanna i 1 sekund
    analogWrite(R_PWM, 0);
    analogWrite(L_PWM, 0);
    delay(1000);

    // Snabbt ryck framåt (0.5s)
    analogWrite(R_PWM, speed);
    analogWrite(L_PWM, 0);
    delay(500);

    // Snabbt ryck bakåt (0.5s)
    analogWrite(R_PWM, 0);
    analogWrite(L_PWM, speed);
    delay(500);

    // Stanna innan loopen startar om
    analogWrite(R_PWM, 0);
    analogWrite(L_PWM, 0);
    delay(1000);
}
