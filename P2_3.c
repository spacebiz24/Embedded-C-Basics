// Read text from echo.txt and write to file and console

#include<fcntl.h>
#include<unistd.h>
int main()
{
	char c[50];
	int file = open("echo.txt", O_RDWR | O_CREAT, 0777);
	int CharLen = read(0, c, 50);
	write(1, c, CharLen); // Write to console
	write(file, c, CharLen); // Write to file
	close(file);
	
	return 0;
}
