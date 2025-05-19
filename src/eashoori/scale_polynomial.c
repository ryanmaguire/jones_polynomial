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

//scales all terms of a laurent polynomial by a certain degree - Hansen
void scale_polynomial(struct laurent_polynomial* P, int degree_change) {
	if (degree_change == 0)
		return;
	int start_degree;
	int end_degree;
	int increment;
	if (degree_change > 0) {
		start_degree = P->highest_degree;
		end_degree = P->lowest_degree;
		increment = -1;
	}
	else {
		start_degree = P->lowest_degree;
		end_degree = P->highest_degree;
		increment = 1;
	}
	for (int degree = start_degree; degree != end_degree; degree += increment)
		P->coeffs[degree + degree_change + DEGREE_SHIFT] = P->coeffs[degree + DEGREE_SHIFT];
	P->coeffs[end_degree + degree_change + DEGREE_SHIFT] = P->coeffs[end_degree + DEGREE_SHIFT];
	P->highest_degree += degree_change;
	P->lowest_degree += degree_change;
}
