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
struct specialized_tangle make_tangle(int number_of_boundary_points, struct boundary_point*first_boundary_point, int has_crossing, struct boundary_point** crossing_points) {
	/*After creating the struct variable, set all variables inside the struct equal to the input*/
	struct specialized_tangle temp;
	temp.number_of_boundary_points = number_of_boundary_points;
	temp.first_boundary_point = first_boundary_point;
	temp.has_crossing = has_crossing;
	if (has_crossing == YES)
		temp.crossing_points = crossing_points;
	else
		temp.crossing_points = NULL;
	return temp;
}
