/**
 * fgets(), fscanf() 파일 읽기 예제 소스 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *f;
    char buffer[100] = {0};

    if ((f = fopen("sample1.txt", "r")) == NULL)
    {
        printf("File not found\n");
        exit(1);
    }
    // Sample #1: fgets() 사용
    printf("Example 1. fgets()\n");
    while(fgets(buffer, sizeof(buffer), f) != NULL) 
    {
        printf("%s", buffer);
    }
    fclose(f);

    memset(buffer, 0, sizeof(buffer));
    if ((f = fopen("sample.txt", "r")) == NULL)
    {
        printf("File not found\n");
        exit(1);
    }
    // Sample #2: fscanf() 사용
    printf("Example 2. fscanf()\n");
    int num = 0;
    int ret = 0;
    while ((ret = fscanf(f, "%d %s", &num, buffer)) != EOF)
    {
        //printf("fscanf() ret=%d\n", ret);
        printf("%d %s\n", num, buffer);
    }
    fclose(f);

    return 0;
}
