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

#define NEXT(data_index_macro) ((data_index_macro + 1) % 4)
#define OPP(data_index_macro) ((data_index_macro + 2) % 4)
#define PREV(data_index_macro) ((data_index_macro + 3) % 4)

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
//
//      3
//      |
// 0 -- | --> 2
//      |
//      1
//
// All array numberings used below are consistent with the diagram above
struct crossing {
	int status;
	struct crossing* data[4]; // Array of pointers to neighboring crossings
	int ports[4]; // Which port is connected to which neighboring crossing
	int underdirection; // Current direction of understrand
	int overdirection; // Gives sign (1 = positive, 3 = negative)
	int over_component; // Component containing overstrand
	int under_component; // Component containing unders
};

struct link {
	int number_of_components;
	int* number_of_crossings_in_components;
	struct crossing** first_crossing_in_components; //Pointers to crossings
};
extern struct knot make_link(const int number_of_components, const int* number_of_crossings_in_components, const struct crossing** first_crossing_in_components);

extern void smooth_crossing(struct link* K, struct crossing* C, const int smoothing_type);
extern void reidemeister_move_i(struct link* L);
extern void reidemeister_move_ii(struct link* L);

int writhe(struct link* L);
int jones_polynomial(struct link* L);
int kauffman_bracket_polynomial(struct link* L);

int triple_search(struct link* L);
int gamma_search(struct link* L);
int bigon_search(struct link* L);

// main recursion function:
//   takes in a link and a polynomial
// runs through pattern search functions, calling them in order
// as soon as a pattern search function returns >=0, call smoothing functions

// each pattern search function:
//   takes in a link, and searches through it
//   if it finds the pattern, return the index of the link component where the
//		pattern occurs and modify the corresponding element in first_crossing_in_components
//		the location of the desired smoothing
//   if it doesnt find the pattern, return -1

// 0 smoothing function:
//    takes in a link and applies a 0 smoothing.
// Case 1: over_component = under_component --> 
	// 2 cases: K_0 smoothing splits, other smoothing keeps it as one component
// Case 2: over component != undercomponent --> both smoothings merge
// 1 smoothing function:
//	  takes in a link and applies a 1 smoothing.
// Case 1: over_component = under_component --> 
	// 2 cases: K_0 smoothing splits, other smoothing keeps it as one component
// Case 2: over component != undercomponent --> both smoothings merge


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
/*struct knot {
	int number_of_crossings;
	struct crossing* first_crossing;
};
extern struct knot make_knot(int number_of_crossings, struct crossing* first_crossing);
extern void smooth_crossing(struct knot* K, struct crossing* C, int smoothing_type);
extern void reidemeister_move_ii(struct knot* K);*/
#endif
