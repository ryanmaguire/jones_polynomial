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

//returns the difference of two laurent polynomials - Hansen
struct laurent_polynomial subtract_polynomials(struct laurent_polynomial P, struct laurent_polynomial Q) {
	struct laurent_polynomial difference;
	difference.lowest_degree = MIN(P.lowest_degree, Q.lowest_degree);
	difference.highest_degree = MAX(P.highest_degree, Q.highest_degree);
	difference.coeffs = (int*)malloc(MAX_POLY_SIZE * sizeof(int));
	for (int degree = difference.lowest_degree; degree <= difference.highest_degree; degree++) {
		difference.coeffs[degree + DEGREE_SHIFT] = 0;
		if (degree >= P.lowest_degree && degree <= P.highest_degree)
			difference.coeffs[degree + DEGREE_SHIFT] += P.coeffs[degree + DEGREE_SHIFT];
		if (degree >= Q.lowest_degree && degree <= Q.highest_degree)
			difference.coeffs[degree + DEGREE_SHIFT] -= Q.coeffs[degree + DEGREE_SHIFT];
	}
	return difference;
}
