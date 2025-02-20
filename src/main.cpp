#include <Wire.h>
#include <OPT3101.h>
#include <Arduino.h>

// Motor A (ansluten till M1 på L298N)
int enA = 10;  // PWM-hastighet
int in1 = 9;   // Riktning
int in2 = 8;   // Riktning

void setup() {
  // Sätt motorpinnar som OUTPUT
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void demoOne() {
  // Kör motor A framåt med 200/255 hastighet
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 200);
  delay(2000);
}

void demoTwo() {
  // Accelerera motor A från 0 till full hastighet
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); // Kör bakåt
  for (int i = 0; i < 256; i++) {
    analogWrite(enA, i);
    delay(20);
  }

  // Bromsa ner från full fart till 0
  for (int i = 255; i >= 0; --i) {
    analogWrite(enA, i);
    delay(20);
  }

  // Stanna motorn
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void loop() {
  demoOne();
  delay(1000);
}
