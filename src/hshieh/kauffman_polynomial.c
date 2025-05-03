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

 /*Function to find the Kauffman bracket polynomial of a knot*/
/*This function uses the algorithm from "Efficient Computation of the Kauffman Bracket" by Ellenberg et al., where we first take a 
cutting of the knot, which consists of a sequence of n + 1 tangles, where the first tangle is empty, and each tangle in the sequence
adds one crossing to the previous tangle. Every time we add a crossing, we simply every tangle according to the definition of the Kauffman
bracket polynomial (where we smooth the crossing), so that we are left with base tangles, each of which has a polynomial coefficient. For a
tangle with g boundary points, the number of possible base tangles is C_{g/2}, the (g/2)th Catalan number. It takes O(n) time to add a crossing
to a tangle and then smooth it, and the cutwidth of the graph at any time can be proven to be no more than C*sqrt(n), where C = 6 * sqrt(2) + 
5 * sqrt(3). The mth Catalan number asymptotically is O(4^m), so this algorithm runs in O(n2^{C * sqrt(n)}). */
struct laurent_polynomial kauffman_polynomial(struct knot* K) {
	extern const int catalan[];
	int n = K->number_of_crossings;
	/*The array crossings_at_strand keeps track of the two crossings at every arc*/
	int** crossings_at_strand = (int**)safe_malloc((2 * (size_t)n + 1) * sizeof(int*));
	for (int strand = 1; strand <= 2 * n; strand++) {
		crossings_at_strand[strand] = (int*)safe_malloc(2 * sizeof(int));
		crossings_at_strand[strand][0] = crossings_at_strand[strand][1] = -1;
	}
	for (int crossing = 0; crossing < n; crossing++) {
		for (int index = 0; index < 4; index++) {
			int strand = K->crossings[crossing].data[index];
			if (crossings_at_strand[strand][0] == -1) 
				crossings_at_strand[strand][0] = crossing;
			else 
				crossings_at_strand[strand][1] = crossing;
		}
	}
	/*The array crossings_times_touched keeps track of how many visited arcs touched each crossing at every point
	during the algorithm, and has_visited_crossing keeps track of the crossings which have been added to a tangle*/
	int* crossings_times_touched = (int*)safe_calloc((size_t)n, sizeof(int));
	int* has_visited_crossing = (int*)safe_malloc((size_t)n * sizeof(int));
	for (int index = 0; index < n; index++)
		has_visited_crossing[index] = NO;
	/*The first crossing can be chosen arbitrarily, so we can always pick the crossing at index 0*/
	int current_crossing = 0;
	crossings_times_touched[current_crossing] = 4;
	for (int index = 0; index < 4; index++) {
		int strand = K->crossings[current_crossing].data[index];
		for (int crossing = 0; crossing < 2; crossing++) 
			if (crossings_at_strand[strand][crossing] != current_crossing) 
				crossings_times_touched[crossings_at_strand[strand][crossing]]++;
	}
	int current_width = 4;
	int old_width = -1;
	int* coeffs = (int*)safe_calloc((size_t)n + 1, sizeof(int));
	coeffs[0] = 1;
	/*To add the first crossing, we add the 4 arcs at that crossing to create a tangle with 4 boundary points*/
	struct boundary_point** initial_crossing_points = (struct boundary_point**)safe_malloc(4 * sizeof(struct boundary_point*));
	for (int index = 0; index < 4; index++) {
		struct boundary_point* previous_point, * next_point;
		if (index == 0) {
			previous_point = next_point = NULL;
		}
		else {
			previous_point = initial_crossing_points[0];
			next_point = initial_crossing_points[index - 1];
		}
		initial_crossing_points[index] = insert_boundary_point(K->crossings[current_crossing].data[index], NULL, previous_point, next_point);
	}
	pair_strands(initial_crossing_points[0], initial_crossing_points[2]);
	pair_strands(initial_crossing_points[1], initial_crossing_points[3]);
	struct specialized_tangle initial_tangle = make_tangle(current_width, initial_crossing_points[0], YES, initial_crossing_points);
	struct kauffman_summand initial_kauffman_summand = make_kauffman_summand(n + 1, 0, coeffs, 1, initial_tangle);
	/*The array previous_kauffman_summands keeps track of the kauffman summands (tangles with their polynomial coefficient) from tangles with the
	previous boundary points in the cutting, and current_kauffman_summands keeps track of the tangles from tangles with the current boundary 
	points.*/
	struct kauffman_summand** previous_kauffman_summands = NULL;
	struct kauffman_summand** current_kauffman_summands = (struct kauffman_summand**)safe_malloc((size_t)catalan[current_width / 2] * sizeof(struct kauffman_summand*));
	/*Initial crossing is given a 0-smoothing and 1-smoothing, and then added to the current kauffman sumands array*/
	struct kauffman_summand* copy_initial_summand = copy_kauffman_summand(&initial_kauffman_summand);
	smooth_crossing(&initial_kauffman_summand, 0);
	smooth_crossing(copy_initial_summand, 1);
	current_kauffman_summands[tangle_index(&initial_kauffman_summand.basis_tangle)] = &initial_kauffman_summand;
	current_kauffman_summands[tangle_index(&copy_initial_summand->basis_tangle)] = copy_initial_summand;
	int crossings_visited = 1;
	has_visited_crossing[current_crossing] = YES;
	while (crossings_visited++ < n) {
		previous_kauffman_summands = current_kauffman_summands;
		/*To find the next crossing to visit, find the crossing which is touched by the most number of arcs*/
		int max_touched = 0;
		for (int crossing = 0; crossing < n; crossing++) {
			if (crossings_times_touched[crossing] > max_touched && has_visited_crossing[crossing] == NO) {
				current_crossing = crossing;
				max_touched = crossings_times_touched[crossing];
			}
		}
		int strands_present = max_touched;
		old_width = current_width;
		/*Width is changed by -2 * (number of strands present at crossing) + 4 */
		current_width += -2 * strands_present + 4;
		/*All of the C_{current width/2} current kauffman summands must be initially set to null*/
		current_kauffman_summands = (struct kauffman_summand**)safe_malloc((size_t)catalan[current_width / 2] * sizeof(struct kauffman_summand*));
		for (int index = 0; index < catalan[current_width / 2]; index++) 
			current_kauffman_summands[index] = NULL;
		for (int index = 0; index < catalan[old_width / 2]; index++) {
			struct kauffman_summand* P = previous_kauffman_summands[index];
			if (P == NULL) {
				continue;
			}
			/*The current crossing is first added to P*/
			add_crossing(P, K->crossings + current_crossing, strands_present);
			if (P->basis_tangle.has_crossing == NO) {
				/*If P does not have a crossing, meaning it had a twist, it can be immediately added to the kauffman summands*/
				add_to_kauffman_summand_collection(current_kauffman_summands, P);
			}
			else {
				/*If P does have a crossing, then copy it, and then smooth the crossing and add both kauffman summands to the
				array*/
				struct kauffman_summand* Q = copy_kauffman_summand(P);
				smooth_crossing(P, 0);
				add_to_kauffman_summand_collection(current_kauffman_summands, P);
				smooth_crossing(Q, 1);
				add_to_kauffman_summand_collection(current_kauffman_summands, Q);
			}
			
		}
		/*The count of how many times each crossing has been touched is changed for the four arcs visited*/
		for (int index = 0; index < 4; index++) {
			int strand = K->crossings[current_crossing].data[index];
			for (int crossing = 0; crossing < 2; crossing++) 
				if (crossings_at_strand[strand][crossing] != current_crossing) 
					crossings_times_touched[crossings_at_strand[strand][crossing]]++;
		}
		has_visited_crossing[current_crossing] = YES;
	}
	/*At the end, current_kauffman_summands will only contain one kauffman summand*/
	struct kauffman_summand* P = current_kauffman_summands[0];
	/*The kauffman summand is converted to a laurent polynomial, and then returned*/
	struct laurent_polynomial kauffman_polynomial = initialize_polynomial();
	for (int index = 0; index <= n; index++) 
		kauffman_polynomial.coeffs[P->highest_degree - 4 * index + DEGREE_SHIFT] = P->sign * P->coeffs[index];
	adjust_polynomial_degree(&kauffman_polynomial);
	return kauffman_polynomial;
}
