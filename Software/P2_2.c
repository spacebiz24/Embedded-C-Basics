// Copy text from in.txt into out.txt

#include<fcntl.h>
#include<unistd.h>
int main()
{
	char *c;
	int fin = open("in.txt", O_RDONLY);
	int fout = open("out.txt", O_WRONLY | O_CREAT, 0777); // 0777 is octal to give exectue access
	while (read(fin, &c, 1) == 1)
		write(fout, &c, 1);
	close(fin);
	close(fout);
	return 0;
}
