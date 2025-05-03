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

/*Function to remove twist, if adding a crossing to the current basis tangle of a kauffman summand would result in a twist, also 
returns whether or not adding the crossing will produce a twist*/
int remove_twist(struct kauffman_summand *P, struct boundary_point* BP, struct crossing* C, int num_present, int position, int has_first_boundary_point) {
	if (num_present == 2) {
		/*If two strands are present, then check if these two strands are pairs*/
		if (BP->strand_pair->strand_number == C->data[(position + 1) % 4]) {
			/*If there is a twist, then multiply P by -A^3 or -A^-3, depending on the direction of the twist*/
			P->sign *= -1;
			if (position % 2 == 1)
				P->highest_degree += 3;
			else
				P->highest_degree -= 3;
			BP->strand_number = C->data[(position + 3) % 4];
			BP->strand_pair->strand_number = C->data[(position + 2) % 4];
			return YES;
		}
		else {
			return NO;
		}
	}
	else if (num_present == 3) {
		/*If three strands are present, check if the first two strands are paired together*/
		if (BP->strand_pair->strand_number == C->data[(position + 1) % 4]) {
			/*Adjust P accordingly (either multiply by -A^3 or -A^-3), and also delete the two boundary points in the twist*/
			BP = BP->next->next;
			P->sign *= -1;
			if (position % 2 == 1)
				P->highest_degree += 3;
			else
				P->highest_degree -= 3;
			delete_boundary_point(BP->previous->previous);
			delete_boundary_point(BP->previous);
			BP->strand_number = C->data[(position + 3) % 4];
			if (has_first_boundary_point == YES)
				P->basis_tangle.first_boundary_point = BP;
			return YES;
		}
		/*Also check if the last two strands are paired together*/
		else if (BP->next->strand_pair->strand_number == C->data[(position + 2) % 4]) {
			/*Again, delete the two strands in the twist, and adjust P accordingly*/
			P->sign *= -1;
			if (position % 2 == 0)
				P->highest_degree += 3;
			else
				P->highest_degree -= 3;
			delete_boundary_point(BP->next->next);
			delete_boundary_point(BP->next);
			BP->strand_number = C->data[(position + 3) % 4];
			if (has_first_boundary_point == YES)
				P->basis_tangle.first_boundary_point = BP;
			return YES;
		}
		else {
			return NO;
		}
	}
	else if (num_present == 4) {
		/*If four strands are present, first check if the first two strands are paired together*/
		if (BP->strand_pair->strand_number == C->data[(position + 1) % 4]) {
			/*Adjust P for the first twist*/
			P->sign *= -1;
			if (position % 2 == 1)
				P->highest_degree += 3;
			else
				P->highest_degree -= 3;
			if (BP->next->next->strand_pair->strand_number == C->data[(position + 3) % 4]) {
				/*If the last two strands are also paired together, then the tangle now has a circle, 
				which needs to be removed as long as P has at least one more boundary point*/
				if (P->basis_tangle.number_of_boundary_points > 4)
					remove_circle(P);
			}
			else {
				pair_strands(BP->next->next->strand_pair, BP->next->next->next->strand_pair);
			}
			for (int index = 0; index < 4; index++) {
				delete_boundary_point(BP);
				BP = BP->next;
			}
			if (has_first_boundary_point == YES) {
				if (P->basis_tangle.number_of_boundary_points > 4) 
					P->basis_tangle.first_boundary_point = BP;
				else 
					P->basis_tangle.first_boundary_point = NULL;
			}
			return YES;
		}
		/*Otherwise, check if the middle two strands are paired together*/
		else if (BP->next->strand_pair->strand_number == C->data[(position + 2) % 4]) {
			/*Remove the twist from the middle two strands first*/
			P->sign *= -1;
			if (position % 2 == 0)
				P->highest_degree += 3;
			else
				P->highest_degree -= 3;
			if (BP->strand_pair->strand_number == C->data[(position + 3) % 4]) {
				/*The first and last strands could also be paired together, and if they are, removed
				the circle that is formed as long as there are still more boundary points left*/
				if (P->basis_tangle.number_of_boundary_points > 4)
					remove_circle(P);
			}
			else {
				pair_strands(BP->strand_pair, BP->next->next->next->strand_pair);
			}
			for (int index = 0; index < 4; index++) {
				delete_boundary_point(BP);
				BP = BP->next;
			}
			if (has_first_boundary_point == YES) {
				if (P->basis_tangle.number_of_boundary_points > 4) 
					P->basis_tangle.first_boundary_point = BP;
				else 
					P->basis_tangle.first_boundary_point = NULL;
			}
			return YES;
		}
		/*It could also be the case that only the last two strands are paired together*/
		else if (BP->next->next->strand_pair->strand_number == C->data[(position + 3) % 4]) {
			/*Removed the twist from the last two strands*/
			P->sign *= -1;
			if (position % 2 == 1)
				P->highest_degree += 3;
			else
				P->highest_degree -= 3;
			pair_strands(BP->strand_pair, BP->next->strand_pair);
			for (int index = 0; index < 4; index++) {
				delete_boundary_point(BP);
				BP = BP->next;
			}
			if (has_first_boundary_point == YES) {
				if (P->basis_tangle.number_of_boundary_points > 4) 
					P->basis_tangle.first_boundary_point = BP;
				else 
					P->basis_tangle.first_boundary_point = NULL;
			}
			return YES;
		}
		else {
			return NO;
		}
	}
	/*If only one strand is present, it is impossible for there to be a twist*/
	else {
		return NO;
	}
}
