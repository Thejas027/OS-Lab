#include <stdio.h>
#include <stdlib.h>

void main()
{
      char fn[10].pat[10], temp[200];
      FILE *fp;

      printf("Enter the file name : ");
      scanf("%s", fn);
      printf("Enter the pattern to be search : ");
      scanf("%d", pat);

      fp = fopen(fn, "r");

      while (!feof)
      {
            fgets(temp, 100, fp);
            if (strstr(temp, pat))
                  printf("%s", temp);
      }
      fclose(fp);
}