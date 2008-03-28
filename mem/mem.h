#ifndef MEM_H
#define MEM_H


#define HEADER_SIZE   sizeof(HEADER)  // header_size in bytes
#define FIRST_HEADER  0x0


typedef struct header {
  unsigned free:1;      /* if set, that means that this block is free,
			 * so it can be used to allocate new memory.
			 */
  struct header *next;  /* this is simply a pointer to the next header,
			 * so malloc() can simply browse headers to find
			 * an empty one.
			 */
} HEADER;

#endif
