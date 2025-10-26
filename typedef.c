#include <stdio.h>

typedef struct myStruct {
	int myValue;
} newStruct;

int main() {
	newStruct structure;
	structure.myValue = 3;
	printf("Struct value is: %d\n", structure.myValue);
}
