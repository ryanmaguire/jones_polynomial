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

/*Function to make a kauffman summand given the number of coefficients, highest degree, coefficients, sign, and tangle for it*/
struct kauffman_summand make_kauffman_summand(int number_of_coeffs, int highest_degree, int* coeffs, int sign, struct specialized_tangle B) {
	/*Struct variable is created, and all variables in the struct are set equal to the input*/
	struct kauffman_summand temp;
	temp.number_of_coeffs = number_of_coeffs;
	temp.highest_degree = highest_degree;
	temp.coeffs = (int*)safe_malloc((size_t)number_of_coeffs * sizeof(int));
	for (int index = 0; index < number_of_coeffs; index++)
		temp.coeffs[index] = coeffs[index];
	temp.sign = sign;
	temp.basis_tangle = B;
	return temp;
}
