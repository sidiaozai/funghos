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
#include <stdlib.h>



void playsound(unsigned int freq)
{	
	unsigned int div;
	unsigned short tmp;
	
	div = 1193180 / freq;
	outportb(0x43, 0xb6);
	outportb(0x42, (unsigned short int) (div) );
	outportb(0x42, (unsigned short int) (div >> 8) );
	
	tmp = inportb(0x61);
	if (tmp != (tmp | 3))
	{
		outportb(0x61, tmp | 3);
	}
}



void nosound() {
	unsigned short tmp = (inportb(0x61) & 0xFC);
	outportb(0x61, tmp);
}



void beep() {
	 playsound(1000);
         //set_PIT_2(old_frequency);
}
