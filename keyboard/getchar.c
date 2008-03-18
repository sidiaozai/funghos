#include <system.h>
#include <stdio.h>
#include "kbmap.h"
#include "kb.h"


char getchar()
{
  char c;
  unsigned int scancode;
  while (1) {
     while (!(inportb(0x64) & 0x1))
      ;
     scancode = inportb(0x60);
     
     if (scancode & 0x80)
       {
	 if (scancode==170||scancode==182) kb_flags.shift=FALSE;
	 /*170 - levy shift, 182 - pravy shift*/
       }
     else
       {
	 if (kbdus[scancode]!='\S') {
	   switch (kb_flags.shift) {
	   case 0:c=kbdus[scancode];putch(c);break;
	   case 1:c=kbdus2[scancode];putch(c);break;
	   }
	 } else {
	   c='\S';
	   kb_flags.shift=TRUE;
	 }
       }
     if (c!='\S') return c;
  }
}
