#include <stdio.h>
#include <dirent.h>

void open_directory(const char *path)
{
      DIR *dp = opendir(path);
      struct dirent *entry;

      if (dp == NULL)
      {
            perror("opendir");
            return;
      }

      while ((entry = readdir(dp)) != NULL)
            printf("%s\n", entry->d_name);

      closedir(dp);
}

int main(int argc, char *argv[])
{
      const char *path;

      if (argc > 1)
            path = argv[1];
      else
            path = ".";

      open_directory(path);
}