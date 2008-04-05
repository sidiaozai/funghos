#include <system.h>
#include <mem/paging.h>
#include <mem/mem.h>
#include <stdio.h>



void palloc(unsigned int start_addr, unsigned int end_addr)
{
  /* vynulovat poslednich dvanact bitu v start_addr i end_addr
   * velikost je 32 bitu, tj bitu 0-11 vcetne je treba smazat
   */
  start_addr &= 0xFFFFF000;
  end_addr &= 0xFFFFF000;
  
  unsigned int start_page = start_addr / 0x1000;
  unsigned int end_page = end_addr / 0x1000;

  /* ted je treba zjistit v jake page table se dane page nachazeji
   * to udelame vydelenim 0x1000 jeste jednou
   */

  unsigned int start_table = start_page / 0x1000;
  unsigned int end_table = end_page / 0x1000;

  start_page %= 0x1000;
  end_page %= 0x1000;
  
  /* nyni mame v start_page a end_page jen offset page v table */

  /* nastavit start_talbe i end_table bity "used" na TRUE, pokud nejsou
   * present, priradit jim fyzickou adresu
   */
  
  if ( ! (page_dir[start_table] & 0x3) )
  {
    txtclr(YELLOW,TXTBACKGROUND);
    puts("We need to allocate a new page table.(0x3)\n");
    txtclr(RED,TXTBACKGROUND);
    puts("Requested page table : "); puti(start_table); putch('\n');
    txtclr(TXTFOREGROUND,TXTBACKGROUND);
    puti(page_dir[start_table]);
    putch('\n');
    puti(page_dir[start_table] & 0x3);
    for (;;)
      ;
  }

  if (start_table!=end_table)
  {
    if (page_dir[end_table]==NULL)
    {
      txtclr(YELLOW,TXTBACKGROUND);
      puts("We need to allocate a new page table.\n");
      for (;;)
	;
    }
  }
  
  unsigned long *p_start_table = page_dir[start_table];

    register unsigned int i;

    for (i=start_page; i<=end_page; i++)
    {
      if ( ! (p_start_table[i] & 0x3) )
      {
	/* opet najit volnou fyzickou stranku, spocitat jeji
	 * adresu, zapsat ji a dat nejake flagy
	 */
	unsigned int page_num;
	register unsigned int i=0;
	unsigned int j=0;
	unsigned int i_max = RAM_kb/32/sizeof(unsigned long);

	while ((RAM_pages[i] == 0xFFFFFFFF) && (i<=i_max))
	{
	  i++;
	}

      if (i<=i_max)
      {
	
	while ( (RAM_pages[i] >> j) & 1 )
	{
	  j++;
	}

	RAM_pages[i] |= 2^j;
	
	unsigned int page = page_num*0x1000;
	p_start_table[i] = page | 7; // classic flags : user,r/w,present
      } else {

	  txtclr(RED,TXTBACKGROUND);
	  puts("No free pages!\n");
	  puts("Halting System.\n");
	  for (;;)
	    ;
      }
      }
    }
}
