/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of jones_polynomial.                                    *
 *                                                                            *
 *  jones_polynomial is free software: you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  jones_polynomial is distributed in the hope that it will be useful,       *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License along   *
 *
 *  with jones_polynomial.  If not, see <https://www.gnu.org/licenses/>.      *
 ******************************************************************************/
#ifndef LOAD_BALANCED_H
#define LOAD_BALANCED_H
#define BACK 0
#define RIGHT 1
#define FORWARD 2
#define LEFT 3
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Functions to safely use malloc, calloc, and free*/
extern void* safe_malloc(const size_t size);
extern void* safe_calloc(const size_t n, const size_t size);
#define SAFE_FREE(pointer) if (pointer) free(pointer); pointer = NULL

/*Struct for crossing in PD notation; first entry of data is the undercrossing which points at
the crossing (when the knot is given an orientation), and then lists crossings adjacent to it
in councterclockwise order */
struct crossing {
	int status;
	struct crossing* data[4];
	int ports[4]; //Which port is connected to which neighboring crossing
	int direction; //Current direction of travel when struct is reached
	int id;
};

extern struct crossing* make_crossing(int status, struct crossing** data, int *ports,int id);

/*Struct for knot in PD notation; contains number of crossings and a pointer to its first 
crossing */
struct knot {
	int number_of_crossings;
	struct crossing* first_crossing;
};
extern struct knot make_knot(int number_of_crossings, struct crossing* first_crossing);
#endif
