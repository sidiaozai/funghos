#include <system.h>
#include <mem/paging.h>
#include <mem/mem.h>



void *malloc(unsigned int size)
{
  /* 1/ find a free header
     2/ mark it as used
     3/ twidling with pointerz
     4/ return its address
   */

  HEADER *header_curr = FIRST_HEADER;

  while ((!header_curr->free)&&(header_curr->next-header_curr>=size))
  {
    header_curr =& header_curr->next;
  }
  header_curr->free=FALSE;
  unsigned int tmp = header_curr->next;
  header_curr->next=header_curr+size+1;
  HEADER *header_next;
  header_next = header_curr->next;
  header_next->next = tmp;
  header_next->free = TRUE;
  return header_curr+1;
}
