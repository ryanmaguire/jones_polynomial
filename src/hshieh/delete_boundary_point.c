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

/*Function to delete a bounadry point from a tangle*/
void delete_boundary_point(const struct boundary_point* const BP) {
	/*Since the set of boundary points is a doubly linked list, simply put the previous
	point's next strand as the strand after BP, and the next point's previous strand as
	the strand before BP (as long as previous/next is not null)*/
	if (BP->previous != NULL)
		BP->previous->next = BP->next;
	if (BP->next != NULL)
		BP->next->previous = BP->previous;
}
