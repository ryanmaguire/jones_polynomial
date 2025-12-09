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

 void shift_polynomial(struct laurent_polynomial* const P, const int shift) {
    if (shift == 0)
        return;
    if (shift > 0) {
        for (int degree = P->highest_degree; degree >= P->lowest_degree; degree--)
            P->coeffs[degree + shift] = P->coeffs[degree];
    } else {
        for (int degree = P->lowest_degree; P->highest_degree; degree++)
            P->coeffs[degree + shift] = P->coeffs[degree];
    }
    P->highest_degree += shift;
    P->lowest_degree += shift;
 }