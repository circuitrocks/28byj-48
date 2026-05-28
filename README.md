# 28BYJ-48 — 5V geared stepper motor (with ULN2003)

Sample sketch for the **[28BYJ-48 Stepper Motor + ULN2003 Driver Board](https://circuit.rocks/products/28byj-48-high-quality-stepper-motor-12v)**, sold by [Circuitrocks](https://circuit.rocks/).

This example rotates the motor one full turn clockwise, then one full turn counter-clockwise, using the built-in Arduino `Stepper` library — **no external library required**.

## What you need

- 1x 28BYJ-48 stepper motor with ULN2003 driver board (typically sold together)
- 1x Arduino Uno (or compatible)
- 1x external 5 V supply (battery pack or 5 V wall adapter, ≥ 500 mA)
- Jumper wires

## Wiring

| ULN2003 board | Arduino Uno pin |
|---------------|-----------------|
| IN1           | D8              |
| IN2           | D9              |
| IN3           | D10             |
| IN4           | D11             |
| `+`           | External 5V     |
| `–`           | External GND (also wired to Arduino GND) |

> **Don't power the motor from the Arduino's 5 V pin.** The 28BYJ-48 can pull ~240 mA while moving, and surges higher on each step. The Arduino's USB power can't reliably supply that — you'll brown out the board and get random resets. Use a separate supply, and connect its GND to the Arduino's GND.

## How to use

1. Open `28byj-48.ino` in the Arduino IDE.
2. Select **Tools → Board → Arduino Uno** and the correct COM port.
3. Click **Upload**.
4. Connect the external supply to the ULN2003 board.
5. The motor turns one revolution clockwise, pauses, then one revolution counter-clockwise. Repeats forever.

## How it works

- The 28BYJ-48 has 64:1 internal gearing. The Arduino `Stepper` library, configured for 2048 steps per revolution of the output shaft, drives the motor in full-step mode.
- Pin order in `Stepper(steps, in1, in3, in2, in4)` is intentionally swapped (IN1, IN3, IN2, IN4 — not IN1, IN2, IN3, IN4). This matches the coil energization sequence the ULN2003 board uses.

## Notes

- **Speed**: max practical RPM is ~15 with the default Stepper library. For faster motion, use the `AccelStepper` library and half-step the coils.
- **Holding torque**: the motor stays energized after a `step()` call, drawing current and heating up. To save power between movements, call `digitalWrite()` to drive all 4 IN pins LOW.
- **5V vs 12V models**: the standard 28BYJ-48 is the 5 V version. A 12 V version exists with the same form factor — check the label. Wrong voltage either stalls (12 V motor on 5 V) or burns out the windings (5 V motor on 12 V).

## Datasheet

[28BYJ-48 datasheet & pinout (docs.circuit.rocks)](https://docs.circuit.rocks/motors/28byj-48/)

## Troubleshooting

- **Motor vibrates but doesn't rotate** — coil sequence is wrong. Double-check the pin order in the `Stepper()` constructor matches IN1, IN3, IN2, IN4 (not IN1, IN2, IN3, IN4).
- **Arduino resets when motor starts moving** — power supply is too weak or you're powering the motor from the Arduino. Use a separate supply.
- **Motor turns wrong direction** — swap `STEPS_PER_REV` for `-STEPS_PER_REV` in `loop()`, or swap any two adjacent pins.
- **One LED on the ULN2003 doesn't light up** — that channel is dead. The board may need replacement, but the motor itself is fine.

## License

MIT — see [LICENSE](LICENSE).

## Got stuck?

Drop by [circuit.rocks](https://circuit.rocks/) — happy to help our customers get their modules working.
