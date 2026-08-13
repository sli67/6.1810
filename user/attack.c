#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"
#define DATASIZE (8 * 4096)

int main(int argc, char *argv[])
{
  char *p = (char *)sbrk(16 * 4096);
  for (int i = 0; i < 16 * 4096; i++)
  {
    if (strcmp(p + i, "This may help.") == 0)
    {
      printf("%s\n", p + i + 16);
      break;
    }
  }
  exit(0);
}
