#include <stdio.h>



char *gets(char *string, int max)
{
  unsigned int i=0;
  char c;
  for (i=0;(i<max&&c!='\n');) {
    c = getchar();
    if (c=='\n') {
      string[i++]='\0';
      return string;
    } else {
      if (c=='\b') {
	string[i--]=' ';
      } else {
	string[i++]=c;
      }
    }
  }
}
