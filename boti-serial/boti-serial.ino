String serialVal = "";
bool stringDone = false;
int number = 0;

bool isNumber(char c) {
  if (!(c >= '0' && c <= '9'))
    return 0;
  return 1;
}

void setup() {
  Serial.begin(9600);
  stringDone = false;
}

void handleNumber(int number) {
  //enter motor control here
}

void loop() {
     // Check for available data
  if (Serial.available()) {
    char foo = Serial.read();
    serialVal += foo;
       // If we read a digit, update the number
    if (isNumber(foo)) {
      number = number * 10 + (foo - '0');
    }
       // If we read a newline, set the flag
    if (foo == '\n') {
      stringDone = true;
    }
  }
     // If we have finished reading a string (i.e., newline received)
  if (stringDone) {
    stringDone = false;
       // Only print if the number is not zero (or maybe we always print?)
    if (number != 0) {
      Serial.print(number);
      handleNumber(number);
      number = 0; // reset the number
    }
    serialVal = ""; // clear the string
    }
}
