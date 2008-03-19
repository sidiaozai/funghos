#ifndef KB_H
#define KB_H

#include <system.h>
#include <stdio.h>
#include "kbmap.h"

typedef struct {
  unsigned shift :1;
} KB_FLAGS;

extern KB_FLAGS kb_flags;

#endif
