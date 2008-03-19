#include <stdio.h>

char *gets(char *string)
{
  char c;
  register unsigned int i;
  unsigned int string_len=strlen(string);
  for (i=0;i<=string_len;i++) {
    c = getchar();
    
    if (c=='\n') {
      string[i]='\0';
      return string;
    } else {
    string[i]=c;
    }
  }
}