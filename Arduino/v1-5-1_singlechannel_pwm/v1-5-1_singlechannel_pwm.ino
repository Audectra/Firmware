/*
 * Simple Firmware for Arduino/Teensy boards with Audectra v1.5.1
 * Single-Channel with PWM control (for non-addressable LEDs)
 * 
 * Author:    Dipl.-Ing. Phillip Djurdjevic, Audectra e.U.
 * Version:   v1.2.0
 * Date:      08.06.2018
 * 
 * Feel free to use and modify to your liking! =)
 */

// If you were following our Easy DIY Audectra Setup,
// you might need to turn on the output inversion:
const char InvertOutput = 0;	// = 1; If inversion is needed.

// Don't forget to change the pins according to your setup!
// These pins must be PWM(/Analog) Output pins.
int pinBlue = 2;
int pinGreen = 3;
int pinRed = 4;

// ! Do not change following section ->
const char* ID = "DIYAudectra";
const char* FirmwareVersion = "1.2.0";

enum AudectraCommands {
    IDENTIFY = 1,
};

enum ControllerCommands {
    CHANGE_BRIGHTNESS = 1,
    CHANGE_MODE,
    CHANGE_STATIC_COLOR
};

enum AudectraMode
{
    MODE_NONE = 0,
    MODE_STATIC,
    MODE_BAND,
    MODE_INTENSITY,
    MODE_BEAT,
    MODE_COMBINED,
    MODE_RAINBOW
};

unsigned int Inversion(unsigned int value)
{
	if (InvertOutput == 0)
		return value;
	else
		return (255 - value);
}

void ChangeBrightness (unsigned char brightness)
{
    unsigned char buffer[2];
    
    buffer[0] = CHANGE_BRIGHTNESS;
    buffer[1] = brightness;
    
    Serial.write(buffer, 2);
    return;
}

void ChangeMode (int mode)
{
    unsigned char buffer[2];
    
    buffer[0] = CHANGE_MODE;
    buffer[1] = mode;
    
    Serial.write(buffer, 2);
    return;
}

void ChangeStaticColor (unsigned char R, unsigned char G, unsigned char B)
{
    unsigned char buffer[4];
    
    buffer[0] = CHANGE_STATIC_COLOR;
    buffer[1] = R;
    buffer[2]= G;
    buffer[3] = B;
    
    Serial.write(buffer, 4);
    return;
}
// <- Do not change this section !

void setup()
{
    pinMode(pinBlue, OUTPUT);
    pinMode(pinGreen, OUTPUT);
    pinMode(pinRed, OUTPUT);
  
    analogWrite(pinBlue, Inversion(0));  	// Blue
    analogWrite(pinGreen, Inversion(0));  	// Green
    analogWrite(pinRed, Inversion(0));  	// Red

    Serial.begin(9600);
}

void loop()
{  
  if (Serial.available() >= 4)
  {
    unsigned char buffer[4];
    
    for (int i = 0; i < 4; i++)
      buffer[i] = '\0';
      
    Serial.readBytes(buffer, 4);
    
    switch (buffer[0])
    {
      case IDENTIFY:
        Serial.println(ID);
        Serial.println(FirmwareVersion);
        
        // Example of setting Brightness to 50% on Startup.
        // ChangeBrightness(255);
        
        // Example of setting static color on Startup.
        // ChangeStaticColor(0, 255, 0);
        
        // Example of setting Audectra Mode on Startup.
        // ChangeMode(MODE_STATIC);
        break;
        
      default:
        break;
    }
    
    analogWrite(pinBlue, Inversion(buffer[3]));  	// Blue
    analogWrite(pinGreen, Inversion(buffer[2]));  	// Green
    analogWrite(pinRed, Inversion(buffer[1]));  	// Red
  }
}
