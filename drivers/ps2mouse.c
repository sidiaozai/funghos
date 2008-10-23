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
#include <drivers/dvtab.h>

void ps2m_handler();
void ps2m_handle(unsigned char flags, unsigned char x, unsigned char y);
void ps2m_init(struct dvsw *x);
void ps2m_wait(unsigned char a);

unsigned char ps2m_bytes[3];

ps2m_install() {
  int (*dvproc[DV_SRV])(struct dvsw*,...);
  dvproc[Init]=ps2m_init;
  dvtab_add("ps2mouse",dvproc,12,12,&ps2m_handler,&ps2m_handler,TRUE);
}


void ps2m_handler(struct regs *r)
{
  static unsigned char cycle = 0;
  ps2m_bytes[cycle++] = inportb(0x60);
  if (cycle == 3) {
  	cycle = 0;
  	ps2m_handle(ps2m_bytes[0],ps2m_bytes[1],ps2m_bytes[2]);
  }
}


void ps2m_init(struct dvsw *x)
{
  unsigned char status_byte;
  ps2m_wait(1);
  outportb(0x64, 0xA8); /* enable the auxiliary mouse device */
  
  ps2m_wait(1);
  outportb(0x64,0x20);
  ps2m_wait(0);
  status_byte = (inportb(0x60) | 2);
  ps2m_wait(1);
  outportb(0x64, 0x60);
  ps2m_wait(1);
  outportb(0x60, status_byte);
  
  ps2m_wait(1);
  outportb(0x64,0xD4); /* tell the mouse we are sending a command */
  ps2m_wait(1);
  outportb(0x60,0xF6);
  ps2m_wait(0);
  inportb(0x60);
  
  ps2m_wait(1);
  outportb(0x64,0xD4); // tell the mouse we are sending a command
  ps2m_wait(1);
  outportb(0x60,0xF4);
  ps2m_wait(0);
  inportb(0x60);
}


void ps2m_wait(unsigned char a)
{
  unsigned int time_out = 100000;
  if (a==0)
  {
  	while (time_out--)
  	{
  	  if ((inportb(0x64) & 1)==1)
  	    return;
	}
	return;
  } else {
    while (time_out--)
  	{
  	  if ((inportb(0x64) & 2)==0)
  	    return;
	}
	return;  	
  }
}


void ps2m_handle(unsigned char flags, unsigned char x, unsigned char y)
{
  if (flags & 0x8)
  {
  if ((flags & 0x80) || (flags & 0x40))
    return; // 0x80 and 0x40 only show x and y overflows, do not care about them
  if (flags & 0x20)
    y |= 0xFFFFFF00; //delta-y is a negative value
  if (flags & 0x10)
    x |= 0xFFFFFF00;
  if (flags & 0x4)
    puts("[ps2] middle\n"); //middle button is pressed
  if (flags & 0x2)
    puts("[ps2] right\n"); //right button is pressed
  if (flags & 0x1)
    puts("[ps2] left\n"); //left button is pressed
  } else {
  	puts("[ps2] bad flags byte (0x8 is not set)\n");
  	while (1)
  	 ;
  }
}
