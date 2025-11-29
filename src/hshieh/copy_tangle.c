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

/*Function to copy a tangle*/
struct specialized_tangle* copy_tangle(const struct specialized_tangle* const T) {
	struct specialized_tangle* temp = safe_malloc(sizeof(struct specialized_tangle));
	/*First, set number of boundary points and whether T has a crossing or not accordingly*/
	temp->number_of_boundary_points = T->number_of_boundary_points;
	temp->has_crossing = T->has_crossing;

	/*Loop through all boundary points of T*/
	struct boundary_point* current = NULL;
	struct boundary_point* previous = NULL;
	struct boundary_point* T_point = T->first_boundary_point;
	do {
		/*Allocate memory for current boundary point and set its strand number, and previous point*/
		current = safe_malloc(sizeof(struct boundary_point));
		current->strand_number = T_point->strand_number;
		if (T_point != T->first_boundary_point) {
			current->previous = previous;
			previous->next = current;
		}
		else {
			current->previous = NULL;
			temp->first_boundary_point = current;
		}

		/*To record strand pairs, multiply the strand number by -1 if the pair hasn't been visited and 
		record its address as its current strand pair*/
		if (T_point->strand_pair->strand_number < 0) {
			pair_strands(current, T_point->strand_pair->strand_pair);
			pair_strands(T_point, T_point->strand_pair);
			T_point->strand_pair->strand_number *= -1;
		}

		/*Otherwise, return T_point back to its original state, so the original tangle is unchanged at the end*/
		else {
			T_point->strand_number *= -1;
			T_point->strand_pair = current;
		}

		/*If T has a crossing, then set the crossing points of temp to the correct boundary points*/
		if (temp->has_crossing) 
			for (int index = 0; index < 4; index++) 
				if (T->crossing_points[index] == T_point)
					temp->crossing_points[index] = current;

		/*Move on to the next boundary point*/
		previous = current;
		T_point = T_point->next;
	} while (T_point != T->first_boundary_point);

	/*After getting back to the start, join the first and last boundary points together*/
	current->next = temp->first_boundary_point;
	temp->first_boundary_point->previous = current;

	return temp;
}
