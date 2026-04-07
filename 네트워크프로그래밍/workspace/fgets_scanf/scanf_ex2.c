/**
 * scanf() Enter 키 처리 테스트 
 * 
 */
 
 #include <stdio.h>

 int main()
 {
	 int a, b;
	 char c1, c2;
	 printf("Enter something: ");
	 scanf("%d", &a); // line 1
	 printf("Enter other something: ");
	 scanf("%d", &b); // line 2

	 printf("Enter a char: ");
	 scanf("%c", &c1); // line 3: Enter키 자동 입력됨 
	 printf("Enter another char: ");
	 scanf("%c", &c2); // line 4: 

	 printf("Done"); // line 5
	 return 0;
 }