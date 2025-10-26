#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//get a string
//if it is a number, convert it to an integer
//if not, print a message

int main() {
	char buf[9];
	bool number = true;
	scanf("%s", &buf);
	printf("your string is: %s\n", buf);
	for(int i = 0; i < strlen(buf); i++) {
		if(buf[i] >= '0' && buf[i] <= '9') {
			printf("char number %d is %c\n", i, buf[i]);
		}
		else printf("not a number: %c\n");
	}
}
