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
#include <stdlib.h>
#include "kauffman.h"

struct laurent_polynomial
kauffman_bracket_from_data(const signed int *data)
{
    unsigned int n_elements, shift, n;
    struct laurent_polynomial P;

    P.lowest_degree = MIN_DEGREE;
    P.highest_degree = MAX_DEGREE;

    while (data[P.lowest_degree + DEGREE_SHIFT] == 0)
        P.lowest_degree++;

    while (data[P.highest_degree + DEGREE_SHIFT] == 0)
        P.highest_degree--;

    n_elements = (unsigned int)(P.highest_degree - P.lowest_degree + 1);
    shift = (unsigned int)(DEGREE_SHIFT + P.lowest_degree);
    P.coeffs = malloc(sizeof(*P.coeffs) * n_elements);

    for (n = 0U; n < n_elements; ++n)
        P.coeffs[n] = data[n + shift];

    return P;
}
