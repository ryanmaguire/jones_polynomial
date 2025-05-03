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

/*Function which swaps the strand pairs of two boundary points*/
void swap_strand_pairs(struct boundary_point* BP1, struct boundary_point* BP2) {
	/*Store BP1's strand pair in a temporary variable, then pair BP1 with BP2's strand pair,
	and then pair BP2 with temp*/
	struct boundary_point* temp = BP1->strand_pair;
	pair_strands(BP1, BP2->strand_pair);
	pair_strands(BP2, temp);
}
