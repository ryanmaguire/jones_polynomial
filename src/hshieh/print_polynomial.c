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
#include <stdio.h>

/*Function to print a laurent polynomial in a given variable*/
void print_polynomial(struct laurent_polynomial* P, char c) {
	/*Starting from the highest degree, print all the terms, with + and - signs as needed*/
	for (int degree = P->highest_degree; degree >= P->lowest_degree; degree--) {
		int coeff = P->coeffs[degree + DEGREE_SHIFT];
		if (coeff == 0) {
			if (degree == P->highest_degree)
				printf("0");
			continue;
		}
		if (coeff > 0) {
			if (degree != P->highest_degree)
			printf(" + ");
			if (coeff > 1)
				printf("%d", coeff);
		}
		else {
			printf(" - ");
			if (coeff < -1)
				printf("%d", -coeff);
		}
		if (degree == 0) {
			if (coeff == 1 || coeff == -1)
				printf("1");
		}
		else {
			putchar(c);
			if (degree != 1)
				printf("^%d", degree);
		}
	}
	printf("\n");
}
