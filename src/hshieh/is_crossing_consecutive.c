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

/*Function to check if all strands of a crossing at a certain tangle are at consecutive positions*/
int is_crossing_consecutive(struct crossing* C, int* boundary_point_positions, int strands_present, int tangle_width) {
	/*First, set the crossing strand positions to the corresponding positions of boundary points on the tangle*/
	int crossing_strand_positions[4];
	for (int index = 0; index < 4; index++) 
		crossing_strand_positions[index] = boundary_point_positions[C->data[index]];
	/*Check if it's possible to start at one of the strands, and then trace the other present points consecutively*/
	for (int index = 0; index < 4; index++) {
		int current_position = crossing_strand_positions[index];
		int current_index = index;
		while (current_position != -1 && current_index != (index + strands_present) % 4) {
			if (crossing_strand_positions[current_index] != current_position)
				break;
			current_index = (current_index + 1) % 4;
			current_position = (current_position + 1) % tangle_width;
		}
		if (current_index == (index + strands_present)  % 4)
			return YES;
	}
	return NO;
}
