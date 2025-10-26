#include <stdio.h>

int isDigit(char a, char b) {
	//will check to see if both chars a and b are digits, and create number ab in memory
	if(a >= '0' &&
	a <= '9') {
		int num1 = a - '0';
		if(b >= '0' &&
		b <= '9') {
			//both chars are valid digits
			//procceed to create the 2 digit number
			int num2 = b - '0';
			int num = num1 * 10 + num2;
			return num;
		}
	}
	else
		return -1;
}

int main() {
	char a, b;
	scanf("%c%", &a);
	scanf("%c%", &b);
	int digit = isDigit(a, b);
	if(digit == -1)
		printf("Not a valid value!\n");
	else
		printf("Your number: %d\n", digit);
}
