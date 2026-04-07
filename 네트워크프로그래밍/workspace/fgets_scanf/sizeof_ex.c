/*
	sizeof() 연산자와 strlen() 함수 비교 
*/

#include <stdio.h>
#include <string.h>

int main()
{
	char buf[] = "Hello";

	printf("strlen(): %zu\n", strlen(buf));
	printf("sizeof(): %zu\n", sizeof(buf));

	return 0;
}