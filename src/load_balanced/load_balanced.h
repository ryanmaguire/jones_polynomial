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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BACK 0
#define RIGHT 1
#define FORWARD 2
#define LEFT 3

#define NEXT(data_index) ((data_index + 1) % 4)
#define OPP(data_index) ((data_index + 2) % 4)
#define PREV(data_index) ((data_index + 3) % 4)

/*Swap two variables*/
#define SWAP(temp, x, y) temp = x; x = y; y = temp

/* booleans*/
enum boolean { FALSE, TRUE };

/*Functions to safely use malloc, calloc, and free*/
extern void* safe_malloc(const size_t size);
extern void* safe_calloc(const size_t n, const size_t size);
#define SAFE_FREE(pointer) if (pointer) free(pointer); pointer = NULL

/*Struct for laurent polynomial; stores coefficients, highet, and lowest degrees of polyonmial*/
struct laurent_polynomial {
	signed int lowest_degree;
	signed int highest_degree;
	signed int* coeffs;
};

extern struct laurent_polynomial initialize_polynomial(void);
extern void print_polynomial(struct laurent_polynomial* P, char c);

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
struct bigon{
	struct crossing* C1;
	struct crossing* C2;
	int port1;
	int port2;
};
struct gamma{
	struct bigon B;
	struct crossing *C3;
	int port3;//Which things attach to the third crossing?
	int port4;//Which things attach to the third crossing?
};
extern struct crossing* make_crossing(int status, struct crossing** data, int *ports,int id);
extern struct crossing* next_crossing(struct crossing* C, int direction);
extern void reverse(struct crossing* C);
extern void delete_crossing(struct crossing* C, int direction);

/*Struct for knot in PD notation; contains number of crossings and a pointer to its first 
crossing */
struct knot {
	int number_of_crossings;
	struct crossing* first_crossing;
};
extern struct knot make_knot(int number_of_crossings, struct crossing* first_crossing);
extern void smooth_crossing(struct knot* K, struct crossing* C, int smoothing_type);
extern void reidemeister_move_ii(struct knot* K);
#endif
