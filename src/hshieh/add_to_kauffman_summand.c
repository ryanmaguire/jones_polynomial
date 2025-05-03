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

/*Function to add the polynomial coefficient from a kauffman summand Q to another kauffman summand P*/
void add_to_kauffman_summand(struct kauffman_summand* P, struct kauffman_summand* Q) {
	/*The variable sign_change keeps track of whether P and Q have the same sign or not */
	int sign_change = P->sign * Q->sign;
	if (P->highest_degree == Q->highest_degree) {
		/*If P and Q have the same highest degree, add the coefficients of Q to P*/
		for (int index = 0; index < P->number_of_coeffs; index++) 
			P->coeffs[index] += sign_change * Q->coeffs[index];
	}
	else if (P->highest_degree > Q->highest_degree) {
		/*If P has a highest degree than Q, find the difference, and then add the shifted coefficients from Q*/
		int difference = (P->highest_degree - Q->highest_degree) / 4;
		for (int index = 0; index < P->number_of_coeffs - difference; index++) 
			P->coeffs[index + difference] += sign_change * Q->coeffs[index];
	}
	else if (P->highest_degree < Q->highest_degree) {
		/*If Q has a higher degree than P, then shift the coefficients of P, and add the coefficients from Q*/
		int difference = (Q->highest_degree - P->highest_degree) / 4;
		for (int index = P->number_of_coeffs - 1; index >= 0; index--) {
			P->coeffs[index] = sign_change * Q->coeffs[index];
			if (index >= difference) 
				P->coeffs[index] += P->coeffs[index - difference];
		}
		/*The highest degree of P must be changed in this case*/
		P->highest_degree = Q->highest_degree;
	}
}
