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
#include <mem/mem.h>
#include "paging.h"


unsigned long *page_dir = (unsigned long *)0x9C000;
unsigned long *page_table = (unsigned long *) 0x9D000;
unsigned long *page_table2 = (unsigned long *) 0x9E000;
unsigned long address = 0x0;



void pgfault_handler(struct regs *r)
{
  static unsigned int debug=1;

  unsigned int faulting_addr;
  __asm__ __volatile__ ("mov %%cr2, %0" : "=r" (faulting_addr));

  if (debug==0) {
    malloc_test();
  } else {

    int present   = !(r->err_code & 0x1); // Page not present
    int rw = r->err_code & 0x2;           // Write operation?
    int us = r->err_code & 0x4;           // Processor was in user-mode?
    int reserved = r->err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
    int id = r->err_code & 0x10;          // Caused by an instruction fetch?
    
    txtclr(RED,TXTBACKGROUND);
    puts("\nPage Fault!\n");
    txtclr(GREEN,TXTBACKGROUND);
    puts("( ");
    if (present) puts("present ");
    if (rw) puts("read-only ");
    if (us) puts("user-mode ");
    if (reserved) puts("reserved ");
    
    puts(")\n");
    
    txtclr(YELLOW,TXTBACKGROUND);
    putx(faulting_addr);
    
    putch('\n');
    
    txtclr(TXTFOREGROUND,TXTBACKGROUND);
    
    puts("System Halted!\n");
    for (;;)
      ;
  
  }
}

void i_paging() {
  register unsigned int i;

  idt_set_gate(14, (unsigned)pgfault_handler, 0x08, 0x8E);

 // map the first 4MB of memory
  for (i=0; i<1024; i++) {
    page_table[i] = address | 3; // attribute set to: supervisor level, read/write, present(011 in binary)
    address = address + 4096;
  }

  // fill the first entry of the page directory
  page_dir[0] = page_table; // attribute set to: supervisor level, read/write, present(011 in binary)
  page_dir[0] = page_dir[0] | 3;  // +1024 means "page table in use"
  for(i=1; i<1024; i++)
  {
    page_dir[i] = 0 | 3; // attribute set to: supervisor level, read/write, present(011 in binary)
  };
  write_cr3(page_dir); // put that page directory address into CR3
  write_cr0(read_cr0() | 0x80000000); // set the paging bit in CR0 to 1

  for (i=0; i<1024; i++) {
    page_table2[i] = address | 3; // attribute set to: user level, read/write, present(011 in binary)
    address = address + 4096;
  }
  page_dir[1] = page_table2;
  page_dir[1] = page_dir[1] | 3;
  
  malloc_test();

  struct header *header_curr = FIRST_HEADER;
  header_curr->used = 0;
  header_curr->next = END_OF_MEMORY;
}



void malloc_test() {
  register unsigned int i;
  for (i=0; i<1024; i++) {
    page_table2[i] = address | 3; // attribute set to: supervisor level, read/write, present(011 in binary)
    address = address + 4096;
  }
  page_dir[2] = page_table2;
  page_dir[2] = page_dir[1] | 3;
}
