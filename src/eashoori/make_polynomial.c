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

#include "skein_template.h"

//makes polynomial based off its lowest degree, highest degree, and coefficients - Hansen
struct laurent_polynomial make_polynomial(int lowest_degree, int highest_degree, int* coeffs) {
	struct laurent_polynomial temp;
	temp.lowest_degree = lowest_degree;
	temp.highest_degree = highest_degree;
	temp.coeffs = (int*)malloc(MAX_POLY_SIZE * sizeof(int));
	for (int degree = lowest_degree; degree <= highest_degree; degree++)
		temp.coeffs[degree + DEGREE_SHIFT] = coeffs[degree - lowest_degree];
	return temp;
}
x