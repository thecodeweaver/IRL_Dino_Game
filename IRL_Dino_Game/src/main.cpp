#include <Arduino.h>
#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 gyro(Wire);

void setup() 
{
    Serial.begin(9600);
    Wire.begin();
  
    // Connect to gyro
    byte gyro_status = gyro.begin();
    
    if (gyro_status != 0)
    {
        Serial.println("Error: Unable to connect to gyro...halting...");
        while (1) { } // Infite loop if unable to connect to gyro (no point in continuing)
    }

    // Blink LED 3 times to indicate gyro calibration beginning
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        delay(1000);
    }

    // Calibrate gyro
    Serial.print("Calibrating gyro...");
    digitalWrite(LED_BUILTIN, HIGH); // Turn LED on while calibrating
    gyro.calcOffsets(true, true);
    digitalWrite(LED_BUILTIN, LOW); // Turn LED off when calibrating completes
    Serial.println("Done.");
}

void loop()
{
    // Print the accelerometer data for the Z access every 250ms
    gyro.update();
    Serial.print("Y Axis Accel: ");
    Serial.println(gyro.getAccY());
    delay(250);
}