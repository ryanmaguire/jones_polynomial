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
 
 //put all structs and functions in a header file - Hansen
#ifndef SKEIN_TEMPLATE_H
#define SKEIN_TEMPLATE_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_CROSSINGS (32)
#define MAX_POLY_SIZE (4 * MAX_CROSSINGS + 1)
#define DEGREE_SHIFT (2 * MAX_CROSSINGS)
#define ALPHA_DEGREE (-2)
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

enum {UNDER, OVER};

struct Gauss {// Give crossings, sign, over/under. Seems like you can do this in a matrix...
    int crossings; //number of crossings.
    int components; //number of components in link
    int* sizecomp; //gives sizes of each component
    int*** matrix;
    int splices;
    /* components # of matrices....
    (Each matrix has three rows: Top row gives crossing numbers )
    second row gives over/under crossing (Over = one, Under = zero)
    third row gives +/-.*/
    int startcross; /*starting crossing*/
    int ovorun;//overcrossing or undercrossing for startcross??
    int sign; //sign of startcross (+/- 1)
};

int isitsmaller(struct Gauss);
struct Gauss splice(struct Gauss);
struct Gauss virtue(struct Gauss);
void free_gauss(struct Gauss);
int writhe(struct Gauss);

//Added everything below to work with laurent polynomials - Hansen
struct laurent_polynomial {
    signed int lowest_degree;
    signed int highest_degree;
    signed int* coeffs;
};

struct laurent_polynomial initialize_polynomial(void);
struct laurent_polynomial make_polynomial(int, int, int*);
struct laurent_polynomial add_polynomials(struct laurent_polynomial, struct laurent_polynomial);
struct laurent_polynomial subtract_polynomials(struct laurent_polynomial, struct laurent_polynomial);
struct laurent_polynomial multiply_polynomials(struct laurent_polynomial, struct laurent_polynomial);
struct laurent_polynomial polynomial_power(struct laurent_polynomial, int);
void scale_polynomial(struct laurent_polynomial*, int);
void adjust_polynomial_degree(struct laurent_polynomial*);
void print_polynomial(struct laurent_polynomial*, char);
struct laurent_polynomial Jones_Partial(struct Gauss);
struct laurent_polynomial JONES(struct Gauss);
#endif
