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

/*Function to insert a boundary point on a tangle*/
struct boundary_point* insert_boundary_point(int strand_number, struct boundary_point* strand_pair, struct boundary_point* previous, struct boundary_point* next) {
	/*Allocate space for point and set its strand number, strand pair, previous strand, and next strand
	to the given inputs*/
	struct boundary_point* temp = (struct boundary_point*)safe_malloc(sizeof(struct boundary_point));
	temp->strand_number = strand_number;
	temp->strand_pair = strand_pair;
	temp->previous = previous;
	temp->next = next;

	/*If strand pair/previous/next are not null, pair the other boundary points accordingly*/
	if (strand_pair != NULL)
		strand_pair->strand_pair = temp;
	if (previous != NULL) 
		previous->next = temp;
	if (next != NULL) 
		next->previous = temp;
	return temp;
}
