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

 /* Functions to multiply Laurent polynomials */
struct laurent_polynomial* multiply_polynomials(const struct laurent_polynomial* P, const struct laurent_polynomial* Q) 
{
	struct laurent_polynomial* product = (struct laurent_polynomial*) safe_malloc(sizeof(struct laurent_polynomial));
	product->lowest_degree = P->lowest_degree + Q->lowest_degree;
	product->highest_degree = P->highest_degree + Q->highest_degree;
	product->coeffs = (int*) safe_malloc(MAX_POLY_SIZE * sizeof(int));
	for (int degree = product->lowest_degree; degree <= product->highest_degree; degree++)
		product->coeffs[degree + DEGREE_SHIFT] = 0;
	for (int P_degree = P->lowest_degree; P_degree <= P->highest_degree; P_degree++)
		for (int Q_degree = Q->lowest_degree; Q_degree <= Q->highest_degree; Q_degree++)
			product->coeffs[P_degree + Q_degree + DEGREE_SHIFT] += P->coeffs[P_degree + DEGREE_SHIFT] * Q->coeffs[Q_degree + DEGREE_SHIFT];
	return product;
}