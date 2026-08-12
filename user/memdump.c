#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void memdump(char *fmt, char *data);

int
main(int argc, char *argv[])
{
  if(argc == 1){
    printf("Example 1:\n");
    int a[2] = { 61810, 2025 };
    memdump("ii", (char*) a);
    
    printf("Example 2:\n");
    memdump("S", "a string");
    
    printf("Example 3:\n");
    char *s = "another";
    memdump("s", (char *) &s);

    struct sss {
      char *ptr;
      int num1;
      short num2;
      char byte;
      char bytes[8];
    } example;
    
    example.ptr = "hello";
    example.num1 = 1819438967;
    example.num2 = 100;
    example.byte = 'z';
    strcpy(example.bytes, "xyzzy");
    
    printf("Example 4:\n");
    memdump("pihcS", (char*) &example);
    
    printf("Example 5:\n");
    memdump("sccccc", (char*) &example);
  } else if(argc == 2){
    // format in argv[1], up to 512 bytes of data from standard input.
    char data[512];
    int n = 0;
    memset(data, '\0', sizeof(data));
    while(n < sizeof(data)){
      int nn = read(0, data + n, sizeof(data) - n);
      if(nn <= 0)
        break;
      n += nn;
    }
    memdump(argv[1], data);
  } else {
    printf("Usage: memdump [format]\n");
    exit(1);
  }
  exit(0);
}

void
memdump(char *fmt, char *data)
{
  char *p;
  for(p = fmt; *p != '\0'; p++){
    switch(*p){
      case 'i':{
      int i = *(int*)data;
      data += 4;
      printf("%d\n", i);
      break;
      }
      case 'p':{
      long long int lli = *(long long int*)data;
      data += 8;
      printf("%llx\n", lli);
      break;}
      case 'h':{
      short si = *(short*)data;
      data += 2;
      printf("%d\n",si);
      break;}
      case 'c':{
      char c = *(char*)data;
      data+=1;
      printf("%c\n",c);
      break;}
      case 's':{
      char *s = *(char**)data;
      data+=8;
      printf("%s\n",s);
      break;}
      case 'S':{
      printf("%s\n",data);
      break;
      }
    }
  }
}
