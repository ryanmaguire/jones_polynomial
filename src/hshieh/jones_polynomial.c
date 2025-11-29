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

/*Function which returns the jones polynomial of a knot*/
struct laurent_polynomial* jones_polynomial(const struct knot* const K) {
	/*Start with the Kauffman bracket polynomial of the knot
	To find the jones polynomial, first find the writhe, which is the sum of the signs of every crossing*/
	struct laurent_polynomial* kauffman_bracket_polynomial = kauffman_polynomial(K);
	int n = K->number_of_crossings;
	int writhe = 0;
	for (int crossing = 0; crossing < n; crossing++) 
		if ((K->crossings[crossing].data[3] - K->crossings[crossing].data[1] + 2 * n) % (2 * n) == 1)
			writhe++;
		else
			writhe--;

	/*After finding the writhe, the normalized Kauffman bracket polynomial is (-A^3)^writhe * <L>, where
	<L> is the Kauffman bracket polynomial */
	/*The jones polynomial is found by substutituting A = q^{-1/4} into the normalized Kauffman bracket polynomial*/
	int sign = (writhe % 2 == 0) ? 1 : -1;
	struct laurent_polynomial* jones_polynomial = initialize_polynomial();
	for (int degree = kauffman_bracket_polynomial->lowest_degree; degree <= kauffman_bracket_polynomial->highest_degree; degree+= 4) 
		jones_polynomial->coeffs[-(degree - 3 * writhe)/4 + DEGREE_SHIFT] = sign * kauffman_bracket_polynomial->coeffs[degree + DEGREE_SHIFT];
	jones_polynomial->lowest_degree = -(kauffman_bracket_polynomial->highest_degree - 3 * writhe) / 4;
	jones_polynomial->highest_degree = -(kauffman_bracket_polynomial->lowest_degree - 3 * writhe) / 4;
	return jones_polynomial;
}
