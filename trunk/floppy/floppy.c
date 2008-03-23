#include <system.h>
#include <stdio.h>



void i_floppy()
{
  char *drive_type[5] = {"no floppy drive", "360kb 5.25in floppy drive", "1.2mb 5.25in floppy drive", "720kb 3.5in", "1.44mb 3.5in", "2.88mb 3.5in"};

  unsigned char data,drive_a,drive_b;

  outportb(0x70, 0x10);
  data = inportb(0x71);

  drive_a = data >> 4;
  drive_b = data & 0xF;

  puts("Floppy drive A : ");
  puts(drive_type[drive_a]);
  putch('\n');

  puts("Floppy drive B : ");
  puts(drive_type[drive_b]);
  putch('\n');

}
