#include <system.h>
#include <mem/paging.h>
#include <mem/mem.h>



void *free(unsigned int addr)
{
  HEADER *header_curr = addr;
  header_curr->free = TRUE;
}