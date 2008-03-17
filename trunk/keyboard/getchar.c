#include <system.h>
#include <stdio.h>
#include "kbmap.h"

char getchar()
{
  while (!(inportb(0x64) & 0x1))
    ;
  unsigned int scancode=inportb(0x60);
  char c=kbdus[scancode];
  putch(c);
  return c;
}
