/*
 * 28BYJ-48 Stepper Motor Demo (with ULN2003 driver board)
 * --------------------------------------------------------
 * Rotates the 28BYJ-48 geared stepper motor one full turn clockwise,
 * then one full turn counter-clockwise. Uses the built-in Arduino
 * Stepper library — no external library required.
 *
 * Target board: Arduino Uno (or any Arduino)
 * Wiring (ULN2003 driver board → Arduino):
 *   ULN2003 IN1 -> Arduino D8
 *   ULN2003 IN2 -> Arduino D9
 *   ULN2003 IN3 -> Arduino D10
 *   ULN2003 IN4 -> Arduino D11
 *   ULN2003 +   -> external 5V supply (motor draws up to ~240 mA — DON'T
 *                  power from the Arduino's 5V pin, you'll brown-out the board)
 *   ULN2003 -   -> external supply GND (shared with Arduino GND)
 *
 * (c) 2026 Circuitrocks. Released under the MIT License.
 * https://github.com/circuitrocks
 */

#include <Stepper.h>

// 28BYJ-48 has 64:1 internal gearing. In full-step mode the Arduino
// Stepper library treats one revolution of the OUTPUT shaft as 2048 steps
// (32 steps per electrical rev * 64 gear ratio).
const int STEPS_PER_REV = 2048;

// Stepper library expects the pins in the order IN1, IN3, IN2, IN4 for
// the ULN2003 board to produce the correct full-step sequence.
Stepper stepper(STEPS_PER_REV, 8, 10, 9, 11);

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(10);   // RPM (motor maxes out around 15 RPM)
  Serial.println(F("28BYJ-48 demo: 1 turn CW, 1 turn CCW, repeat."));
}

void loop() {
  Serial.println(F("Forward 1 revolution..."));
  stepper.step(STEPS_PER_REV);
  delay(500);

  Serial.println(F("Backward 1 revolution..."));
  stepper.step(-STEPS_PER_REV);
  delay(500);
}
