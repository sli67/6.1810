#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"
#include "user/user.h"
#include "kernel/param.h"

char *
fmtname(char *path)
{
  char *p;

  // Find first character after last slash.
  for (p = path + strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;
  return p;
}

void recurse(char *path, char *pattern, char **carg, int exe);

int main(int argc, char **argv)
{
  int exe = 0;
  if (argc >= 4 && strcmp(argv[3], "-exec") == 0)
  {
    exe = 1;
  }
  recurse(argv[1], argv[2], argv + 4, exe);
  exit(0);
}

void recurse(char *path, char *pattern, char **carg, int exe)
{
  int fd = open(path, O_RDONLY);
  struct stat st;
  struct dirent de;
  fstat(fd, &st);

  switch (st.type)
  {
  case T_DEVICE:
    break;
  case T_DIR:
  {
    char buf[512], *p;
    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
      if (de.inum == 0)
        continue;
      strcpy(buf, path);
      p = buf + strlen(buf);
      *p = '/';
      p += 1;

      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = '\0';

      if (strcmp(p, ".") != 0 && strcmp(p, "..") != 0)
        recurse(buf, pattern, carg, exe);
    }
    break;
  }
  case T_FILE:
  {
    if (strcmp(fmtname(path), pattern) == 0)
    {
      if (exe)
      {
        int pid = fork();
        if (pid == 0)
        {
          char *ecarg[MAXARG];
          int i;
          for (i = 0; carg[i] != 0; i++)
            ecarg[i] = carg[i];
          ecarg[i] = path;
          ecarg[i + 1] = 0;
          exec(*carg, ecarg);
        }
        else
          wait(0);
      }
      else
        printf("%s\n", path);
    }
    break;
  }
  }
  close(fd);
}