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

/*Function to make a knot given the number of crossings, and array of its crossings*/
struct knot make_knot(int number_of_crossings, struct crossing* crossings) {
	/*After creating the struct variable, the number of crossings and crossings are copied over*/
	struct knot temp;
	temp.number_of_crossings = number_of_crossings;
	temp.crossings = (struct crossing*)safe_malloc((size_t)number_of_crossings * sizeof(struct crossing));
	for (int crossing = 0; crossing < temp.number_of_crossings; crossing++) 
		temp.crossings[crossing] = crossings[crossing];
	return temp;
}
