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
#include "kauffman.h"

struct laurent_polynomial normalized_kauffman_bracket(const struct knot *K)
{
    unsigned int n, weight, n_circles;
    const unsigned int number_of_resolutions = 1U << K->number_of_crossings;
    signed int data[MAX_POLY_SIZE];
    const struct crossing_indices * const ind = get_indices(K);

    for (n = 0U; n < MAX_POLY_SIZE; ++n)
        data[n] = 0U;

    for (n = 0; n < number_of_resolutions; ++n)
    {
        weight = hamming_weight(n);
        n_circles = circle_count(K, ind, n);
        add_normalized_kauffman_summand(n_circles, weight, DEGREE_SHIFT, data);
    }

    return kauffman_bracket_from_data(data);
}
