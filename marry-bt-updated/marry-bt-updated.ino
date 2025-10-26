#include <Arduino.h>

int speed = 0;
int num = 0;
char BT[4];
bool dataComplete = false;

void setDirection(char dir) {
    //switch case for direction, values can be changed
    switch(dir) {
        case 'a':
            Serial.println("Your dir variable is A");
            break;
        case 'b':
            Serial.println("Your dir variable is B");
            break;
        case 'c':
            Serial.println("Your dir variable is C");
            break;
        case 'd':
            Serial.println("Your dir variable is D");
            break;
    }
}

int isDigit(char a, char b) {
    //will check to see if both chars a and b are digits, and create number ab in memory
    if(a >= '0' && a <= '9') {
        //a is a digit, so convert to int
        int num1 = a - '0';
        if(b >= '0' && b <= '9') {
            //both chars are valid digits
            //procceed to create the 2 digit number
            //b is a digit, so convert to int
            int num2 = b - '0';
            //calculate the number
            int num = num1 * 10 + num2;
            return num;
        }
    }
    else
        //return -1 as flag "this is not digit"
        return -1;
}

void procesMessage(char message[]) {
    //check validity
    char repVal[3];
    String repString = "";
    int number = isDigit(message[0], message[1]);
    if((message[0] == '0' || message[0] == '1') && !(message[0]== '1' && (message[1]!= '0' || message[2]!= '0'))) {
        repVal[0] = message[0];
        repVal[1] = message[1];
        repVal[2] = message[2];
        repString = repVal;
        
        speed = repString.toInt();
        Serial.print("Speed set to: ");
        Serial.println(speed);
    }
    else
    {
        Serial.println("Number outside of scope");
    }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  static int index = 0; // Use a static variable for consistent declaration
  // put your main code here, to run repeatedly:
  while (Serial.available() != 0) {
    char input = (char)Serial.read();
    if (index > 3)
    {
      BT[index++] = '\0'; // Null-terminate the string
      dataComplete = true;
      index = 0;
    }      
    else
    {
        BT[index++] = input;
    }
  }

  if(dataComplete == true) {
    String data(BT);
    Serial.println(data);
    procesMessage(BT);
    dataComplete = false;
  }
}