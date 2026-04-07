#include <stdio.h>

int main()
{
	FILE *stream;
	int c;

	stream = fopen("sample.txt", "r");
	if(stream != NULL)
	{
		while((c = fgetc(stream)) != EOF)
		{
			putchar(c);
		}
		printf("\n");
	}
	return 0;
}
