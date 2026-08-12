#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int isdigit(char c){
  return c>='0' && c<='9';
}

int
main(int argc, char *argv[])
{
  const char sep[] = "-\r\t\n./";
  if(argc<2)exit(1);
  int i;
  char buf[512];
  for(i=1; i<argc; i++ ){
    int fd = open(argv[i], O_RDONLY);
    read(fd, buf, sizeof(buf));

    char *p;
    int res = 0;
    int lst = 1;
    for(p = buf; *p != '\0'; p++){
      if(strchr(sep, *p)){
        if(p != buf && lst){
          if(res % 5 == 0||res % 6 == 0)printf("%d\n", res);
        }
        lst = 1;
        res = 0;
      }
      else if (isdigit(*p)){
        res = res * 10 + (*p) - '0';
      }
      else lst = 0;
    }
    if(res && (res % 5 == 0||res % 6 == 0))printf("%d\n",res);
  }
  exit(0);
}
