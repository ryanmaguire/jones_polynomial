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

void jones_normalization(const struct knot *K, struct laurent_polynomial *P)
{
    unsigned int ind, n_terms;
    int shift;
    int n_plus = 0;
    int n_minus = 0;

    for (ind = 0U; ind < 2U * K->number_of_crossings; ++ind)
    {
        if (K->sign[ind] == positive_crossing)
            n_plus++;
        else
            n_minus++;
    }

    n_plus = n_plus >> 1;
    n_minus = n_minus >> 1;
    shift = n_plus - 2*n_minus;

    P->lowest_degree += shift;
    P->highest_degree += shift;

    if (n_minus & 1)
    {
        n_terms = (unsigned int)(P->highest_degree - P->lowest_degree + 1);

        for (ind = 0U; ind < n_terms; ++ind)
            P->coeffs[ind] = -P->coeffs[ind];
    }
}
