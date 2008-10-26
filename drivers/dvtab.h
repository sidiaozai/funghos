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
#ifndef DVTAB_H
#define DVTAB_H

/* general stuff to make calling functions more readable */
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* names of services */

enum {Init,Read,Write,Getc,Putc,Seek};
#define DV_SRV 6

typedef struct dvsw {
	char *dvname;
	int (*dvproc[DV_SRV])(struct dvsw*,...);
	int dvnum;
	int dviirq, dvoirq; /* input IRQ, output IRQ */
	void (*iinterrupt)(struct regs *r);
	void (*ointerrupt)(struct regs *r);
	struct dvsw *next;
};

extern struct dvsw *dvtab;

#endif
