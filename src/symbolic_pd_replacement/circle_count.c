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
#include <stddef.h>

unsigned int
circle_count(struct affine_term *terms,
             unsigned int len,
             unsigned int ind)
{
    struct chain c[2U * MAX_CROSSINGS];
    unsigned int n;
    unsigned int term_ind = 0U;
    unsigned int choice = ind & 1U;

    c[2U*len - 1U].next = NULL;
    c[0].previous = NULL;
    c[0].next = &c[1];
    c[1].previous = &c[0];

    c[0].current = &(terms[term_ind].dat[choice][0]);
    c[1].current = &(terms[term_ind].dat[choice][1]);

    for (n = 2U; n < 2U * len; n += 2U)
    {
        ind = ind >> 1U;
        term_ind = n >> 1U;
        choice = ind & 1U;

        c[n - 1].next = &c[n];
        c[n].previous = &c[n - 1];
        c[n].next = &c[n + 1];
        c[n + 1U].previous = &c[n];

        c[n].current = &(terms[term_ind].dat[choice][0]);
        c[n + 1].current = &(terms[term_ind].dat[choice][1]);

    }

    simplify_chain(&c[0]);
    return chain_length(&c[0]);
}
