#include <stdio.h>

char *gets(char *string)
{
  unsigned int i=0;
  char c;
  while (1) {
    c = getchar();
    
    if (c=='\n') {
      string[i++]='\0';
      return string;
    } else {
    string[i++]=c;
    }
  }
}
