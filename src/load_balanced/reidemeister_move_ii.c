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

void reidemeister_move_ii(struct knot* K) {
	struct crossing* current = K->first_crossing;
	int crossings_visited = 0;
	int n = K->number_of_crossings;

	while (crossings_visited++ < n) {
		enum boolean has_r2 = FALSE;
		int direction = current->direction;
		struct crossing* next = next_crossing(current, direction);
		if (direction == next->direction) {
			if (current->data[(direction + 1) % 4] == next || current->data[(direction + 3) % 4] == next) {
				has_r2 = TRUE;
				delete_crossing(current, direction);
				delete_crossing(next, direction);
				delete_crossing(current, (direction + 1) % 4);
				delete_crossing(current, (direction + 1) % 4);
				if (current == K->first_crossing || next == K->first_crossing) {
					K->first_crossing = next_crossing(next, direction);
				}
			}
		}
		if (has_r2) {
			current = next_crossing(next, direction);
			crossings_visited++;
		}
		else {
			current = next;
		}
	} 
}
