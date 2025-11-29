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

/*Function to make tangle from the number of boundary points, struct for the first boundary point, and crossing if one is present*/
struct specialized_tangle* make_tangle(const int number_of_boundary_points, struct boundary_point* const first_boundary_point, const enum boolean has_crossing, struct boundary_point** const crossing_points) {
	/*After creating the struct variable, set all variables inside the struct equal to the input*/
	struct specialized_tangle* temp = safe_malloc(sizeof(struct specialized_tangle));
	temp->number_of_boundary_points = number_of_boundary_points;
	temp->first_boundary_point = first_boundary_point;
	temp->has_crossing = has_crossing;

	/*If the tangle has a crossing, set its crossing points to the given, and otherwise set it equal to null*/
	if (has_crossing) 
		for (int i = 0; i < 4; i++)
			temp->crossing_points[i] = crossing_points[i];

	return temp;
}
