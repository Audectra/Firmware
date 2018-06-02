# Firmware

This repository is collection of firmware source codes, which you can use to jump start on your Audectra project. Alternatively, you can use a normal TPM2 controller, which is compatible with our strips. However, having the ability to change the firmware, makes your project even more customizable.

## Requirements

You need to install the [Arduino IDE](https://www.arduino.cc/en/Main/Software) to be able to compile the Arduino projects. If you have a Teensy board, then you additionally need the [Teensy Addon](https://www.pjrc.com/teensy/teensyduino.html) for the Arduino IDE.

## Arduino/Teensy Firmware

The folder "Arduino" contains a collection of firmware source codes for Arduino and Teensy boards.

### TPM2 Single-Channel with PWM

If you are upgrading to Audectra v2 and still want to control your non-addressable strips or panels with PWM, this might be the best base firmware to start off. 

### TPM2 Multi-Channel with FastLED

If you are eager to control addressable LEDs with Audectra, then this might be the bast starting point for your firmware.

