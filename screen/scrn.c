#include <system.h>
#include <stdio.h>



unsigned short *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;



void move_csr(void); /* moves the cursor, using csr_x and csr_y */
void cls(); /* clears the screen */
void putch(unsigned char c); /* PUTCHaracter */
void putcha(unsigned char c); /* system use only */
void puts(unsigned char *text); /* PUTString */
void puti(int x); /* PUTInteger */
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

    /* if the cursor is at the end of a window, bring it somewhere else :D */
    if(rtwin(WINEND))
    {
        csr_x = rtwin(CSRX)+1;
        csr_y++;
    }
    
    /* same as above, but it scrolls the window */
    if (rtwin(WINSCROLL)) {
      scwin(currwin);
      /*
      csr_x = rtwin(CSRX)+1;
      csr_y = rtwin(CSRY2)-1;
      */
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
    move_csr();
    
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
  char c[5];
  int i,tmp;
  for (i=0;i<5;++i) {
    c[i]='x';
  }
  i=4;
  while (x>=10) {
    tmp=x%10;
    c[i]='0'+tmp;
    x=(x-tmp)/10;
    --i;
  }
  tmp=x;
  c[i]='0'+tmp;
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
  textmemptr = (unsigned short *)0xB8000;
  txtclr(BLACK,BLACK);
  cls();
}
