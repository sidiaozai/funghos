#ifndef STDIO_H
#define STDIO_H



#define TRUE 1
#define FALSE 0



typedef enum {
  BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHT_GREY, DARK_GREY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN, LIGHT_RED, LIGHT_MAGENTA, LIGHT_BROWN, WHITE
} COLORS;



extern void putch(unsigned char c);

extern void puts(unsigned char *text);

extern void puti(int x);

extern void txtclr(unsigned char forecolor, unsigned char backcolor);

extern char getchar();

extern char *gets(char *string, int max);




#endif
