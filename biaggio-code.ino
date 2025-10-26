#include <avr/io.h>
#include <util/delay.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 20, 4); 

// Pins for Motor A
#define MOTOR_A_IN1 8 //PB0
#define MOTOR_A_IN2 11 //PB3
#define MOTOR_A_ENA 9 //PB1

#define MOTOR_B_IN3 12 //PB4 
#define MOTOR_B_IN4 13 //PB5
#define MOTOR_B_ENB 10//PB2


#define TRIGGER_PIN_F 2 //PD2
#define ECHO_PIN_F    3 //PD3
#define TRIGGER_PIN_B 4 //PD4
#define ECHO_PIN_B    5 //PD5

float distance_cm(uint8_t TRIGGER_PIN, uint8_t ECHO_PIN) {
   digitalWrite(TRIGGER_PIN, LOW);
   delayMicroseconds(4);
   digitalWrite(TRIGGER_PIN, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIGGER_PIN, LOW);
   long duration = pulseIn(ECHO_PIN, HIGH);
   float distance = duration / 58.0;
   return distance;
}

void setup() {
 Serial.begin(9600);
 pinMode(TRIGGER_PIN_F, OUTPUT);
 pinMode(ECHO_PIN_F, INPUT);
 pinMode(TRIGGER_PIN_B, OUTPUT);
 pinMode(ECHO_PIN_B, INPUT);

 pinMode(MOTOR_A_IN1, OUTPUT);
 pinMode(MOTOR_A_IN2, OUTPUT);
 pinMode(MOTOR_A_ENA, OUTPUT);
 pinMode(MOTOR_B_IN3, OUTPUT);
 pinMode(MOTOR_B_IN4, OUTPUT);
 pinMode(MOTOR_B_ENB, OUTPUT);


 digitalWrite(MOTOR_A_IN1, LOW); digitalWrite(MOTOR_A_IN2, LOW); analogWrite(MOTOR_A_ENA, 0); 
 digitalWrite(MOTOR_B_IN3, LOW); digitalWrite(MOTOR_B_IN4, LOW); analogWrite(MOTOR_B_ENB, 0); 

 lcd.init();
 lcd.backlight();


}


//Motor A
void motorA_forward(int speed) {
 digitalWrite(MOTOR_A_IN1, LOW);
 digitalWrite(MOTOR_A_IN2, HIGH);
 analogWrite(MOTOR_A_ENA, speed);
}

void motorA_backward(int speed) {
 digitalWrite(MOTOR_A_IN1, HIGH);
 digitalWrite(MOTOR_A_IN2, LOW);
 analogWrite(MOTOR_A_ENA, speed);
}

void motorA_stop() {
 digitalWrite(MOTOR_A_IN1, LOW);
 digitalWrite(MOTOR_A_IN2, LOW);
 analogWrite(MOTOR_A_ENA, 0);
}


// Motor B
void motorB_forward(int speed) {
 digitalWrite(MOTOR_B_IN3, LOW);
 digitalWrite(MOTOR_B_IN4, HIGH);
 analogWrite(MOTOR_B_ENB, speed);
}
void motorB_backward(int speed) {
 digitalWrite(MOTOR_B_IN3, HIGH);
 digitalWrite(MOTOR_B_IN4, LOW);
 analogWrite(MOTOR_B_ENB, speed);
}
void motorB_stop() {
 digitalWrite(MOTOR_B_IN3, LOW);
 digitalWrite(MOTOR_B_IN4, LOW);
 analogWrite(MOTOR_B_ENB, 0);
}


void loop() {
  float dist_f = distance_cm(TRIGGER_PIN_F, ECHO_PIN_F);
  delay(60);
  float dist_b = distance_cm(TRIGGER_PIN_B, ECHO_PIN_B);
  delay(60);

  int speed_f = 0;
  int speed_b = 0;

  if (dist_f < 20){
    speed_f = 0;
  } else if (dist_f <100) {
    speed_f = map(dist_f, 20, 100, 0, 255);
    if (speed_f > 255) speed_f = 255;
    if (speed_f <0 ) speed_f =0;
  } else {
    speed_f = 255;
  }

  if (dist_b < 20) {
    speed_b = 0;
  } else if (dist_b < 100) {
    speed_b = map(dist_b, 20, 100, 0, 255);
    if (speed_b > 255) speed_b = 255;
    if (speed_b < 0) speed_b = 0;
  } else {
    speed_b = 255;
  }

  lcd.clear();
  lcd.setCursor(0,0);

if (speed_f > 0) {
  motorA_forward(speed_f);
  motorB_forward(speed_f);
  Serial.println("Moving Forward");
  lcd.print("Moving Forward");
  lcd.setCursor(0, 1); // Second row
  lcd.print("Speed: ");
  lcd.print(speed_f);
} else if (speed_b > 0) {
  motorA_backward(speed_b);
  motorB_backward(speed_b);
  Serial.println("Moving Backward");
  lcd.print("Moving Backward");
  lcd.setCursor(0, 1);
  lcd.print("Speed: ");
  lcd.print(speed_b);
} else {
  motorA_stop();
  motorB_stop();
  Serial.println("Stopped");
  lcd.print("Stopped");
  lcd.setCursor(0, 1);
  lcd.print("Speed: 0");
}

  delay(150);
}