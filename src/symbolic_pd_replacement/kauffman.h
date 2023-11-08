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
#ifndef KAUFFMAN_H
#define KAUFFMAN_H

/*  The algorithm is exponential in crossings. The crossings need to fit in   *
 *  the width of an integer, which is usually 32-bits.                        */
#define MAX_CROSSINGS (32)

/*  Given a knot with n crossings, bound is (n-1) + (n+1) = 2n. Lower bound   *
 *  is -(n+1). Max size of coefficient array is then 3n + 2.                  */
#define MAX_POLY_SIZE (3 * MAX_CROSSINGS + 2)

/*  The zeroth entry of the array corresponds to the minimum degree. Use this *
 *  shift to correctly compute the degree corresponding to the zeroth element.*/
#define DEGREE_SHIFT (MAX_CROSSINGS + 1)

/*  Minimum and maximum possible degrees for the Kauffman bracket for knot    *
 *  diagrams with up to MAX_CROSSINGS number of crossings.                    */
#define MIN_DEGREE (-(MAX_CROSSINGS + 1))
#define MAX_DEGREE (2 * MAX_CROSSINGS)

struct ordered_pair {
    unsigned int dat[2];
};

struct crossing {
    unsigned int dat[4];
};

struct knot {
    unsigned int number_of_crossings;
    struct crossing *index;
};

typedef unsigned char crossing_type;
typedef unsigned char crossing_sign;

struct gauss_code {
    unsigned int number_of_crossings;
    crossing_sign *sign;
    crossing_type *type;
    unsigned int *crossing_number;
};

struct affine_term {
    struct ordered_pair dat[2][2];
};

struct chain {
    struct ordered_pair *current;
    struct chain *previous;
    struct chain *next;
};

struct laurent_polynomial {
    signed int *coeffs;
    signed int lowest_degree;
    signed int highest_degree;
};

extern struct knot knot_from_gauss_code(const struct gauss_code *C);
extern void pop_chain(struct chain *c);
extern void simplify_chain(struct chain *c);
extern void print_chain(const struct chain *c);
extern unsigned int chain_length(const struct chain *c);
extern unsigned int hamming_weight(unsigned int n);
extern struct laurent_polynomial kauffman_bracket(const struct knot *K);
extern struct affine_term *get_affine_terms(const struct knot *K);
extern void print_poly(const struct laurent_polynomial *P);
extern void print_knot(const struct knot *K);
extern struct laurent_polynomial jones(const struct knot *K);
extern struct laurent_polynomial normalized_jones(const struct knot *K);

extern void
add_kauffman_summand(unsigned int cycles,
                     unsigned int weight,
                     unsigned int degree_shift,
                     signed int *coeffs_array);

extern void
add_normalized_kauffman_summand(unsigned int cycles,
                                unsigned int weight,
                                unsigned int degree_shift,
                                signed int *coeffs_array);

extern struct laurent_polynomial
kauffman_bracket_from_data(const signed int *data);

extern void
jones_normalization(const struct knot *K, struct laurent_polynomial *P);

extern void
set_affine_term_from_crossing(struct affine_term *a, const struct crossing *c);

extern struct laurent_polynomial
normalized_kauffman_bracket(const struct knot *K);

extern unsigned int
circle_count(struct affine_term *terms,
             unsigned int len,
             unsigned int ind);

#endif
