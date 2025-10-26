#include <stdio.h>
#include <string.h>

int speed = 0;
int num = 0;

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

void procesMessage(char message[20]) {
	//check validity
	int number = isDigit(message[1], message[2]);
	if(message[0] == '0' &&           //Says: if the first 3 characters = 000 then set speed to 000
	  message[1] == '0' &&
      	  message[2] == '0') {
		printf("Speed set to: %d\n", speed);
        	speed = 0;
  	}
	else if(message[0] == '1' &&           //Says: if the first 3 characters = 100 then set speed to 100
          message[1] == '0' &&
          message[2] == '0' ) {
            speed = 100;
	    printf("Speed set to: %d\n", speed);
          }	
	else if(message [0] == '0' && 
	  number != -1) {
		printf("Nice job! This is a valid number: %d\n", number);
		//convert 2 chars into 1 int

	}
}

int main() {
	char foo[20];
	scanf("%s", foo);
	printf("Your text: %s\n", foo);
	procesMessage(foo);	
	if(foo[3] >= 'a' &&
	  foo[3] <= 'z') {
		setDirection(foo[3]);
	}
}
