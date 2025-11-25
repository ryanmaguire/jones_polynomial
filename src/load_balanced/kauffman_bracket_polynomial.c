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
struct laurent_polynomial* kauffman_bracket_polynomial(struct link* L)
{
    /* Loop through all reidemeister moves and generalized reidemeister moves until no more can be performed */
    while (reidemeister_move_i(L) || reidemeister_move_ii(L) || null_gamma(L) || null_triple(L)) {}

    /* Count number of unknot diagrams in link */
    int number_of_unknots = 0;
    for (int i = 0; i < L->number_of_components; i++) {
        if (L->number_of_crossings_in_components[i] == 0) number_of_unknots++;
    }

    /* Deal with the case where the link is now a union of unknot diagrams */
    if (number_of_unknots == L->number_of_components) {
        /* If we remove unknots until we have one remaining, we get number_of_unknots - 1 as our exponent for A^2+A^-2 */
        int exponent = number_of_unknots - 1;
        struct laurent_polynomial* result = (struct laurent_polynomial*) safe_malloc(sizeof(struct laurent_polynomial));
        result->coeffs = a_squared_a_inv_squared_powers[exponent];
        result->lowest_degree = -2 * exponent;
        result->highest_degree = 2 * exponent;
        
        /* Free memory of L */
        /* All components of L must now be unknots, so there are no crossings to free */
        SAFE_FREE(L->first_crossing_in_components);
        SAFE_FREE(L->number_of_crossings_in_components);
        SAFE_FREE(L);

        return result;
    }

    /* Otherwise, check for individual unknot diagrams and remove them */
    struct laurent_polynomial* multiplier = (struct laurent_polynomial*) safe_malloc(sizeof(struct laurent_polynomial));
    multiplier->coeffs = a_squared_a_inv_squared_powers[number_of_unknots];
    multiplier->lowest_degree = -2 * number_of_unknots;
    multiplier->highest_degree = 2 * number_of_unknots;

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
    L->number_of_components -= number_of_unknots;

    int pattern_component; // Component in which pattern is located

    /* Check for triples, which have complexity type (4,1+R3) for types 1,2 or (3,1+bigon) for types 3,4 */ 
    if ((pattern_component = triple_search(L)) != -1) {}
    /* Check for R3 configurations, which have complexity type (3,1) */
    else if ((pattern_component = reidemeister_move_iii_search(L)) != -1) {}
    /* Check for untwistable gammas, which have complexity type (2,1+bigon) */
    else if ((pattern_component = gamma_search(L)) != -1) {}
    /* Check for bigons, which have complexity type (2,1) */
    else if ((pattern_component = bigon_search(L)) != -1) {}
    /* Otherwise pick a component and crossing at random */
    else pattern_component = 0;

    /* Make a deep copy of link L */
    struct link *L_copy = copy_link(L);

    /* Smooth respective crossings in both link copies */
    smooth_crossing(L, L->first_crossing_in_components[pattern_component], 0);
    smooth_crossing(L_copy, L->first_crossing_in_components[pattern_component], 1);

    /* Recursion step */
    struct laurent_polynomial* polynomial_1 = kauffman_bracket_polynomial(L);
    struct laurent_polynomial* polynomial_2 = kauffman_bracket_polynomial(L_copy);

    /* We will now evaluate the final polynomial according to KBP Skein relation */

    /* First, compute the two individual terms - notice that multiplying or dividing by 
     * A is just shifting the coeffs up or down by 1 index */
    polynomial_1->highest_degree++;
    polynomial_1->lowest_degree++;
    polynomial_2->highest_degree--;
    polynomial_2->lowest_degree--;

    /* Now, add them */
    struct laurent_polynomial* sum_of_two_polynomials = add_polynomials(polynomial_1, polynomial_2);
    
    /* Finally, scale by multiplier */
    struct laurent_polynomial* result = multiply_polynomials(sum_of_two_polynomials, multiplier);

    /* We never actually need to free L or L_copy because they will get passed down
     * the recursion and eventually freed by the base case */
    /* However, we do need to free polynomials 1 and 2, their sum, and multiplier */
    delete_polynomial(polynomial_1);
    delete_polynomial(polynomial_2);
    delete_polynomial(sum_of_two_polynomials);
    delete_polynomial(multiplier);

    /* We are done. */
    return result;
}
