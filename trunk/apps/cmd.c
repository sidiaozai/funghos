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
#include <stdlib.h>
#include <mem/mem.h>
#include "cmd.h"



void cmd(); /* loop waiting for commands */
void help(); /* help message */
void help_dev(); /* developer's help message */
void cmdexec(char *string); /* execute commands */
void cmd_install(); /* 'install' the cmd-line */



void cmd() {
  char cmd_buf[CMD_BUFLEN];
  while (strcmp(cmd_buf,CMD_EXIT)!=0) {
    gets(cmd_buf); /* replace with fgets CMD_BUFLEN */
    cmdexec(cmd_buf);
    strcpy(cmd_buf,"");
  }
}



void help() {
  puts("Avaible commands are:\n");
  puts("floppy -- detect floppy drives\n");
  puts("help -- displays this message\n");
  puts("malloctest -- test the memory allocator, should hit an infinite loop. If not, please, report it\n");
  puts("mkwin -- creates a new window\n");
  puts("pgfault -- do a page fault\n");
  puts("ps2mouse -- get the last 3 bytes mouse sent\n");
  puts("speakeroff -- disable the PC speaker\n");
  puts("speakertest -- test the PC's speaker\n");
  puts("stopwatch -- the name says it all\n");
  puts("help_dev -- displays list of debug commands\n");
}


void help_dev()
{
  puts("This is a list of debug, potentionally insecure/damaging commands. Don't try them unless you know what you're doing.\n");
  puts("mkwin_ -- create a window at another portion of the screen\n");
  puts("irqwaitk -- wait for an irq from the keyboard\n");
}



void do_page_fault()
{
  unsigned int *ptr = (u32int*)0xA00000;
  unsigned int do_page_fault2 = *ptr;
}

void malloc2()
{
  puti(sizeof(HEADER));putch('\n');  /*4*/
  puti(sizeof(_HEADER));putch('\n'); /*8*/
  unsigned int *x,*y;
  char *string;
  string = (char *) malloc(40);
  strcpy(string, "dynamically allocated string\n");
  puts(string);

  while (1)
  {
    x=malloc(sizeof(unsigned int));
    y=malloc(sizeof(unsigned int));
    *x = 1;
    *y = 2;
    puts("x => ");puti(x);putch('\n');
    puts("y => ");puti(y);putch('\n');
    puts("*x=> ");puti(*x);putch('\n');
    puts("*y=> ");puti(*y);putch('\n');
    free(x);
    free(y);
  }
}

void malloc3()
{
  puts("Starting...");
  putch(186);
  putch('\n');
  puts("0000000");
  while (1)
  {
    unsigned int *x = malloc(sizeof(unsigned int));
    csr_x -= 7;
    puti(x);
  }
}


void beep2()
{
  puts("Enter \"speakeroff\" when your PC's speaker will annoy you.\n");
  beep(1000);
}


/* volana kdyz je stisknut Enter, mela by vykonavat prikazy */
void cmdexec(char *cmd_buf) {
  if (strcmp(cmd_buf,"help")==0) {help();return;}
  if (strcmp(cmd_buf,"help_dev")==0) {help_dev();return;}
  if (strcmp(cmd_buf,"stopwatch")==0) {stopwatch();return;}
  if (strcmp(cmd_buf,"mkwin")==0) {mkwin(0,0,0,0);return;}
  if (strcmp(cmd_buf,"pgfault")==0) {do_page_fault();return;}
  if (strcmp(cmd_buf,"floppy")==0) {i_floppy();return;}
  if (strcmp(cmd_buf,"malloctest")==0) {malloc2();return;}
  if (strcmp(cmd_buf,"mdebug")==0) {malloc3();return;}
  if (strcmp(cmd_buf,"mallocdebug")==0) {malloc_test();return;}
  if (strcmp(cmd_buf,"speakertest")==0) {beep2();return;}
  if (strcmp(cmd_buf,"speakeroff")==0) {nosound();return;}
  if (strcmp(cmd_buf,"malloc_test")==0) {malloc_test();return;}
  if (strcmp(cmd_buf,"mkwin_")==0) {mkwin(60,17,78,23);return;}
  if (strcmp(cmd_buf,"loop")==0) {while(1);}
  if (strcmp(cmd_buf,"irqwaitk")==0) {puts("waiting... ");irq_wait(1);puts("done\n");return;}
  puts("Command not found.\n");
}



void cmd_install() {
  screen_no_scroll=FALSE;
  mkwin(10,5,70,20);
  puts("Welcome to ");puts(VERSION);putch('\n');
  cmd();
}
