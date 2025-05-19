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

/*Function to copy an entire kauffman summand*/
struct kauffman_summand* copy_kauffman_summand(struct kauffman_summand* P) {
	/*After allocating space for the summand, the number of coefficients, degree, coefficients, and sign are copied,
	and then the basis tangle is copied using the function to copy tangles*/
	struct kauffman_summand* temp = (struct kauffman_summand*)safe_malloc(sizeof(struct kauffman_summand));
	temp->number_of_coeffs = P->number_of_coeffs;
	temp->highest_degree = P->highest_degree;
	temp->coeffs = (int*)safe_malloc((size_t)temp->number_of_coeffs * sizeof(int));
	for (int index = 0; index < temp->number_of_coeffs; index++)
		temp->coeffs[index] = P->coeffs[index];
	temp->sign = P->sign;
	temp->basis_tangle = copy_tangle(P->basis_tangle);
	return temp;
}
