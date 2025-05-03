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

#include "kauffman_implementation.h"

/*Function to adjust degree of laurent polynomial correctly*/
void adjust_polynomial_degree(struct laurent_polynomial* P) {
	for (int index = 0; index < MAX_POLY_SIZE; index++)
		/*The lowest degree of P is set to the lowest power at which the coefficient is nonzero*/
		if (P->coeffs[index] != 0) {
			P->lowest_degree = index - DEGREE_SHIFT;
			break;
		}
	for (int index = MAX_POLY_SIZE - 1; index >= 0; index--)
		/*The highest degree of P is set to the highest power of P with a nonzero coefficient*/
		if (P->coeffs[index] != 0) {
			P->highest_degree = index - DEGREE_SHIFT;
			break;
		}
}
