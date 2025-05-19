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
#include "catalan_info.h"

/*Function to find the index associated to a tangle*/
/*For every tangle with no crossings, imagine straightening out the boundary into a line, where the leftmost point
is the first point on the tangle. Then, with every pairing of boundary points, record down how many pairs of boundary
points are nested within that pair of strands. For instance, if there are six points, and points 1 and 4 are paired
together, and points 2 and 3, and 5 and 6, are paired togethers, then the list would read 1, 0, 0 (since there is 1 pair
of boundary points between points 1 and 4, 0 pairs between points 2 and 3, and 0 pairs between points 5 and 6). The index
of the tangle is the number of possible lists (as described above), of which there are C_{number of boundary points/2}, which are
lexicographically smaller than the current list. The index is always between 0 and C_{number of boundary points/2} - 1, 
inclusive.*/
int tangle_index(struct specialized_tangle* T) {
	struct boundary_point* BP = T->first_boundary_point;
	int width = T->number_of_boundary_points;

	/*The array point_pairs keeps track of which boundary point is paired with which other one, while the array 
	dist_to_pair keeps track of the list described above*/
	int* adjusted_points = (int*)safe_malloc((2 * MAX_CROSSINGS + 1) * sizeof(int));
	int* point_pairs = (int*)safe_malloc((size_t)width * sizeof(int));
	int* dist_to_pair = (int*)safe_malloc((size_t)width / 2 * sizeof(int));
	int pairs = 0;
	for (int index = 0; index < width; index++) {
		if (BP->strand_pair->strand_number < 0) {
			BP->strand_pair->strand_number *= -1;
			int pair_index = adjusted_points[BP->strand_pair->strand_number];
			dist_to_pair[point_pairs[pair_index]] = (index - pair_index - 1) / 2;
		}
		else {
			adjusted_points[BP->strand_number] = index;
			point_pairs[index] = pairs++;
			BP->strand_number *= -1;
		}
		BP = BP->next;
	}

	safe_free(adjusted_points);
	safe_free(point_pairs);

	/*To find the index of the tangle, we use a stack, which keeps tracks of strand pairs which are nested between 
	other pairs of strands, and an element from the list is added to the stack if it is positive, as it indicates
	that there is at least one pair of strands nested between that pair. If there is an element at the top, then the
	catalan prefixes array counts the number of tangles with that element at the top which are lexicographically
	smaller than the current tangle. */
	struct stack pair_starts = make_stack(pairs + 1);
	struct stack pair_distances = make_stack(pairs + 1);
	push_stack(&pair_starts, -1);
	push_stack(&pair_distances, pairs);
	int* tangle_index_summands = (int*)safe_malloc((size_t)pairs * sizeof(int));
	int* tangle_index_multipliers = (int*)safe_malloc((size_t)pairs * sizeof(int));
	int* tangle_index_dividers = (int*)safe_malloc((size_t)pairs * sizeof(int));
	for (int index = 0; index < pairs; index++) 
		tangle_index_multipliers[index] = tangle_index_dividers[index] = 1;
	for (int index = 0; index < pairs; index++) {
		int current_dist = dist_to_pair[index];
		tangle_index_summands[index] = catalan_prefix[peek_stack(&pair_starts) + peek_stack(&pair_distances) - index + 1][current_dist];
		while (peek_stack(&pair_starts) + peek_stack(&pair_distances) == index) {
			int start = pop_stack(&pair_starts);
			pop_stack(&pair_distances);
			if (start == -1)
				break;
			int extra_pairs = peek_stack(&pair_starts) + peek_stack(&pair_distances) - index;
			tangle_index_multipliers[start] *= catalan[extra_pairs];
			tangle_index_dividers[index] *= catalan[extra_pairs];
		}
		if (current_dist > 0) {
			push_stack(&pair_starts, index);
			push_stack(&pair_distances, current_dist);
		}
	}
	safe_free(dist_to_pair);
	int tangle_index = 0;
	int current_multiplier = 1;
	for (int index = 0; index < pairs; index++) {
		tangle_index += current_multiplier * tangle_index_summands[index];
		current_multiplier *= tangle_index_multipliers[index];
		current_multiplier /= tangle_index_dividers[index];
	}
	safe_free(tangle_index_summands);
	safe_free(tangle_index_multipliers);
	safe_free(tangle_index_dividers);
	return tangle_index;
}
