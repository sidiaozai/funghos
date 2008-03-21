#include <system.h>
#include <stdio.h>
#include "paging.h"



void i_paging() {
  unsigned long *page_dir = (unsigned long *)0x9C000;
  unsigned long *page_table = (unsigned long *) 0x9D000;
  unsigned long address = 0; // holds the physical address of a page
  register unsigned int i;

 // map the first 4MB of memory
  for (i=0; i<1024; i++) {
    page_table[i] = address | 3; // attribute set to: supervisor level, read/write, present(011 in binary)
    address = address + 4096;
  }

  // fill the first entry of the page directory
  page_dir[0] = page_table; // attribute set to: supervisor level, read/write, present(011 in binary)
  page_dir[0] = page_dir[0] | 3;
  for(i=1; i<1024; i++)
  {
    page_dir[i] = 0 | 2; // attribute set to: supervisor level, read/write, not present(010 in binary)
  };
  write_cr3(page_dir); // put that page directory address into CR3
  write_cr0(read_cr0() | 0x80000000); // set the paging bit in CR0 to 1
}
