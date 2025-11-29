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

/*Functions to push, pop, and peek from a stack*/
void push_stack(int*, int*, int);
int pop_stack(int*, int*);
int peek_stack(int*, int*);

/*Function to find the index associated to a tangle*/
/*For every tangle with no crossings, imagine straightening out the boundary into a line, where the leftmost point
is the first point on the tangle. Then, with every pairing of boundary points, record down how many pairs of boundary
points are nested within that pair of strands. For instance, if there are six points, and points 1 and 4 are paired
together, and points 2 and 3, and 5 and 6, are paired togethers, then the list would read 1, 0, 0 (since there is 1 pair
of boundary points between points 1 and 4, 0 pairs between points 2 and 3, and 0 pairs between points 5 and 6). The index
of the tangle is the number of possible lists (as described above), of which there are C_{number of boundary points/2}, which are
lexicographically smaller than the current list. The index is always between 0 and C_{number of boundary points/2} - 1, 
inclusive.*/
int tangle_index(const struct specialized_tangle* const T) {
	struct boundary_point* BP = T->first_boundary_point;
	int width = T->number_of_boundary_points;

	/*The array point_pairs keeps track of which boundary point is paired with which other one, while the array 
	dist_to_pair keeps track of the list described above*/
	int* adjusted_points = safe_malloc((2 * MAX_CROSSINGS + 1) * sizeof(int));
	int* point_pairs = safe_malloc((size_t)width * sizeof(int));
	int* dist_to_pair = safe_malloc((size_t)width / 2 * sizeof(int));
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

	SAFE_FREE(adjusted_points);
	SAFE_FREE(point_pairs);
	/*To find the index of the tangle, we use a stack, which keeps tracks of strand pairs which are nested between 
	other pairs of strands, and an element from the list is added to the stack if it is positive, as it indicates
	that there is at least one pair of strands nested between that pair. If there is an element at the top, then the
	catalan prefixes array counts the number of tangles with that element at the top which are lexicographically
	smaller than the current tangle. */
	int* pair_starts_stack = safe_malloc(((size_t)pairs + 1) * sizeof(int));
	int pair_starts_free_position = 0;
	int* pair_distances_stack = safe_malloc(((size_t)pairs + 1) * sizeof(int));
	int pair_distances_free_position = 0;
	push_stack(pair_starts_stack, &pair_starts_free_position, -1);
	push_stack(pair_distances_stack, &pair_distances_free_position, pairs);
	int* tangle_index_summands = safe_malloc((size_t)pairs * sizeof(int));
	int* tangle_index_multipliers = safe_malloc((size_t)pairs * sizeof(int));
	int* tangle_index_dividers = safe_malloc((size_t)pairs * sizeof(int));
	for (int index = 0; index < pairs; index++) 
		tangle_index_multipliers[index] = tangle_index_dividers[index] = 1;
	for (int index = 0; index < pairs; index++) {
		int current_dist = dist_to_pair[index];
		tangle_index_summands[index] = catalan_prefix[peek_stack(pair_starts_stack, &pair_starts_free_position) + peek_stack(pair_distances_stack, &pair_distances_free_position) - index + 1][current_dist];
		while (peek_stack(pair_starts_stack, &pair_starts_free_position) + peek_stack(pair_distances_stack, &pair_distances_free_position) == index) {
			int start = pop_stack(pair_starts_stack, &pair_starts_free_position);
			pop_stack(pair_distances_stack, &pair_distances_free_position);
			if (start == -1)
				break;
			int extra_pairs = peek_stack(pair_starts_stack, &pair_starts_free_position) + peek_stack(pair_distances_stack, &pair_distances_free_position) - index;
			tangle_index_multipliers[start] *= catalan[extra_pairs];
			tangle_index_dividers[index] *= catalan[extra_pairs];
		}
		if (current_dist > 0) {
			push_stack(pair_starts_stack, &pair_starts_free_position, index);
			push_stack(pair_distances_stack, &pair_distances_free_position, current_dist);
		}
	}
	SAFE_FREE(dist_to_pair);
	SAFE_FREE(pair_starts_stack);
	SAFE_FREE(pair_distances_stack);
	int tangle_index = 0;
	int current_multiplier = 1;
	for (int index = 0; index < pairs; index++) {
		tangle_index += current_multiplier * tangle_index_summands[index];
		current_multiplier *= tangle_index_multipliers[index];
		current_multiplier /= tangle_index_dividers[index];
	}
	SAFE_FREE(tangle_index_summands);
	SAFE_FREE(tangle_index_multipliers);
	SAFE_FREE(tangle_index_dividers);
	return tangle_index;
}

/*Function to push element onto a stack*/
void push_stack(int* stack_elements, int* free_position, int element) {
	stack_elements[(*free_position)++] = element;
}

/*Function which pops the first element on a stack if there is one, and otherwise returns -1000*/
int pop_stack(int* stack_elements, int* free_position) {
	if (*free_position > 0)
		return stack_elements[--*free_position];
	else
		return -1000;
}

/*Function which returns the first element on top of the stack if there is one, and otherwise returns -1000*/
int peek_stack(int* stack_elements, int* free_position) {
	if (*free_position > 0)
		return stack_elements[*free_position - 1];
	else
		return -1000;
}
