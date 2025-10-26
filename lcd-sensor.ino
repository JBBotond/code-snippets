/*
  MIC1 Week 5. Sensors and Actuators 1

  Author Janosi Barna-Botond
         2170302
  Date   03/10/2025
*/

// Include the LCD library
// Must use A4 for SDA and A5 for SCL
#include <lcd16x2_i2c.h>

// Associate the HC-SR04 sensor pins with the arduino pins
const int trigPin = 6;
const int echoPin = 7;

// Previous values
unsigned long previousMillis = 0;

// Interval at which to measure the Ping sensor
unsigned long interval = 100;

//up to 16 characters displayed

//array to represent characters
int bar[16] = {0};
//0 represents a space
const int space = 0;
//1 represents a square
const int square = 1;
//2 represents a slash
const int slash = 2;

//constant to represent bar size
const int barSize = 16;

void setup() {

  // Setup HC-SR04 pins
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);

  // Initialize the LCD
  lcd_init();
  lcd_backlight(on);
  lcd_set_cursor(0, 0);
  lcd_put("MIC1 Week 5");
}

void loop() {

  // --------------------------------------------------------------------------

  // Check to see if the interval has passed
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Save the current time so it can be used to calculate if the has passed
    previousMillis = currentMillis;

    // Create a 10 microsecond pulse to trigger the sensor
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure the pulse returned by the sensor
    // Set timeout to 10 ms = 10.000 microseconds
    
    //            ! this line is gold for project
    unsigned long duration = pulseIn(echoPin, HIGH, 10000);

    lcd_set_cursor(0, 1);

    // Check validity of the measured value
    if (duration == 0) {
      // Notify user of invalid measurement
      lcd_put("Distance invalid");
    } else {
      // Calculate the distance in cm
      int distance_cm = duration * 0.034 / 2;
      //if distance fits in the bar
      if(barSize - distance_cm > 0) {
        for(int i = 0; i < distance_cm; i++) {
          bar[i] = square;
        }
        bar[distance_cm] = slash;
        //if there is space left
        for(int i = distance_cm + 1; i < barSize; i++) {
          bar[i] = space;
        }
      }
      //distance is 16 or more
      else {
        for(int i = 0: i < barSize - 1; i++)
          bar[i] = square;
        bar[barSize -1] = slash;
      }
      //function to output bar goes here
      for(int i = 0; i < barSize; i++) {
        switch(bar[i]) {
          case space: 
            lcd_put(" ");
            break;
          case square:
            lcd_put("#");
            break;
          case slash:
            lcd_put("|");
            break;
        }
      }
    }
  }
}
