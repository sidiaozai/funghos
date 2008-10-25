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
#include <screen/win.h>



extern WIN *first_window;
unsigned short *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;
unsigned short screen_no_scroll=0;



void move_csr(void); /* moves the cursor, using csr_x and csr_y */
void cls(); /* clears the screen */
void putch(unsigned char c); /* PUTCHaracter */
void putcha(unsigned char c); /* system use only */
void puts(unsigned char *text); /* PUTString */
void puti(int x); /* PUTInteger */
void putx(int x); /* PUTheXadecimal */
void txtclr(unsigned char forecolor, unsigned char backcolor); /* colors */
void i_video(void); /* video init, system, boot */



void move_csr(void)
{
    unsigned temp;
    temp = csr_y * 80 + csr_x;

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

/* clears the screen */
void cls()
{
    unsigned blank;
    int i;

    blank = 0x20 | (attrib << 8);

    /* nastavit vse na mezery v aktualni barve */
    for(i = 0; i < 25; i++)
        memsetw (textmemptr + i * 80, blank, 80);

    csr_x = 0;
    csr_y = 0;
    move_csr();
}



void putch(unsigned char c)
{
    unsigned short *where;
    unsigned att = attrib << 8;

    if(c == 0x08)
    {
      if ((rtwin(CSRX)+1)<csr_x) {
	csr_x--;
	putch(' ');
	csr_x--;
      } else {
      if (((rtwin(CSRX)+1)==csr_x)&&((rtwin(CSRY)+1)!=csr_y)) {
	csr_x=rtwin(CSRX2)-1;
	--csr_y;
	putch(' ');
	csr_x=rtwin(CSRX2)-1;
	--csr_y;
      }
      }
    }

    /* tab handler */
    else if(c == 0x09)
    {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    /* Handles a 'Carriage Return', which simply brings the
    *  cursor back to the margin */
    else if(c == '\r')
    {
        csr_x = rtwin(CSRX)+1;
    }
    /* next line is pretty simple */
    else if(c == '\n')
    {
        csr_x = rtwin(CSRX)+1;
        csr_y++;
    }
    /* finally, this prints a character! */
    else if(c >= ' ')
    {
      where = textmemptr + (csr_y * 80 + csr_x);
      *where = c | att;	/* Character AND attributes: color */
      csr_x++;
    }

    /*    if the cursor is at the end of a window, bring it somewhere else :D */
/*     if(rtwin(WINEND)) */
/*     { */
/*       putcha('1'); */
/*       csr_x = rtwin(CSRX)+1; */
/*       putcha('2'); */
/*       csr_y++; */
/*       putcha('3'); */
/*     } */
    
    /* same as above, but it scrolls the window */
    if (rtwin(WINSCROLL)) {
      if (!screen_no_scroll) scwin(currwin);
    }

    if (rtwin(WINEND))
    {
      csr_y++;
      csr_x = rtwin(CSRX)+1;
    }

    move_csr();
    
}



/* 'system' putch(), hasn't got the scrolling 'protection',etc... */
void putcha(unsigned char c)
{
    unsigned short *where;
    unsigned att = attrib << 8;

    /* backspace */
    if(c == 0x08)
    {
        if(csr_x != 0) csr_x--;
    }
    /* tabs */
    else if(c == 0x09)
    {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    /* Handles a 'Carriage Return', which simply brings the
    *  cursor back to the margin */
    else if(c == '\r')
    {
        csr_x = 0;
    }
    /* nextlines */
    else if(c == '\n')
    {
        csr_x = 0;
        csr_y++;
    }
    /* characters */
    else if(c >= ' ')
    {
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;	/* Character AND attributes: color */
        csr_x++;
    }

    /* this isn't used often :) */
    if(csr_x >= 80)
    {
        csr_x = 0;
        csr_y++;
    }

    //move_csr(); removed - we don't need this, really
    
}



void puts(unsigned char *text)
{
    int i;

    for (i = 0; i < strlen(text); i++)
    {
        putch(text[i]);
    }
}



/* PUTInteger */
void puti(int x)
{
  char c[20];
  int i,tmp;
  for (i=0;i<20;++i) {
    c[i]='x';
  }
  i=19;
  while (x>=10) {
    tmp=x%10;
    c[i]='0'+tmp;
    x=(x-tmp)/10;
    --i;
  }
  tmp=x;
  c[i]='0'+tmp;
  i=0;
  for (i=0;i<20;++i) {
    if (c[i]!='x') putch(c[i]);
  }
}



void putx(int x)
{
  char c[20];
  int i,tmp;
  for (i=0;i<20;++i) {
    c[i]='x';
  }
  i=19;

  while (x>=16) {
    tmp=x%16;
    if (tmp<=9)
    {
      c[i]='0'+tmp;
      x=(x-tmp)/16;
      --i;
    } else {
      /* a in ASCII is 97 */
      tmp -= 10;
      c[i]=97+tmp;
      x=(x-tmp-10)/16;
      --i;
    }
  }

  tmp=x;

  if (tmp<=9)
  {
    c[i]='0'+tmp;
  } else {
    tmp -= 10;
    c[i]=97+tmp;
  }

  i=0;

  for (i=0;i<5;++i) {
    if (c[i]!='x') putch(c[i]);
  }
}



/* Sets the forecolor and backcolor that we will use */
void txtclr(unsigned char forecolor, unsigned char backcolor)
{
    /* Top 4 bytes are the background, bottom 4 bytes
    *  are the foreground color */
  attrib = (backcolor << 4) | (forecolor & 0x0F);
}



/* sets the pointer */
void i_video(void)
{
  int i;
  for (i=0;i<WINMAX;i++)
    window[i].pid = 0;
  textmemptr = (unsigned short *)0xB8000;
  txtclr(BLACK,BLACK);
  cls();
}

