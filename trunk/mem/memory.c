#include <system.h>
#include <mem/paging.h>
#include <boot/multiboot.h>



unsigned int RAM_kb;
unsigned long *RAM_pages;



void i_memory(multiboot_info_t *mbd)
{
  if (mbd->flags & 1)
  {
    puts("\n mbd->mem_lower = ");
    puti((unsigned int) mbd->mem_lower);
    puts("KB\n mbd->mem_upper = ");
    puti((unsigned int) mbd->mem_upper);
    puts("KB\n both = ");
    puti((unsigned int) (mbd->mem_lower + mbd->mem_upper));
    puts("KB\n");
  }
  /* zjistit velikost RAM */
  RAM_kb = (unsigned int) (mbd->mem_lower) + (mbd->mem_upper);

  i_paging();

  RAM_pages = (unsigned long) malloc(RAM_kb/32);
}
