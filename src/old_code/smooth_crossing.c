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

void smooth_crossing(struct knot* K, struct crossing* C, int smoothing_type) {
	int strand_zero_pair, strand_two_pair;
	if (smoothing_type == 0) {
		strand_zero_pair = 1;
		strand_two_pair = 3;
	}
	else {
		strand_zero_pair = 3;
		strand_two_pair = 1;
	}

	/*Kill crossing C*/
	C->data[0]->data[C->ports[0]] = C->data[strand_zero_pair];
	C->data[0]->ports[C->ports[0]] = C->ports[strand_zero_pair];
	C->data[strand_zero_pair]->data[C->ports[strand_zero_pair]] = C->data[0];
	C->data[strand_zero_pair]->ports[C->ports[strand_zero_pair]] = C->ports[0];
	C->data[2]->data[C->ports[2]] = C->data[strand_two_pair];
	C->data[2]->ports[C->ports[2]] = C->ports[strand_two_pair];
	C->data[strand_two_pair]->data[C->ports[strand_two_pair]] = C->data[2];
	C->data[strand_two_pair]->ports[C->ports[strand_two_pair]] = C->ports[2];

	// Now, c is separated from the knot/link. Nothing points to it.
	// Now, we need to fix the orientations of the crossings.
	enum boolean check = TRUE;
	struct crossing* curr = C;
	int counter = 0;
	while (counter == 0) {
		if (curr->direction == 0)
			reverse(curr);
		if (curr->id == C->data[strand_zero_pair]->id && (curr->direction == C->data[strand_zero_pair]->direction || (curr->direction + 2) % 4 == C->data[strand_zero_pair]->direction))
			check = FALSE;
		curr = next_crossing(curr, curr->direction);
		if (curr->id == C->data[strand_two_pair]->id && curr->direction == C->data[strand_two_pair]->direction)
			counter++;
	}
	counter = 0;
	if (check) {
		curr = C->data[strand_zero_pair];
		while (counter == 0) {
			if (curr->direction == 0) {
				reverse(curr);
			}
			curr = next_crossing(curr, curr->direction);
			if (curr->id == C->data[0]->id && curr->direction == C->data[0]->direction) {
				counter++;
			}
		}
	}

	--K->number_of_crossings;
	if (K->first_crossing == C)
		K->first_crossing = next_crossing(C, C->direction);
}
