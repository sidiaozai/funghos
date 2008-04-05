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



#ifndef WIN_H
#define WIN_H

#define SYSLINE 1 /* border (up) */
#define WINSIZEX 40  /* default <-X-> */
#define WINSIZEY 15  /* default <-Y-> */
#define WINMAX 10 /* how many windows can be opened - linked list later */
#define BDFOREGROUND YELLOW
#define BDBACKGROUND BLUE
#define WINFOREGROUND 0
#define WINBACKGROUND 7
#define WINEND 2
#define WINSCROLL 3
#define CSRY2 4
#define CSRX2 5
/* CSRX & CSRY are defined in system.h */

/* ASCII values
 * used for borders / corners
 * of windows
 */
#define UPLEFTCORNER 201
#define UPRIGHTCORNER 187
#define UPBORDER 205
#define SIDEBORDER 186
#define DOWNBORDER UPBORDER
#define DOWNLEFTCORNER 200
#define DOWNRIGHTCORNER 188


#endif
