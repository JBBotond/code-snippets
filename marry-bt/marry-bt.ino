#include <stdio.h>
#include <string.h>

int speed = 0;
int num = 0;
int index = 0;
char BT[4];
String data = "";
bool dataComplete = false;

void setDirection(char dir) {
	//switch case for direction, values can be changed
	switch(dir) {
		case 'a':
			printf("Your dir variable is A\n");
			break;
		case 'b':
			printf("Your dir variable is B\n");
			break;
		case 'c':
			printf("Your dir variable is C\n");
			break;
		case 'd':
			printf("Your dir variable is D\n");
			break;
		break;

	}
}

int isDigit(char a, char b) {
	//will check to see if both chars a and b are digits, and create number ab in memory
	if(a >= '0' &&
	a <= '9') {
		//a is a digit, so convert to int
		int num1 = a - '0';
		if(b >= '0' &&
		b <= '9') {
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
		//reuturn -1 as flag "this is not digit"
		return -1;
}

void procesMessage(char message[]) {
	//check validity

	char repVal[3];
	String repString = " ";
	int number = isDigit(message[0], message[1]);
  if((message[0] == '0'|| message[0] == '1') && !(message[0]== '1' && (message[1]!= '0' || message[2]!= '0')))		//checks if the value is between 0 and 100
	{
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
  // put your main code here, to run repeatedly:
  while (Serial.available()!=0)
  {
    char input = (char)Serial.read();
			//Serial.println(input);
      if (index > 3)
      {
        dataComplete = true;
        index = 0;
      }      
			if (index <= 3)
			{
        
				BT[index++] = input;
				break;
			}

  }
  if(dataComplete == true)
  {
    data = BT;
    Serial.println(data);
    procesMessage(BT);
    dataComplete = false;
  }
  

}
