/*    (c) 2008 Jan Dlabal <dlabaljan@gmail.com>                               */
/*                                                                            */
/*     This file is part of FunghOS.                                          */
/*                                                                            */
/*     Funghos is free software: you can redistribute it and/or modify        */
/*     it under the terms of the GNU General Public License as published by   */
/*     the Free Software Foundation, either version 3 of the License, or      */
/*     any later version.                                                     */
/*                                                                            */
/*     FunghOS is distributed in the hope that it will be useful,             */
/*     but WITHOUT ANY WARRANTY; without even the implied warranty of         */
/*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          */
/*     GNU General Public License for more details.                           */
/*                                                                            */
/*     You should have received a copy of the GNU General Public License      */
/*     along with FunghOS. If not, see <http://www.gnu.org/licenses/>.        */



#include <system.h>
#include <stdio.h>
#include "kbmap.h"
#include "kb.h"


char getchar()
{
  unsigned char byte_;
  char c='\0';
  unsigned int scancode=0;
  kb_flags.in_use=TRUE;
  while (1) {
    while (!((byte_ = inportb(0x64)) & 1))
	  ;
	
	if (byte_ & 0x20)
	{
	  ps2m_handler();
	} else {
      scancode = inportb(0x60);
     
     if (scancode & 0x80)
       {
	     if (scancode==170||scancode==182) kb_flags.shift=FALSE; /*170 - left shift, 182 - right shift*/
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
	 if (c!='\S') {kb_flags.in_use=FALSE;return c;}
       }
    }
  }
}
