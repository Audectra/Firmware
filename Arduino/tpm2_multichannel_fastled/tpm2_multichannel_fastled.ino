/*
 * Simple TPM2 Firmware for Arduino/Teensy boards
 * Multi-Channel with FastLED Library (for addressable LEDs)
 * 
 * Author:    Dipl.-Ing. Phillip Djurdjevic, Audectra e.U.
 * Version:   v1.0.0
 * Date:      02.06.2018
 * 
 * Feel free to use and modify to your liking! =)
 */

#include <FastLED.h>

// Channel Pin Configuration
#define CH1PIN 4
#define CH2PIN 6

// Channel Size Configuration
#define CH1PIXELS 16*16
#define CH2PIXELS 16*16

// Channel Data Arrays
CRGB ch1Array[CH1PIXELS];
CRGB ch2Array[CH2PIXELS];

void setup()
{
  // Teensy always uses full speed, independet of the baud rate specified here.
  Serial.begin(1250000);

  // Assign all Channels
  FastLED.addLeds<NEOPIXEL, CH1PIN>(ch1Array, CH1PIXELS);
  FastLED.addLeds<NEOPIXEL, CH2PIN>(ch2Array, CH2PIXELS);
}

void ReadChannelData(CRGB* channelArray, unsigned int numLeds)
{
  char buffer[3];
  
  for (unsigned int i = 0; i < numLeds; i++)
  {
    while(Serial.available() < 3);
    Serial.readBytes(buffer, 3);
    channelArray[i] = CRGB((unsigned char)buffer[0], (unsigned char)buffer[1], (unsigned char)buffer[2]);
  }
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

        // Read all channel data
        ReadChannelData(ch1Array, CH1PIXELS);
        ReadChannelData(ch2Array, CH2PIXELS);

        data = Serial.read(); // TPM2 Frame End

        // Applay channel data to LEDs
        FastLED.show();
      }
    }
  }
}

