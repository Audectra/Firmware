/*
 * Simple TPM2 Firmware for Arduino/Teensy boards
 * Single-Channel with PWM control (for non-addressable LEDs)
 * 
 * Author:    Dipl.-Ing. Phillip Djurdjevic, Audectra e.U.
 * Version:   v1.0.0
 * Date:      02.06.2018
 * 
 * Feel free to use and modify to your liking! =)
 */

// If you were following our Easy DIY Audectra Setup,
// you might need to turn on the output inversion:
const char InvertOutput = 0;  // = 1; If inversion is needed.

// Don't forget to change the pins according to your setup!
// These pins must be PWM(/Analog) Output pins.
int pinBlue = 2;
int pinGreen = 3;
int pinRed = 4;

void setup()
{
  pinMode(pinBlue, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinRed, OUTPUT);

  analogWrite(pinBlue, Inversion(0));    // Blue
  analogWrite(pinGreen, Inversion(0));    // Green
  analogWrite(pinRed, Inversion(0));    // Red
    
  // Teensy always uses full speed, independet of the baud rate specified here.
  Serial.begin(1250000);
}

unsigned int Inversion(unsigned int value)
{
  if (InvertOutput == 0)
    return value;
  else
    return (255 - value);
}

void loop()
{
  if (Serial.available())
  {
    unsigned char data = Serial.read();

    if (data == 0xC9) // TPM2 Frame Start
    {
      while(!Serial.available());
      data = Serial.read();

      if (data == 0xDA) // TPM2 Frame Type - Data
      {
        char buffer[3];
        while(Serial.available() < 2);
        Serial.readBytes(buffer, 2);  // TPM2 Frame Size

        // Read RGB Data
        while(Serial.available() < 3);
        Serial.readBytes(buffer, 3);

        // Apply new Color
        analogWrite(pinRed, Inversion(buffer[0]));    // Red
        analogWrite(pinGreen, Inversion(buffer[1]));    // Green
        analogWrite(pinBlue, Inversion(buffer[2]));    // Blue

        data = Serial.read(); // TPM2 Frame End
      }
    }
  }
}

