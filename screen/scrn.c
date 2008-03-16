#include "system.h"

unsigned short *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;


void scroll(void)
{
    unsigned blank, temp;

    /* A blank is defined as a space... we need to give it
    *  backcolor too */
    blank = 0x20 | (attrib << 8);

    /* Row 25 je posledni, musime "soupnout" display */
    if(csr_y >= 25)
    {
        /* Move the current text chunk that makes up the screen
        *  back in the buffer by a line */
        temp = csr_y - 25 + 1;
        memcpy (textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);

        /* Finally, we set the chunk of memory that occupies
        *  the last line of text to our 'blank' character */
        memsetw (textmemptr + (25 - temp) * 80, blank, 80);
        csr_y = 25 - 1;
	move_csr();
    }
}

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

/* Put a single character on the screen */
void putch(unsigned char c)
{
    unsigned short *where;
    unsigned att = attrib << 8;

    /* funkce pro reseni 'backmezery' :) */
    if(c == 0x08)
    {
      if ((rtwin(CSRX)+1)<csr_x) {
	csr_x--;
	putch(' ');
	csr_x--; /* reseni logicke chyby : cursor se nejprve vrati, ale psanim mezery se zase posune dopredu, je tedy treba opet skocit dozadu */
      } else { /* else je nutne, dalsi logicka chyba, pokud by zde else nebylo, smazou se 2 mezery za sebou */

      if (((rtwin(CSRX)+1)==csr_x)&&((rtwin(CSRY)+1)!=csr_y)) {
        /* volano pokud jsme na kraji radku */
	csr_x=rtwin(CSRX2)-1;
	--csr_y;
	putch(' ');
	csr_x=rtwin(CSRX2)-1;
	--csr_y; /* stejny trik jako nahore */
      }
      }
    }
    /* taby, posune se na misto delitelne 8 */
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
    /* jednoduche, proste dalsi radek :) */
    else if(c == '\n')
    {
        csr_x = rtwin(CSRX)+1;
        csr_y++;
    }
    /* jde do tuheho, tahle funkce vytiskne charakter !! */
    else if(c >= ' ')
    {
        /*int temp_x,temp_y;
        temp_x=wherewin(CSRX);
        temp_y=wherewin(CSRY);
	csr_x=temp_x;
	csr_y=temp_y;*/
	where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;	/* Character AND attributes: color */
        csr_x++;
    }

    /* pokud se kurzor 'dotkne' konce okna, prehodit ho na new line */
    if(rtwin(WINEND))
    {
        csr_x = rtwin(CSRX)+1;
        csr_y++;
    }
    
    /* stejne jako ^^, ale jedna se o dolni okraj a jeste posune celou obrazovku nahoru */
    if (rtwin(WINSCROLL)) {
      scwin(currwin);
      /* tyto dva prikazy budou v platnosti az kdyz se okno opravdu posune, ne jen smaze...
      csr_x = rtwin(CSRX)+1;
      csr_y = rtwin(CSRY2)-1;
      */
    }

    move_csr();
  
    
}

/* stejne jako putch, ale pouzivane pri tvorbe oken, malo pada :D */
void putcha(unsigned char c)
{
    unsigned short *where;
    unsigned att = attrib << 8;

    /* Handle a backspace, by moving the cursor back one space */
    if(c == 0x08)
    {
        if(csr_x != 0) csr_x--;
    }
    /* Handles a tab by incrementing the cursor's x, but only
    *  to a point that will make it divisible by 8 */
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
    /* We handle our newlines the way DOS and the BIOS do: we
    *  treat it as if a 'CR' was also there, so we bring the
    *  cursor to the margin and we increment the 'y' value */
    else if(c == '\n')
    {
        csr_x = 0;
        csr_y++;
    }
    /* Any character greater than and including a space, is a
    *  printable character. The equation for finding the index
    *  in a linear chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    else if(c >= ' ')
    {
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;	/* Character AND attributes: color */
        csr_x++;
    }

    /* If the cursor has reached the edge of the screen's width, we
    *  insert a new line in there */
    if(csr_x >= 80)
    {
        csr_x = 0;
        csr_y++;
    }
    move_csr();
    
}

/* tisknuti stringu pomoci putch */
void puts(unsigned char *text)
{
    int i;

    for (i = 0; i < strlen(text); i++)
    {
        putch(text[i]);
    }
}

/* tisknuti integeru , puti jako PUT Integer*/
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
  /* nasleduje vlastni tisk */
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

/* vymaze display, a nastavi pointer na VGA pamet */
void i_video(void)
{
  textmemptr = (unsigned short *)0xB8000;
  txtclr(BLACK,BLACK);
  cls();
}

/* pozdrav, atp. :) */
void i_hello(void)
{
  puts("HoubOS loaded!\n");
  txtclr(2,4);
  puts("Tohle by melo byt v jine barve...\n");
  txtclr(LIGHT_BLUE,LIGHT_RED);
  puts("Jeste jina barva... \n");
}
