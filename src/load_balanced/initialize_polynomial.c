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

/*Function which returns a laurent polynomial initialized to the zero polynomial*/
struct laurent_polynomial* initialize_polynomial(void) 
{
	/*Create struct for polynomial, set its lowest and highest degrees to zero, and then set
	all of its coefficients to zero*/
	struct laurent_polynomial* temp = (struct laurent_polynomial*) safe_malloc(sizeof(struct laurent_polynomial));
	temp->lowest_degree = temp->highest_degree = 0;
	temp->coeffs = (int*) safe_calloc(MAX_POLY_SIZE, sizeof(int));
	return temp;
}
