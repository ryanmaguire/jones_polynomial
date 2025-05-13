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

/*Function to add crossing to a basis tangle from a kauffman summand*/
void add_crossing(struct kauffman_summand* P, struct crossing* C, int strands_present) {
	struct boundary_point* BP = P->basis_tangle.first_boundary_point;
	/*First, find the pos (index) of the leftmost boundary point which has a strand in the crossing*/
	int pos;
	while ((pos = crossing_position(BP->strand_number, C)) == -1) 
		BP = BP->next;
	/*If BP is the first boundary point, then the leftmost boundary point could still be to its left*/
	int has_first_boundary_point = (P->basis_tangle.first_boundary_point == BP) ? YES : NO;
	if (has_first_boundary_point == YES) 
		while (crossing_position(BP->previous->strand_number, C) != -1 && BP->previous != P->basis_tangle.first_boundary_point) {
			pos = crossing_position(BP->previous->strand_number, C);
			BP = BP->previous;
		}
	/*If adding the crossing to the current kauffman summand would produe a twist, then we do not add
	it normally and instead use the remove twist function */
	if (remove_twist(P, BP, C, strands_present, pos, has_first_boundary_point) == NO) {
		struct boundary_point** crossing_points = (struct boundary_point**)safe_malloc(4 * sizeof(struct boundary_point*));
		if (strands_present == 1) {
			/*If one of the strands in the tangle is at the crossing, then the label on that strand is changed, and 
			two more boundary points are inserted into the tangle (before and after it)*/
			BP->strand_number = C->data[(pos + 2) % 4];
			crossing_points[pos] = BP->strand_pair;
			crossing_points[(pos + 2) % 4] = BP;
			crossing_points[(pos + 3) % 4] = insert_boundary_point(C->data[(pos + 3) % 4], NULL, BP->previous, BP);
			crossing_points[(pos + 1) % 4] = insert_boundary_point(C->data[(pos + 1) % 4], BP->previous, BP, BP->next);
			if (has_first_boundary_point == YES)
				P->basis_tangle.first_boundary_point = BP->previous;
		}
		else if (strands_present == 2) {
			/*If two strands are present at the crossing, then their labels need to be changed accordingly, and
			their strand pairs have to be swapped*/
			BP->strand_number = C->data[(pos + 3) % 4];
			BP->next->strand_number = C->data[(pos + 2) % 4];
			crossing_points[pos] = BP->strand_pair;
			crossing_points[(pos + 1) % 4] = BP->next->strand_pair;
			crossing_points[(pos + 2) % 4] = BP->next;
			crossing_points[(pos + 3) % 4] = BP;
			swap_strand_pairs(BP, BP->next);
		}
		else if (strands_present == 3) {
			/*If three strands are present at the crossing, then the first and last boundary point need to be
			deleted (and their pairs joined together), and the middle point has to be relabeled*/
			pair_strands(BP->strand_pair, BP->next->next->strand_pair);
			for (int index = 0; index < 3; index++) {
				if (index == 1) {
					BP->strand_number = C->data[(pos + 3) % 4];
					crossing_points[(pos + 3) % 4] = BP;
					if (has_first_boundary_point == YES)
						P->basis_tangle.first_boundary_point = BP;
				}
				else {
					delete_boundary_point(BP);
				}
				crossing_points[(pos + index) % 4] = BP->strand_pair;
				BP = BP->next;
			}
		}
		else if (strands_present == 4) {
			/*If four strands are present at the crossing, then all four boundary points need to be deleted, and
			their strand pairs have to be paired together accordingly */
			for (int index = 0; index < 4; index++) {
				if (index < 2)
					pair_strands(BP->strand_pair, BP->next->next->strand_pair);
				crossing_points[(pos + index) % 4] = BP->strand_pair;
				delete_boundary_point(BP);
				BP = BP->next;
			}
			if (has_first_boundary_point == YES) {
				if (P->basis_tangle.number_of_boundary_points > 4) 
					P->basis_tangle.first_boundary_point = BP;
				else 
					P->basis_tangle.first_boundary_point = NULL;
			}
		}
		/*Crossing is stored in the basis tangle*/
		P->basis_tangle.has_crossing = YES;
		P->basis_tangle.crossing_points = crossing_points;
	}
	/*New width of the tangle changes by (-2 * strands present + 4) */
	P->basis_tangle.number_of_boundary_points += -2 * strands_present + 4;
}
