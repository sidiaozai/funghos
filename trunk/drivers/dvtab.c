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
#include "dvtab.h"

#define error(string) puts(string) /* tmp */


struct dvsw *dvtab = NULL;

int gen_dvnum();
void dvtab_add(char *name,int (*dvproc[DV_SRV])(struct dvsw*,...),
				int iirq,int oirq,void (*interrupt)(struct regs *r),
				void (*ointerrupt)(struct regs *r),int init);

void dvtab_init()
{
  dvtab = NULL;
}


void dvtab_add(char *name,int (*dvproc[DV_SRV])(struct dvsw*,...),
				int iirq,int oirq,void (*iinterrupt)(struct regs *r),
				void (*ointerrupt)(struct regs *r),int init) {

  int i;
  struct dvsw *dvtmp,*dvtmp2;
  if ((dvtmp = malloc(sizeof(struct dvsw)))==NULL)
    error("Can't allocate memory for dvsw structure for device!\n");

  dvtmp->next = NULL;
  dvtmp->dvnum = gen_dvnum();
  dvtmp->dvname = name;
  dvtmp->dviirq = iirq;
  dvtmp->dvoirq = oirq;
  dvtmp->iinterrupt = iinterrupt;
  dvtmp->ointerrupt = ointerrupt;
  for (i = 0; i<DV_SRV; i++)
    dvtmp->dvproc[i] = dvproc[i];
  
  /* now comes the easy part, just put this somewhere in the linked list */
  dvtmp2 = dvtab;
  
  while (dvtmp2)
    dvtmp2 = dvtmp2->next;
  
  dvtmp2 = dvtmp;
  if (!init) return; /* for devices that don't want to be initialized */
  /* now for the others */
  dvproc[Init](dvtmp);
  irq_install_handler(iirq, iinterrupt);
  if (iirq!=oirq) irq_install_handler(oirq, ointerrupt);
}

int gen_dvnum()
{
  static int i = 1;
  return i++;
}
