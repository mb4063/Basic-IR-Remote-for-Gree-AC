# GREE Air Conditioner Remote Control with Arduino

This project demonstrates how to control a GREE air conditioner (A/C) using an Arduino and an IR transmitter. The code integrates the `IRremoteESP8266` library for sending IR commands and the `ir_Gree` library for GREE-specific command formats. The air conditioner's state and settings can be adjusted using a simple analog sensor.

## Components

- Arduino board (e.g., Arduino Uno)
- IR Sender module
- Keypad (or you can use simple buttons)


## Libraries

- **IRremoteESP8266**: Library for sending and receiving IR signals with ESP8266 boards.
- **ir_Gree**: Library for encoding IR commands specific to GREE air conditioners.



### Setup

- Initializes the A/C and serial communication.
- Sets initial A/C settings (e.g., fan speed, mode, temperature).
- Prints the default state of the A/C to the serial monitor.

### Loop

- Continuously checks for button presses and updates the A/C settings based on the direction buttons (left, right, up, down).
- Toggles the A/C power state when the "select" button is pressed.

## Notes

- Ensure the IR LED is properly aligned with the A/C unit's IR receiver for effective communication.
- Adjust the `analogValue` thresholds in the `buttonPress()` function if needed based on your analog sensor's characteristics.

## Troubleshooting

- **IR Communication Issues**: Verify the IR LED connections and alignment. Ensure the A/C unit is in the line of sight of the IR LED.
- **Inconsistent Button Readings**: Calibrate the analog sensor or adjust the thresholds in the `buttonPress()` function.

Feel free to modify the code to suit your needs or to integrate additional features.
