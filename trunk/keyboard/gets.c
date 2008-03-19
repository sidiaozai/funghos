#include <stdio.h>

char *gets(char *string)
{
  unsigned int i=0;
  char c;
  while (1) {
    c = getchar();
    c = getchar(); // strange, but it solves the bug (?!)
    if (c=='\n') {
      string[i++]='\0';
      return string;
    } else {
    string[i++]=c;
    }
  }
}
