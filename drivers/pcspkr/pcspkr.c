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
