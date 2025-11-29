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
 *  with jones_polynomial.  If not, see <https://www.gnu.org/licenses/>.      *
 ******************************************************************************/
#ifndef KAUFFMAN_IMPL_H
#define KAUFFMAN_IMPL_H

#include <stdlib.h>
#include <stdio.h>

/*The maximum possible number of crossings a knot can have for this algorithm */
#define MAX_CROSSINGS (32)
/*The maximum size of the jones/kauffman bracket polynomial for such a knot, since for a knot 
with n crossings, a hard limit for the smallest and largest degrees are -3n and 3n */
#define MAX_POLY_SIZE (6 * MAX_CROSSINGS + 1)
/*Degree which the coefficients of the laurent polynomials are shifted by, so the ith number
in the coefficients array is the coefficient of the term with degree i - DEGREE_SHIFT */
#define DEGREE_SHIFT (3 * MAX_CROSSINGS)

/*Macros to find min and max of two numbers*/
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

/* booleans */
enum boolean { FALSE, TRUE };

/*Functions to safely use malloc, calloc, and free*/
extern void* safe_calloc(const size_t n, const size_t size);
extern void* safe_malloc(const size_t size);
#define SAFE_FREE(pointer_SAFE_FREE_MACRO) if (pointer_SAFE_FREE_MACRO) {free(pointer_SAFE_FREE_MACRO);} pointer_SAFE_FREE_MACRO = NULL

/*Struct for laurent polynomial; stores coefficients, highet, and lowest degrees of polyonmial*/
struct laurent_polynomial {
	signed int lowest_degree;
	signed int highest_degree;
	signed int* coeffs;
};

extern struct laurent_polynomial* initialize_polynomial(void);
extern void adjust_polynomial_degree(struct laurent_polynomial* P);
extern void print_polynomial(const struct laurent_polynomial* const P, const char c);

/*Struct for crossing in PD notation; first entry of data is the undercrossing which points at
the crossing (when the knot is given an orientation), and then lists arcs in clockwise order
(this is different from many other PD codes, which go in counterclockwise order) */
struct crossing {
	int data[4];
};

extern int crossing_position(const int strand_number, const struct crossing* const C);
extern int is_crossing_consecutive(const struct crossing* const C, const int* const boundary_point_positions, const int strands_present, const int tangle_width);

/*Struct for knot in PD notation; contains number of crossings and data of all crossings */
struct knot {
	int number_of_crossings;
	struct crossing* crossings;
};

extern struct knot* make_knot(const int number_of_crossings, struct crossing* const crossings);
extern struct laurent_polynomial* kauffman_polynomial(const struct knot* const K);
extern struct laurent_polynomial* jones_polynomial(const struct knot* const K);

/*Struct for boundary point of a tangle; contains the number on the strand passing through
the boundary point, and pointers to the boundary point of the strand paired with it, as well
as the previous (left) and next (right) boundary points on the tangle*/
struct boundary_point {
	int strand_number;
	struct boundary_point* strand_pair;
	struct boundary_point* previous;
	struct boundary_point* next;
};

extern struct boundary_point* insert_boundary_point(const int strand_number, struct boundary_point* const strand_pair, struct boundary_point* const previous, struct boundary_point* const next);
extern void delete_boundary_point(const struct boundary_point* const BP);
extern void pair_strands(struct boundary_point* const BP1, struct boundary_point* const BP2);
extern void swap_strand_pairs(struct boundary_point* const BP1, struct boundary_point* const BP2);

/*Struct for tangle used for this algorithm; stores the number of boundary points, first 
boundary point (can be chosen arbitrarily), whether the tangle has a crossing or knot, and
if yes, the strands around that crossing, in the same order as the arcs in PD notation*/
struct specialized_tangle {
	int number_of_boundary_points;
	struct boundary_point* first_boundary_point;
	enum boolean has_crossing;
	struct boundary_point* crossing_points[4];
};

extern struct specialized_tangle* make_tangle(const int number_of_boundary_points, struct boundary_point* const first_boundary_point, const enum boolean has_crossing, struct boundary_point** const crossing_points);
extern struct specialized_tangle* copy_tangle(const struct specialized_tangle* const T);
extern int tangle_index(const struct specialized_tangle* const T);

/*Struct for summand when expressing the kauffman bracket polynomial of a portion of a knot diagram
(where we express the summand as a polynomial times a basis tangle); contains data for the number of
coefficients, highest degree, actual coefficients (where each term has degree 4 less than the term with
the previous coefficient), sign in front of the polynomial, and the tangle*/
struct kauffman_summand {
	int number_of_coeffs;
	int highest_degree;
	int* coeffs;
	int sign;
	struct specialized_tangle* basis_tangle;
};

extern struct kauffman_summand* make_kauffman_summand(const int number_of_coeffs, const int highest_degree, int* const coeffs, const int sign, struct specialized_tangle* const B);
extern struct kauffman_summand* copy_kauffman_summand(const struct kauffman_summand* const P);
extern void add_crossing(struct kauffman_summand* const P, const struct crossing* const C, const int strands_present);
extern enum boolean remove_twist(struct kauffman_summand* const P, struct boundary_point* BP, const struct crossing* const C, const int num_present, const int position, const enum boolean has_first_boundary_point);
extern void remove_circle(struct kauffman_summand* const P);
extern void smooth_crossing(struct kauffman_summand* const P, const int smoothing);
extern void add_to_kauffman_summand(struct kauffman_summand* const P, const struct kauffman_summand* const Q);
extern void add_to_kauffman_summand_collection(struct kauffman_summand** const summand_collection, struct kauffman_summand* const P);

/*Struct for knot in DT code; contains the DT code of the knot and the number of crossings*/
struct DT_knot {
	char* DT_code;
	int number_of_crossings;
};

extern struct DT_knot* make_DT_knot(const char* const DT_code);
extern struct knot* DT_to_PD(const struct DT_knot* const K);
extern int DT_letter_to_number(const char c);
#endif
