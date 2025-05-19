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

/*Function to smooth crossing in a kauffman summand*/
void smooth_crossing(struct kauffman_summand* P, int smoothing) {
	/*For zero-smoothing, increase the highest degree of P by 1, and then pair each of
		the overcrossings with the arc to their right*/
	if (smoothing == 0) {
		P->highest_degree++;
		pair_strands(P->basis_tangle.crossing_points[1], P->basis_tangle.crossing_points[2]);
		pair_strands(P->basis_tangle.crossing_points[3], P->basis_tangle.crossing_points[0]);
	}

	/*For one-smoothing, decrease the highest degree of P by 1, and then pair each of
		the overcrossings with the arc on their left*/
	else if (smoothing == 1) {
		P->highest_degree--;
		pair_strands(P->basis_tangle.crossing_points[1], P->basis_tangle.crossing_points[0]);
		pair_strands(P->basis_tangle.crossing_points[3], P->basis_tangle.crossing_points[2]);
	}

	/*Change the basis the tangle of P to have no crossing*/
	P->basis_tangle.has_crossing = NO;
	P->basis_tangle.crossing_points = NULL;
}
