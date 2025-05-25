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

/*Symbolic constants for yes and no*/
enum {YES, NO};

/*Functions to safely use malloc, calloc, and free*/
void* safe_malloc(size_t);
void* safe_calloc(size_t, size_t);
void safe_free(void*);

/*Struct for laurent polynomial; stores coefficients, highet, and lowest degrees of polyonmial*/
struct laurent_polynomial {
	signed int lowest_degree;
	signed int highest_degree;
	signed int* coeffs;
};

struct laurent_polynomial initialize_polynomial(void);
void adjust_polynomial_degree(struct laurent_polynomial*);
void print_polynomial(struct laurent_polynomial*, char);

/*Struct for crossing in PD notation; first entry of data is the undercrossing which points at
the crossing (when the knot is given an orientation), and then lists arcs in clockwise order
(this is different from many other PD codes, which go in counterclockwise order) */
struct crossing {
	int data[4];
};

int crossing_position(int, struct crossing*);
int is_crossing_consecutive(struct crossing*, int*, int, int);

/*Struct for knot in PD notation; contains number of crossings and data of all crossings */
struct knot {
	int number_of_crossings;
	struct crossing* crossings;
};

struct knot make_knot(int, struct crossing*);
struct laurent_polynomial kauffman_polynomial(struct knot*);
struct laurent_polynomial jones_polynomial(struct knot*);

/*Struct for boundary point of a tangle; contains the number on the strand passing through
the boundary point, and pointers to the boundary point of the strand paired with it, as well
as the previous (left) and next (right) boundary points on the tangle*/
struct boundary_point {
	int strand_number;
	struct boundary_point* strand_pair;
	struct boundary_point* previous;
	struct boundary_point* next;
};

struct boundary_point* insert_boundary_point(int, struct boundary_point*, struct boundary_point*, struct boundary_point*);
void delete_boundary_point(struct boundary_point*);
void pair_strands(struct boundary_point*, struct boundary_point*);
void swap_strand_pairs(struct boundary_point*, struct boundary_point*);

/*Struct for tangle used for this algorithm; stores the number of boundary points, first 
boundary point (can be chosen arbitrarily), whether the tangle has a crossing or knot, and
if yes, the strands around that crossing, in the same order as the arcs in PD notation*/
struct specialized_tangle {
	int number_of_boundary_points;
	struct boundary_point* first_boundary_point;
	int has_crossing;
	struct boundary_point** crossing_points;
};

struct specialized_tangle make_tangle(int, struct boundary_point*, int, struct boundary_point**);
struct specialized_tangle copy_tangle(struct specialized_tangle);
int tangle_index(struct specialized_tangle*);

/*Struct for summand when expressing the kauffman bracket polynomial of a portion of a knot diagram
(where we express the summand as a polynomial times a basis tangle); contains data for the number of
coefficients, highest degree, actual coefficients (where each term has degree 4 less than the term with
the previous coefficient), sign in front of the polynomial, and the tangle*/
struct kauffman_summand {
	int number_of_coeffs;
	int highest_degree;
	int* coeffs;
	int sign;
	struct specialized_tangle basis_tangle;
};

struct kauffman_summand make_kauffman_summand(int, int, int*, int, struct specialized_tangle);
struct kauffman_summand* copy_kauffman_summand(struct kauffman_summand*);
void add_crossing(struct kauffman_summand*, struct crossing*, int);
int remove_twist(struct kauffman_summand*, struct boundary_point*, struct crossing*, int, int, int);
void remove_circle(struct kauffman_summand*);
void smooth_crossing(struct kauffman_summand*, int);
void add_to_kauffman_summand(struct kauffman_summand*, struct kauffman_summand*);
void add_to_kauffman_summand_collection(struct kauffman_summand**, struct kauffman_summand*);

/*Struct for stack; stores elements of the stack and the next free position*/
struct stack {
	int* elements;
	int free_position;
};

struct stack make_stack(int);
void push_stack(struct stack*, int);
int pop_stack(struct stack*);
int peek_stack(struct stack*);

/*Struct for knot in DT code; contains the DT code of the knot and the number of crossings*/
struct DT_knot {
	char* DT_code;
	int number_of_crossings;
};

struct DT_knot make_DT_knot(char*);
struct knot DT_to_PD(struct DT_knot);
int DT_letter_to_number(char);
int* copy_array(int*, int);
int array_position(int*, int, int);
void reverse_array(int*, int, int);
#endif
