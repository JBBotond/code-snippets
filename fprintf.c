#include <stdio.h>

int main() {
	FILE* myFile;

	myFile = fopen("./file.in", "a");
	fprintf(myFile, "this is my message to the world!\n");
	fclose(myFile);
}