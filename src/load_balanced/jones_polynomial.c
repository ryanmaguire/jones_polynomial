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

 /* Function to return the Jones polynomial of a link */
 struct laurent_polynomial* jones_polynomial(struct link* L) 
 {
    int w = writhe(L);
    struct laurent_polynomial* kauffman_bracket = kauffman_bracket_polynomial(L);
    adjust_polynomial_degree(kauffman_bracket);
    struct laurent_polynomial* jones_polynomial = initialize_polynomial();
    int sign = (w % 2 == 0) ? 1 : -1;
	for (int degree = kauffman_bracket->lowest_degree; degree <= kauffman_bracket->highest_degree; degree+= 4) 
		jones_polynomial->coeffs[-(degree - 3 * w)/4 + DEGREE_SHIFT] = sign * kauffman_bracket->coeffs[degree + DEGREE_SHIFT];
	jones_polynomial->lowest_degree = -(kauffman_bracket->highest_degree - 3 * w) / 4;
	jones_polynomial->highest_degree = -(kauffman_bracket->lowest_degree - 3 * w) / 4;

    delete_polynomial(&kauffman_bracket);    
    return jones_polynomial;
 }