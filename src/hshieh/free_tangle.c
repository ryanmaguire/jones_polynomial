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

/*Function to free all memory associated to a tangle, returns NULL */
extern void free_tangle(struct specialized_tangle* T) {
	/* First, free all boundary points in the tangle */
	struct boundary_point* current = T->first_boundary_point;
	struct boundary_point* next;
	int boundary_points_visited = 0;
	while (boundary_points_visited++ < T->number_of_boundary_points) {
		next = current->next;
		SAFE_FREE(current);
		current = next;
	}

	/* Now, free T itself */
	SAFE_FREE(T);
}