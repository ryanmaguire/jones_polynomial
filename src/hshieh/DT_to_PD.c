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
#include <math.h>

/*Keeps track of which crossings have been visited while performing dfs*/
static int* visited;
/*Contains direction of every crossing*/
static int* directions;
/*Contains the other crossings whose chords intersect a crossing*/
static int** intersections;
/*Contains number of other crossings each crossing intersects*/
static int* intersection_counts;

/*Function to perform dfs to determine all crossing directions*/
void directions_dfs(int, int);

/*Function to convert DT code of a knot to PD code; based on the program in the Mathematica Knot Theory package
written by Siddarth Sankaran*/
struct knot DT_to_PD(struct DT_knot K) {
	int n = K.number_of_crossings;

	/*DT code is converted to a gauss input, and original edge list with all edges from 1 to 2n is made*/
	int* gauss_input = (int*)safe_malloc(2 * (size_t)n * sizeof(int));
	int* original_edgelist = (int*)safe_malloc(2 * (size_t)n * sizeof(int));
	for (int i = 0; i < 2 * n; i++)
		original_edgelist[i] = i + 1;
	int* edgelist = copy_array(original_edgelist, 2 * n);
	for (int index = 0; index < n; index++) {
		int even_index = DT_letter_to_number(K.DT_code[index]);
		if (even_index < 0) {
			gauss_input[2 * index] = -index - 1;
			gauss_input[-even_index] = index + 1;
		}
		else {
			gauss_input[2 * index] = index + 1;
			gauss_input[even_index] = -index - 1;
		}
	}

	/*Knot is now relaxed, so direction of traversal is reversed after visiting every crossing; this means
	reversing all of the elements between -crossing and crossing in the chords array, as well as reversing
	a portion of the edgelist array*/
	int* chords = copy_array(gauss_input, 2 * n);
	for (int crossing = 1; crossing <= n; crossing++) {
		int negative_position = array_position(chords, 2 * n, -crossing);
		int positive_position = array_position(chords, 2 * n, crossing);
		int first_position = MIN(negative_position, positive_position);
		int second_position = MAX(negative_position, positive_position);
		reverse_array(chords, first_position + 1, second_position - 1);
		reverse_array(edgelist, first_position + 1, second_position);
	}

	/*All of the other crossings which intersect a certain crossing c are recorded by finding all indices
	which appear exactly once in the chords array between c and -c*/
	intersections = (int**)safe_malloc((size_t)n * sizeof(int*));
	for (int index = 0; index < n; index++)
		intersections[index] = (int*)safe_malloc((size_t)n * sizeof(int));
	intersection_counts = (int*)safe_calloc((size_t)n, sizeof(int));
	for (int crossing = 1; crossing <= n; crossing++) {
		int negative_position = array_position(chords, 2 * n, -crossing);
		int positive_position = array_position(chords, 2 * n, crossing);
		int first_position = MIN(negative_position, positive_position);
		int second_position = MAX(negative_position, positive_position);
		int* counts = (int*)safe_calloc((size_t)n, sizeof(int));
		for (int index = first_position + 1; index <= second_position - 1; index++)
			counts[abs(chords[index]) - 1]++;
		for (int other_crossing = 0; other_crossing < n; other_crossing++) 
			if (counts[other_crossing] == 1)
				intersections[crossing - 1][intersection_counts[crossing - 1]++] = other_crossing;
	}

	/*Any two crossings which intersect each other must have opposite direction (right/left handed). Note 
	that if we draw an edge between every two crossings who have intersecting chords, then we get a connected 
	and bipartite graph. So, we can start by setting crossing 0 to be right-handed, and then perform a dfs to 
	label every crossing with their direction.
	*/
	visited = (int*)safe_malloc((size_t)n * sizeof(int));
	for (int index = 0; index < n; index++)
		visited[index] = NO;
	visited[0] = YES;
	directions = (int*)safe_malloc((size_t)n * sizeof(int));
	directions_dfs(0, 1);

	/*The knot in PD code is created by going through every crossing and finding the edge labels which belong
	to it*/
	struct knot temp;
	temp.number_of_crossings = n;
	temp.crossings = (struct crossing*)safe_malloc((size_t)n * sizeof(struct crossing));
	for (int crossing = 1; crossing <= n; crossing++) {
		int original_position = array_position(gauss_input, 2 * n, -crossing);
		int first_label = original_edgelist[original_position];
		int negative_position = array_position(chords, 2 * n, -crossing);
		int positive_position = array_position(chords, 2 * n, crossing);
		int crossing_labels[4];
		crossing_labels[0] = edgelist[negative_position];
		crossing_labels[1] = edgelist[(negative_position + 1) % (2 * n)];
		crossing_labels[2] = edgelist[positive_position];
		crossing_labels[3] = edgelist[(positive_position + 1) % (2 * n)];
		/*If the crossing is left-handed, reverse the order of the labels*/
		if (directions[crossing - 1] == -1)
			reverse_array(crossing_labels, 1, 3);
		int index_shift = array_position(crossing_labels, 4, first_label);
		/*When putting the labels into the PD code, shift the array so that the first label becomes the first
		element*/
		for (int index = 0; index < 4; index++)
			temp.crossings[crossing - 1].data[index] = crossing_labels[(index_shift + index) % 4];
	}
	return temp;
}

/*When visiting a crossing, mark it with the sign, and then visit all of its neighbors which have not been
visited yet*/
void directions_dfs(int crossing, int sign) {
	directions[crossing] = sign;
	for (int index = 0; index < intersection_counts[crossing]; index++) {
		int neighbor = intersections[crossing][index];
		if (visited[neighbor] == NO) {
			visited[neighbor] = YES;
			/*Note that all of its neighbors will have the opposite sign*/
			directions_dfs(neighbor, -sign);
		}
	}
}
