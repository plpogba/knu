/**
 * scanf() 두 개의 문자열 입력 및 Enter키 테스트 
 * 
 */

#include <stdio.h>
#include <string.h>

#define BUF_SIZE 100

 int main()
 {
	 char msg1[BUF_SIZE];
	 char msg2[BUF_SIZE];

	 memset(msg1, -1, sizeof(msg1));
	 memset(msg2, -1, sizeof(msg2));

	 printf("Input string1 -> ");
	 scanf("%s", msg1);
	 
	 //getchar(); // '\n' 제거 용도
	 
	 printf("Input string2 -> ");
	 scanf("%s", msg2);

	 printf("scanf() msg1: %s, len: %zu\n", msg1, strlen(msg1));
	 printf("scanf() msg2: %s, len: %zu\n", msg2, strlen(msg2));

	 return 0;
 }