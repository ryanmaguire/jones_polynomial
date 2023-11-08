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

void
set_affine_term_from_crossing(struct affine_term *a, const struct crossing *c)
{
    if (!a || !c)
        return;

    a->dat[0][0].dat[0] = c->dat[0];
    a->dat[0][0].dat[1] = c->dat[1];
    a->dat[0][1].dat[0] = c->dat[2];
    a->dat[0][1].dat[1] = c->dat[3];

    a->dat[1][0].dat[0] = c->dat[0];
    a->dat[1][0].dat[1] = c->dat[3];
    a->dat[1][1].dat[0] = c->dat[1];
    a->dat[1][1].dat[1] = c->dat[2];
}
