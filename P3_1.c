#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	char letters[50];
	int input = read(0, letters, 50); // (read from keyboard, to which buffer, len of input to read)
	printf("%d\n", input);
	write(1, letters, input); // (write to monitor, from which buffer, how much to print)
	return 0;
}