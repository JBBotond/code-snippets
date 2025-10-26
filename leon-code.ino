#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address 0x27, 16 column and 2 rows

unsigned long startTime;

byte customChar0[8] = {
  0b01110,
  0b11011,
  0b10001,
  0b11111,
  0b10001,
  0b11111,
  0b10001,
  0b11111
};

byte customChar1[8] = {
  0b00100,
  0b01110,
  0b11111,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100
};

byte customChar2[8] = {
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b11111,
  0b01110,
  0b00100
};

byte customChar3[8] = {
  0b00000,
  0b00100,
  0b01100,
  0b11111,
  0b11111,
  0b01100,
  0b00100,
  0b00000
} ;

byte customChar5[8] = {
  0b01010,
  0b01010,
  0b01010,
  0b01010,
  0b01010,
  0b01010,
  0b01010,
  0b01010
};

//no space

/*byte customChar4[8] = {
  0b11111,
  0b00111,
  0b00111,
  0b01001,
  0b10001,
  0b00000,
  0b00000,
  0b00000
};

byte customChar5[8] = {
  0b11111,
  0b11100,
  0b11100,
  0b10010,
  0b10001,
  0b00000,
  0b00000,
  0b00000,
};

byte customChar6[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b10001,
  0b01001,
  0b00111,
  0b00111,
  0b11111,
};

byte customChar7[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b10001,
  0b10010,
  0b11100,
  0b11100,
  0b11111,
};*/

byte customChar4[8] = {
  0b00100,
  0b00100,
  0b00110,
  0b11111,
  0b11111,
  0b00110,
  0b00100,
  0b00100,
} ;

byte customChar6[8] = {
  0b00100,
  0b00100,
  0b01000,
  0b01011,
  0b01100,
  0b10110,
  0b10001,
  0b10110,
} ;

byte customChar7[8] = {
  0b00000,
  0b00000,
  0b11011,
  0b11011,
  0b11011,
  0b11011,
  0b00000,
  0b00000,
} ;

void setup()
{ 
  lcd.init(); // initialize the lcd
  lcd.backlight();
  Serial.begin(9600);

  
  
  lcd.createChar(0, customChar0); // battery
  lcd.createChar(1, customChar1); // front
  lcd.createChar(2, customChar2); // back
  lcd.createChar(3, customChar3); //left
  lcd.createChar(4, customChar4); //right
  /*lcd.createChar(4, customChar4); //Front Right
  lcd.createChar(5, customChar5); //Front Left
  lcd.createChar(6, customChar6); //Back Right
  lcd.createChar(7, customChar7); //Back Left*/
  lcd.createChar(5, customChar5); //double line
  lcd.createChar(6, customChar6); //per second
  lcd.createChar(7, customChar7);


  lcd.setCursor(0,0);
  lcd.print("D"); //direction placement
  lcd.setCursor(5,0);
  lcd.print("T"); //show time
  lcd.setCursor(5,1);
  lcd.print("S");      //show speed
  lcd.setCursor(14, 0); // move cursor to (2, 0)
  lcd.write((byte)0);  // Battery

  lcd.setCursor(1,0);
  lcd.print(":"); //show the equation
  lcd.setCursor(6,0);
  lcd.print(":");  //:
  lcd.setCursor(6,1);
  lcd.print(":"); //:

  lcd.setCursor(15,0);
  lcd.print("%");
  lcd.setCursor(10,1);
  lcd.print("m");
  lcd.setCursor(11,1);
  lcd.write((byte)6); //per second for velocity
  //lcd.setCursor(12,0);
  //lcd.print("s"); //show seconds for time
  lcd.setCursor(9,0);
  lcd.print("M");

  lcd.setCursor(4,0);  
  lcd.write((byte)5);  //spacing
  lcd.setCursor(4,1);
  lcd.write((byte)5);  //spacing
  lcd.setCursor(12,0);  
  lcd.write((byte)5);  //spacing
  lcd.setCursor(12,1);
  lcd.write((byte)5);  //spacing

  /*  
  lcd.setCursor(3,0);
  lcd.write((byte)1);  //Front
  lcd.setCursor(2,0);
  lcd.write((byte)5);  //FL
  lcd.setCursor(4, 0); // move cursor to (4, 0)
  lcd.write((byte)4);  // FR
  lcd.setCursor(3, 1); 
  lcd.write((byte)2);  //Back
  lcd.setCursor(2,1);
  lcd.write((byte)7);  //BL
  lcd.setCursor(4,1);
  lcd.write((byte)6);  //BR
  lcd.setCursor(0,1);
  lcd.write((byte)3);  //L
  lcd.setCursor(1,1);
  lcd.write((byte)8);   //R
  /* */
  startTime = millis(); //start
  
}

void loop()
{
  //time
  unsigned long elapsed = (millis() - startTime)/ 1000;
  int minutes = elapsed / 60;
  int seconds = elapsed % 60;

  lcd.setCursor(7,0);
  if (minutes < 10) lcd.print("0");
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) lcd.print("0");
  lcd.print(seconds);
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    data.trim();
    int c1 = data.indexOf(',');
    int c2 = data.indexOf(',', c1+1);
    if (c1>0 && c2 >0) {
      int dir =data.substring(0, c1).toInt();
      int speed = data.substring(c1 +1, c2).toInt();
      int battery =data.substring(c2 +1).toInt();
      
      lcd.setCursor(2,0); //directions
      lcd.print("  ");
      lcd.setCursor(2,0);
      if (dir == 1) lcd.write((byte)1);//front
      else if (dir ==2 ) lcd.write((byte)2);  //back
      else if (dir ==3 ) lcd.write((byte)3);  //left
      else if (dir ==4 ) lcd.write((byte)4);  //right

      lcd.setCursor(7,1); //speed
      lcd.print("   ");
      lcd.setCursor(4,1);
      lcd.print(speed);

      
      lcd.setCursor(13,1); //battery
      lcd.print("   ");
      lcd.setCursor(14,1);
      lcd.print(battery);
    }


  }


  delay(300); //refresh
}