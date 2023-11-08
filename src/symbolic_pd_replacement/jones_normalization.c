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

/*  All typedef's and function prototypes are provided here.                  */
#include "kauffman.h"

void jones_normalization(const struct knot *K, struct laurent_polynomial *P)
{
    unsigned int n, n_terms;
    int shift;
    int n_plus = 0;
    int n_minus = 0;

    for (n = 0U; n < K->number_of_crossings; ++n)
    {
        if (K->index[n].dat[1] == 0U)
        {
            if (K->index[n].dat[3] == 1U)
                n_minus++;
            else
                n_plus++;
        }

        else if (K->index[n].dat[3] == 0U)
        {
            if (K->index[n].dat[1] == 1U)
                n_plus++;
            else
                n_minus++;
        }

        else
        {
            if (K->index[n].dat[1] > K->index[n].dat[3])
                n_plus++;
            else
                n_minus++;
        }
    }

    shift = n_plus - 2*n_minus;

    P->lowest_degree += shift;
    P->highest_degree += shift;

    if (n_minus % 2)
    {
        n_terms = (unsigned int)(P->highest_degree - P->lowest_degree + 1);

        for (n = 0U; n < n_terms; ++n)
            P->coeffs[n] = -P->coeffs[n];
    }
}
