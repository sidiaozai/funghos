#include <system.h>
#include <stdio.h>
#include "cmd.h"



void cmd(); /* loop waiting for commands */
void help(); /* help message */
void cmdexec(char *string); /* execute commands */
void cmd_install(); /* 'install' the cmd-line */



void cmd() {
  char cmd_buf[CMD_BUFLEN];
  while (strcmp(cmd_buf,CMD_EXIT)!=0) {
    gets(cmd_buf,CMD_BUFLEN);
    cmdexec(cmd_buf);
    strcpy(cmd_buf,"");
  }
}



void help() {
  puts("Avaible commands are:\n");
  puts("help -- displays this message\n");
  puts("mkwin -- creates a new window\n");
  puts("paging -- enables paging\n");
  puts("pgfault -- do a page fault\n");
  puts("stopwatch -- the name says it all\n");
}



void do_page_fault()
{
  unsigned int *ptr = (u32int*)0xA0000000;
  unsigned int do_page_fault2 = *ptr;
}



/* volana kdyz je stisknut Enter, mela by vykonavat prikazy */
void cmdexec(char *cmd_buf) {
  if (strcmp(cmd_buf,"help")==0) {help();return;}
  if (strcmp(cmd_buf,"stopwatch")==0) {stopwatch();return;}
  if (strcmp(cmd_buf,"mkwin")==0) {mkwin(0,0,0,0,0);return;}
  if (strcmp(cmd_buf,"paging")==0) {i_paging();return;}
  if (strcmp(cmd_buf,"pgfault")==0) {do_page_fault();return;}
  if (strcmp(cmd_buf,"floppy")==0) {i_floppy();return;}
  puts("Command not found.\n");
}



void cmd_install() {
  mkwin(0,0,0,0,2);
  puts("Welcome to ");puts(VERSION);putch('\n');
  cmd();
}
