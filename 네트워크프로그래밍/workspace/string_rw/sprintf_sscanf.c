#include <stdio.h>
int main()
{
    char *token = "25 54.32 Thompson 56789";
    int n1, n2;
    char name1[20] = {0};
    double d1;
    sscanf(token, "%d %lf %s %d", &n1, &d1, name1, &n2);
    printf("%d, %lf, %s, %d\n", n1, d1, name1, n2);

    char buf[256] = {0};
    char name[20] = "홍길동";
    int num = 23;
    double level = 2.37;

    sprintf(buf, "Name: %s, No: %d, Level: %f", name, num, level);
    //puts(buf);
    printf("%s\n", buf);
    return 0;
}