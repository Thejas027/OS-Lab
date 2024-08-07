#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
      char temp[200];
      FILE *fp;

      char *filename = argv[1];
      char *pattern = argv[2];

      fp = fopen(filename, "r");

      while (fgets(temp, sizeof(temp), fp) != NULL)
      {
            if (strstr(temp, pattern))
            {
                  printf("%s", temp);
            }
      }

      fclose(fp);

      return 0;
}