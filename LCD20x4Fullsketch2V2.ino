#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

// ==================== LCD SETUP ====================
LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address 0x27, 20x4

unsigned long startTime = 0;
unsigned long prevMillis = 0;
unsigned long elapsedSeconds = 0;
int eeAddress = 0;
int mode = 0;
int dir = 0;
bool paused = false;

// Custom characters
byte customChar0[8] = {0b01110,0b11011,0b10001,0b11111,0b10001,0b11111,0b10001,0b11111};
byte customChar1[8] = {0b00100,0b01110,0b11111,0b00100,0b00100,0b00100,0b00100,0b00100};
byte customChar2[8] = {0b00100,0b00100,0b00100,0b00100,0b00100,0b11111,0b01110,0b00100};
byte customChar3[8] = {0b00000,0b00100,0b01100,0b11111,0b11111,0b01100,0b00100,0b00000};
byte customChar4[8] = {0b00100,0b00100,0b00110,0b11111,0b11111,0b00110,0b00100,0b00100};
byte customChar5[8] = {0b01010,0b01010,0b01010,0b01010,0b01010,0b01010,0b01010,0b01010};
byte customChar6[8] = {0b00100,0b00100,0b01000,0b01011,0b01100,0b10110,0b10001,0b10110};
byte customChar7[8] = {0b00000,0b00000,0b11011,0b11011,0b11011,0b11011,0b00000,0b00000};

// ==================== LCD FUNCTIONS ====================
void setupLCD() {
  lcd.init(); 
  lcd.backlight();
  lcd.createChar(0, customChar0);
  lcd.createChar(1, customChar1);
  lcd.createChar(2, customChar2);
  lcd.createChar(3, customChar3);
  lcd.createChar(4, customChar4);
  lcd.createChar(5, customChar5);
  lcd.createChar(6, customChar6);
  lcd.createChar(7, customChar7);
  //Start Screen
  lcd.setCursor(4, 1);
  lcd.print("Robot Ready...");
  delay(1000);
  lcd.clear();
  //cursor setup
  lcd.setCursor(0,0); lcd.print("Mode:"); lcd.setCursor(14,0); lcd.write((byte)5);
  lcd.setCursor(0,1); lcd.print("Time"); lcd.setCursor(4,1);lcd.print("---"); lcd.setCursor(14,1); lcd.write((byte)5);lcd.setCursor(12,1);lcd.print("--"); lcd.setCursor(15,1); lcd.print("-----");
  lcd.setCursor(0,2); lcd.print("Dir"); lcd.setCursor(3,2); lcd.print(":"); lcd.setCursor(14,2); lcd.write((byte)5);
  lcd.setCursor(0,3); lcd.print("Spd"); lcd.setCursor(3,3); lcd.print(":"); lcd.setCursor(14,3); lcd.write((byte)5); lcd.setCursor(15,3); lcd.print("m"); lcd.setCursor(16,3); lcd.write((byte)6);
  lcd.setCursor(15,0); lcd.write((byte)0); lcd.setCursor(19,0); lcd.print("%");

  EEPROM.get(eeAddress, elapsedSeconds);
}

void updateLCD() {
  // ===== TIME =====
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis >= 1000) {
    prevMillis = currentMillis;
    elapsedSeconds++;
    if (elapsedSeconds %10 ==0) EEPROM.put(eeAddress, elapsedSeconds);
  }
  unsigned long elapsed = (millis() - startTime)/1000;
  int minutes = elapsed / 60;
  int seconds = elapsed % 60;
  lcd.setCursor(7,1);    
  if (minutes < 10) lcd.print("0");
  lcd.print(minutes); lcd.print(":");
  if (seconds < 10) lcd.print("0");
  lcd.print(seconds);

  // ===== DIRECTION =====
  lcd.setCursor(4,2); lcd.print("          "); lcd.setCursor(4,2);
  if (dir == 1) {lcd.write((byte)1); lcd.print("FORWARD"); paused = false;}
  else if (dir ==2 ) {lcd.write((byte)2); lcd.print("BACKWARD"); paused = false;}
  else if (dir ==3 ) {lcd.write((byte)3); lcd.print("LEFT"); paused = false;}
  else if (dir ==4 ) {lcd.write((byte)4); lcd.print("RIGHT"); paused = false;}
  else if (dir ==5 ) {lcd.write((byte)7); lcd.print("PAUSED"); paused = true;}

  // ===== SPEED =====
  int speed = 0;
  if(dir==1 || dir==3 || dir==4) speed = forwSpeed;
  else if(dir==2) speed = revSpeed;
  lcd.setCursor(4,3); lcd.print("   "); lcd.setCursor(4,3); lcd.print(speed);

  // ===== MODE =====
  lcd.setCursor(5,0); lcd.print("");
  if(mode ==0) lcd.print("Auto");
  else if(mode == 1) lcd.print("Master");
  else if(mode == 2) lcd.print("Slave");
}

// ==================== SETUP ====================
void setup() {
  setupLCD();
  startTime = millis();
}
void loop() {
  lcd.setCursor(16,0);
  
}