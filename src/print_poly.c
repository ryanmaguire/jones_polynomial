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
#include <stdio.h>
#include "kauffman.h"

void print_poly(const struct laurent_polynomial *P)
{
    signed int n, N;

    if (!P)
    {
        puts("0");
        return;
    }

    if (!P->coeffs)
    {
        puts("0");
        return;
    }

    N = P->highest_degree - P->lowest_degree + 1;

    if (P->coeffs[0] == 1)
        printf("q^%d", P->lowest_degree);
    else if (P->coeffs[0] == -1)
        printf("-q^%d", P->lowest_degree);
    else
        printf("%dq^%d", P->coeffs[0], P->lowest_degree);

    for (n = 1; n < N; ++n)
    {
        if (P->coeffs[n] == 0)
            continue;
        else if (P->coeffs[n] == 1)
            printf(" + q^%d", P->lowest_degree + n);
        else if (P->coeffs[n] == -1)
            printf(" - q^%d", P->lowest_degree + n);
        else if (P->coeffs[n] > 1)
            printf(" + %dq^%d", P->coeffs[n], P->lowest_degree + n);
        else
            printf(" - %dq^%d", -P->coeffs[n], P->lowest_degree + n);
    }

    printf("\n");
}
