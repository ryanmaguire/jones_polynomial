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
#include <stdlib.h>

struct affine_term *get_affine_terms(const struct knot *K)
{
    struct affine_term * terms;
    unsigned int n;

    if (!K)
        return NULL;

    terms = malloc(sizeof(*terms) * K->number_of_crossings);

    for (n = 0U; n < K->number_of_crossings; ++n)
        set_affine_term_from_crossing(&terms[n], &K->index[n]);

    return terms;
}
