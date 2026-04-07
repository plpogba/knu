/**
 * scanf() Enter키 처리 테스트 
 */

#include <stdio.h>
#define USE_INT

 int main()
 {
#ifdef USE_INT	
	 int n1, n2;
#else 	 
	 char c1, c2;
#endif 
	 printf("Type two numbers: ");
	 /* 입력 내용:
	  * 10 Enter
	  * 20 Enter 입력 테스트  
	  * => scanf("%d%d")는 선행 공백 문자를 자동으로 건너뜀
	  */
#ifdef USE_INT
	 scanf("%d %d", &n1, &n2); // %d는 공백 문자(space, '\n')를 건너뜀
	 printf("n1: %d, n2: %d\n", n1, n2);
#else 	
	// 'a'입력 후 Enter키 입력의 경우 
	 scanf("%c%c", &c1, &c2);	// %c: 공백 문자를 2번째 char로 저장
	 scanf("%c %c", &c1, &c2);	// 첫 번째 문자 입력 후 공백 문자 건너뜀 
	 printf("c1: %d, c2: %d\n", c1, c2);
#endif 
	 return 0;
 }