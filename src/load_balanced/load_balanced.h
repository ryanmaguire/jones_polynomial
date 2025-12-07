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
#include <assert.h>

#include "a_and_a_inverse.h"
#include "a_squared_plus_a_inverse_squared.h"

/* Minimum and maximum macros */
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

/* Swap two variables */
#define SWAP(type, x, y) do {type my_temp = x; x = y; y = my_temp;} while (0)

/* booleans*/
enum boolean { FALSE, TRUE };

/* Functions to safely use malloc, calloc, and free */
extern void* safe_malloc(const size_t size);
extern void* safe_calloc(const size_t n, const size_t size);
#define SAFE_FREE(pointer_SAFE_FREE_MACRO) if (pointer_SAFE_FREE_MACRO) {free(pointer_SAFE_FREE_MACRO);} pointer_SAFE_FREE_MACRO = NULL

#define MAX_CROSSINGS (32)
#define MAX_POLY_SIZE (6 * MAX_CROSSINGS + 1)
#define DEGREE_SHIFT (3 * MAX_CROSSINGS)

/* Struct for laurent polynomial; stores coefficients, highet, and lowest degrees of polyonmial */
struct laurent_polynomial {
	signed int lowest_degree;
	signed int highest_degree;
	signed int* coeffs; // length = MAX_POLY_SIZE
};

extern struct laurent_polynomial* initialize_polynomial(void);
extern void delete_polynomial(struct laurent_polynomial* P);
extern void print_polynomial(const struct laurent_polynomial* P, char c);
extern struct laurent_polynomial* add_polynomials(const struct laurent_polynomial* P, const struct laurent_polynomial* Q);
extern struct laurent_polynomial* multiply_polynomials(const struct laurent_polynomial* P, const struct laurent_polynomial* Q);

/* Struct for crossing in PD notation; first entry of data is the undercrossing which points at
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

#define BACK 0
#define RIGHT 1
#define FRONT 2
#define LEFT 3

#define NEXT(data_index_NEXT_MACRO) ((data_index_NEXT_MACRO + 1) % 4) // next crossing (+1)
#define OPP(data_index_OPP_MACRO) ((data_index_OPP_MACRO + 2) % 4) // opposite crossing (+2)
#define PREV(data_index_PREV_MACRO) ((data_index_PREV_MACRO + 3) % 4) // previous crossing (-1, or +3)

#define OVER_POS 1
#define OVER_NEG 3

struct crossing {
	int id;
	struct crossing* data[4]; // Array of pointers to neighboring crossings
	int ports[4]; // Which port is connected to which neighboring crossing
	int overdirection; // Gives sign (OVER_POS = positive, OVER_NEG = negative)
	int over_component; // Component containing overstrand
	int under_component; // Component containing understrand
};

extern struct crossing* make_crossing(const int id, struct crossing** const data, const int* ports, const int overdirection, const int over_component, const int under_component);
extern void delete_crossing(struct crossing* C); // DOES NOT UPDATE NEIGHBORING CROSSINGS
extern void pair_crossings(struct crossing* const C1, const int c1_index, struct crossing* const C2, const int c2_index);

struct link {
	int number_of_components; // Link components
	int* number_of_crossings_in_components; // Array of number of crossings in each link component, length = MAX_CROSSINGS
	struct crossing** first_crossing_in_components; // Array of pointers to a crossing in each link component, length = MAX_CROSSINGS
};
extern struct link* make_link(const int number_of_components, int* const number_of_crossings_in_components, struct crossing** const first_crossing_in_components);
extern struct link* copy_link(const struct link* L);
extern void print_link(struct link* const L, enum boolean redo_ids);

extern void smooth_crossing(struct link* L, struct crossing* C, const int smoothing_type);

extern enum boolean reidemeister_move_i(struct link* L);
extern enum boolean reidemeister_move_ii(struct link* L);
extern enum boolean null_gamma(struct link* L);
extern enum boolean null_triple(struct link* L);

extern int writhe(const struct link* L);
extern struct laurent_polynomial* jones_polynomial(struct link* L);
extern struct laurent_polynomial* kauffman_bracket_polynomial(struct link* L);

extern int triple_search(const struct link* L);
extern int gamma_search(const struct link* L);
extern int reidemeister_move_iii_search(const struct link* L);
extern int bigon_search(const struct link* L);

struct PD_crossing {
	int data[4];
};

struct PD_knot {
	int number_of_crossings;
	struct PD_crossing* crossings;
};

struct PD_knot* make_PD_knot(const int number_of_crossings, struct PD_crossing* crossings);
struct link* PD_to_algorithm_knot(const struct PD_knot* K);
#endif
