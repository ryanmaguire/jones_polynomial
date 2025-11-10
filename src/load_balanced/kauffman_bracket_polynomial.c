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
 #include "load_balanced.h"

/* Main recursion function for computing the Kauffman Bracket Polynomial of a link */
/* Complexity types (to a depth of 2) are compared at https://www.desmos.com/calculator/2cyj8icufr */
/* In particular, the current pattern ordering is valid for all alpha >= 1.619 > phi */
struct laurent_polynomial kauffman_bracket_polynomial(struct link* L)
{
    /* Loop through all reidemeister moves and generalized reidemeister moves until no more can be performed */
    while (reidemeister_move_i(L) || reidemeister_move_ii(L) || null_gamma(L) || null_triple(L)) {}
    struct laurent_polynomial A;

    /* Count number of unknot diagrams in link */
    int number_of_unknots = 0;
    for (int i = 0; i < L->number_of_components; i++) {
        if (L->number_of_crossings_in_components[i] == 0) number_of_unknots++;
    }

    /* Deal with the case where the link is now a union of unknot diagrams */
    if (number_of_unknots == L->number_of_components) {
        // ==========================================================================================================================
        // TODO: take a^2+a^-2 and raise it to the power of number_of_unknots, we should definitely precompute all the powers of this
        // ==========================================================================================================================
        
        /* Free memory of L */
        /* All components of L must now be unknots, so there are no crossings to free */
        SAFE_FREE(L->first_crossing_in_components);
        SAFE_FREE(L->number_of_crossings_in_components);
        SAFE_FREE(L);

        // ===================
        // TODO: return result
        // ===================
    }

    /* Otherwise, check for individual unknot diagrams */
    struct laurent_polynomial multiplier;
    // ==========================================================================================================================
    // TODO: take a^2+a^-2 and raise it to the power of number_of_unknots, we should definitely precompute all the powers of this
    // ==========================================================================================================================
    /* Linear time run through the components */
    int scanning_index = 0; // Current (old) index that we are looking att
    int moved_index = 0; // New index that we will put non-unknot components into
    for (; scanning_index < L->number_of_components; scanning_index++) {
        if (L->number_of_crossings_in_components[scanning_index] != 0) {
            L->number_of_crossings_in_components[moved_index] = L->number_of_crossings_in_components[scanning_index];
            L->first_crossing_in_components[moved_index] = L->first_crossing_in_components[scanning_index];
            moved_index++;
        }
    }
    L->number_of_crossings_in_components -= number_of_unknots;

    // =================================================
    // TODO: remember to scale ALL outputs by multiplier
    // =================================================

    /* Check for triples, which have complexity type (4,1+R3) for types 1,2 or (3,1+bigon) for types 3,4 */ 
    int triple_component = triple_search(L); // Component where the triple is located
    if (triple_search(L) != -1) {
        /* Make a deep copy of link L */
        struct link *L_copy = copy_link(L);

        /* Smooth respective crossings in both link copies */
        smooth_crossing(L, L->first_crossing_in_components[triple_component], 0);
        smooth_crossing(L_copy, L->first_crossing_in_components[triple_component], 1);

        /* Recursion step */
        struct laurent_polynomial polynomial_1 = kauffman_bracket_polynomial(L);
        struct laurent_polynomial polynomial_2 = kauffman_bracket_polynomial(L_copy);

        /* Evaluate polynomial according to KBP Skein relation */
        return add_polynomials(multiply_polynomials(kauffman_bracket_polynomial(L),A)), multiply_polynomials(kauffman_bracket_polynomial(L_copy),A_inverse);
    }
    if (bigon_search(L) != -1) {
        /* Make a deep copy of link L */
        struct link *L_copy = copy_link(L);

        /* Smooth respective crossings in both link copies */
        smooth_crossing(L, L->first_crossing_in_components[triple_component], 0);
        smooth_crossing(L_copy, L->first_crossing_in_components[triple_component], 1);

        /* Recursion step */
        struct laurent_polynomial_1 = kauffman_bracket_polynomial(L);

        /* Evaluate polynomial according to KBP Skein relation */
        return add_polynomials(multiply_polynomials (kauffman_bracket_polynomial(L),A)), multiply_polynomials(kauffman_bracket_polynomial(L_copy),A_inverse);
    }
    if (r3_search(L) != -1) {
        /* Make a deep copy of link L */
        struct link *L_copy = copy_link(L);

        /* Smooth respective crossings in both link copies */
        smooth_crossing(L, L->first_crossing_in_components[triple_component], 0);
        smooth_crossing(L_copy, L->first_crossing_in_components[triple_component], 1);

        /* Recursion step */
        struct laurent_polynomial_1 = kauffman_bracket_polynomial(L);

        /* Evaluate polynomial according to KBP Skein relation */
        return add_polynomials(multiply_polynomials (kauffman_bracket_polynomial(L),A)), multiply_polynomials(kauffman_bracket_polynomial(L_copy),A_inverse);
    }

    /* Check for R3 configurations, which have complexity type (3,1) */

    /* Check for untwistable gammas, which have complexity type (2,1+bigon) */

    /* Check for bigons, which have complexity type (2,1) */
}
