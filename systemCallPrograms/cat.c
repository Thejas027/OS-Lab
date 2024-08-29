#include <stdio.h>
#include <stdlib.h>

void cat_file(const char *path)
{
      FILE *file = fopen(path, "r");

      // edge case
      if (file == NULL)
      {
            perror("fopen");
            exit(EXIT_FAILURE);
      }

      char ch;
      while ((ch = fgetc(file)) != EOF)
            putchar(ch);

      fclose(file);
}

int main(int argc, char *argv[])
{
      // edge case
      if (argc < 2)
      {
            fprintf(stderr, "usage: %s <filepath>...\n", argv[0]);
            exit(EXIT_FAILURE);
      }

      for (int i = 1; i < argc; i++)
      {
            printf("\nContent of %s: ", argv[i]);
            cat_file(argv[i]);
      }

      return 0;
}
