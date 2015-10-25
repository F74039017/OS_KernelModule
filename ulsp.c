#include <stdio.h>

#define MAX_BUF_SIZE 512

/* Print the proc file "lsproc" */
int main(int argc, char **argv)
{
	FILE *fp = fopen("/proc/lsproc", "r");
	if(!fp)
		puts("Proc file doesn't exist");
	else
	{
		char buf[MAX_BUF_SIZE];
		while(fgets(buf, sizeof(buf), fp))
			printf("%s", buf);
		fclose(fp);
		fp = NULL;
	}

	return 0;
}
