
//this code will convert a string to variables :)
char gotMessage = 0;
char direction = ' ';
int speed = 0;
bool stringComplete = false;  // whether the string is complete
String inputString[20];

void procesMessage(char message[20])
{
  if(message[0] == '0' &&           //Says: if the first 3 characters = 000 then set speed to 000
      message[1] == '0' &&
      message[2] == '0') {
        speed = 0;
  }
  else if (message[0] == '1' &&           //Says: if the first 3 characters = 100 then set speed to 100
          message[1] == '0' &&
          message[2] == '0' ){
            speed = 100;
          }
  else if(message[0] != '0'||
          message[0] != '1') {
    Serial.println("invalid data speed");
  }
  else {
    Serial.println("valid data speed");
    if( message[3] == 'w' ||  //forward
      message[3] == 's' ||  //backward
      message[3] == 'a' ||  //left
      message[3] == 'd' ||  //right
      message[3] == 'q' ) //stop
      {
       direction = message[3]; 
      }
      else {
        direction = message[3];
        Serial.println(message[3]);
      }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //prompt for message
  Serial.println("Type a message: ");
}

void loop() {
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
    procesMessage(inputString);
  }
}

void serialEvent() {
  while (Serial.available()) {
    gotMessage = (char)Serial.read();
    inputString += gotMessage;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  } 
}