#include<fcntl.h>
#include<unistd.h>
int main()
{
	char c[50];
	int file = open("echo.txt", O_RDWR | O_CREAT, 0777);
	int n = read(0, c, 50);
	write(1, c, n); // Write to console
	write(file, c, n); // Write to file
    close(file);
	return 0;
}