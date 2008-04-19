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



#ifndef STDIO_H
#define STDIO_H



#define TRUE 1
#define FALSE 0

/* Colors for the video memory */
#define BLACK   0x0
#define BLUE    0x1
#define GREEN   0x2
#define CYAN    0x3
#define RED     0x4
#define MAGENTA 0x5
#define BROWN   0x6
#define LIGHT_GREY  0x7
#define DARK_GREY   0x8
#define LIGHT_BLUE  0x9
#define LIGHT_GREEN 0xA
#define LIGHT_CYAN  0xB
#define LIGHT_RED   0xC
#define LIGHT_MAGENTA 0xD
#define YELLOW     0xE
#define WHITE      0xF


#define TXTFOREGROUND BLUE
#define TXTBACKGROUND LIGHT_GREY


extern void putch(unsigned char c);

extern void puts(unsigned char *text);

extern void puti(int x);

extern void putx(int x);

extern void txtclr(unsigned char forecolor, unsigned char backcolor);

extern char getchar();

extern char *gets(char *string, int max);

#endif
