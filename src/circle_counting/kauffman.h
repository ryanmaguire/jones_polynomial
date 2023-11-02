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

/*  Crossing signs are negative and positive. This assumes the knot has been  *
 *  given an orientation.                                                     */
enum crossing_sign {negative_crossing, positive_crossing};

/*  Crossing type for the Gauss code. Is the current strand over or under.    */
enum crossing_type {under_crossing, over_crossing};

/*  Extended Gauss code. This contains crossing number, sign, and type.       */
struct knot {
    unsigned int number_of_crossings;
    enum crossing_sign *sign;
    enum crossing_type *type;
    unsigned int *crossing_number;
};

/*  This struct is used for keeping track of which crossing number            *
 *  corresponds to which indices.                                             */
struct crossing_indices {
    unsigned int under;
    unsigned int over;
};

/*  Laurent polynomials, i.e. polynomials with negative exponents allowed.    */
struct laurent_polynomial {
    signed int lowest_degree;
    signed int highest_degree;
    signed int *coeffs;
};

extern unsigned int hamming_weight(unsigned int val);
extern struct crossing_indices *get_indices(const struct knot *K);
extern struct laurent_polynomial kauffman_bracket(const struct knot *K);
extern void print_poly(const struct laurent_polynomial *P);
extern struct knot knot_from_gauss_code(const char *str);
extern struct laurent_polynomial jones(const struct knot *K);
extern struct laurent_polynomial normalized_jones(const struct knot *K);

extern void
jones_normalization(const struct knot *K, struct laurent_polynomial *P);

extern struct laurent_polynomial
normalized_kauffman_bracket(const struct knot *K);

extern unsigned int
circle_count(const struct knot *K,
             const struct crossing_indices *ind,
             unsigned int resolution);

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

#endif
