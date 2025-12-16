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
#include "load_balanced.h"

/*Keeps track of which crossings have been visited while performing dfs*/
static enum boolean* visited;
/*Contains direction of every crossing*/
static int* directions;
/*Contains the other crossings whose chords intersect a crossing*/
static int** intersections;
/*Contains number of other crossings each crossing intersects*/
static int* intersection_counts;

/*Function to perform dfs to determine all crossing directions*/
void directions_dfs(const int, const int);

/*Functions to copy array, find position of an element in an array, and reverse part of an array*/
int* copy_array(int*, const int);
int array_position(int*, const int, const int);
void reverse_array(int*, const int, const int);

/*Function to convert DT code of a knot to PD code; based on the program in the Mathematica Knot Theory package
written by Siddarth Sankaran*/
struct PD_knot* DT_to_PD(const struct DT_knot* const K) {
	int n = K->number_of_crossings;

	/*DT code is converted to a gauss input, and original edge list with all edges from 1 to 2n is made*/
	int* gauss_input = safe_malloc(2 * (size_t)n * sizeof(int));
	int* original_edgelist = safe_malloc(2 * (size_t)n * sizeof(int));
	for (int i = 0; i < 2 * n; i++)
		original_edgelist[i] = i + 1;
	int* edgelist = copy_array(original_edgelist, 2 * n);
	for (int index = 0; index < n; index++) {
		int even_index = DT_letter_to_number(K->DT_code[index]);
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
	intersections = safe_malloc((size_t)n * sizeof(int*));
	for (int index = 0; index < n; index++)
		intersections[index] = safe_malloc((size_t)n * sizeof(int));
	intersection_counts = safe_calloc((size_t)n, sizeof(int));
	for (int crossing = 1; crossing <= n; crossing++) {
		int negative_position = array_position(chords, 2 * n, -crossing);
		int positive_position = array_position(chords, 2 * n, crossing);
		int first_position = MIN(negative_position, positive_position);
		int second_position = MAX(negative_position, positive_position);
		int* counts = safe_calloc((size_t)n, sizeof(int));
		for (int index = first_position + 1; index <= second_position - 1; index++)
			counts[abs(chords[index]) - 1]++;
		for (int other_crossing = 0; other_crossing < n; other_crossing++)
			if (counts[other_crossing] == 1)
				intersections[crossing - 1][intersection_counts[crossing - 1]++] = other_crossing;
		SAFE_FREE(counts);
	}

	/*Any two crossings which intersect each other must have opposite direction (right/left handed). Note
	that if we draw an edge between every two crossings who have intersecting chords, then we get a connected
	and bipartite graph. So, we can start by setting crossing 0 to be right-handed, and then perform a dfs to
	label every crossing with their direction.
	*/
	visited = safe_malloc((size_t)n * sizeof(enum boolean));
	for (int index = 0; index < n; index++)
		visited[index] = FALSE;
	visited[0] = TRUE;
	directions = safe_malloc((size_t)n * sizeof(int));
	directions_dfs(0, 1);

	/*The knot in PD code is created by going through every crossing and finding the edge labels which belong
	to it*/
	struct PD_knot* temp = safe_malloc(sizeof(struct PD_knot));
	temp->number_of_crossings = n;
	temp->crossings = safe_malloc((size_t)n * sizeof(struct PD_crossing));
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
			temp->crossings[crossing - 1].data[index] = crossing_labels[(index_shift + index) % 4];
	}
	SAFE_FREE(gauss_input);
	SAFE_FREE(original_edgelist);
	SAFE_FREE(edgelist);
	SAFE_FREE(chords);
	for (int index = 0; index < n; index++) {
		SAFE_FREE(intersections[index]);
	}
	SAFE_FREE(intersections);
	SAFE_FREE(intersection_counts);
	SAFE_FREE(visited);
	SAFE_FREE(directions);
	return temp;
}

/*When visiting a crossing, mark it with the sign, and then visit all of its neighbors which have not been
visited yet*/
void directions_dfs(const int crossing, const int sign) {
	directions[crossing] = sign;
	for (int index = 0; index < intersection_counts[crossing]; index++) {
		int neighbor = intersections[crossing][index];
		if (!visited[neighbor]) {
			visited[neighbor] = TRUE;
			/*Note that all of its neighbors will have the opposite sign*/
			directions_dfs(neighbor, -sign);
		}
	}
}

/*Function which returns a copy of an array given the array and its size*/
int* copy_array(int* array, const int n) {
	int* temp = safe_malloc((size_t)n * sizeof(int));
	for (int i = 0; i < n; i++)
		temp[i] = array[i];
	return temp;
}

/*Function to return the position of the first occurence of an element in an array, and -1 otherwise*/
int array_position(int* array, const int size, const int element) {
	for (int i = 0; i < size; i++) {
		if (array[i] == element)
			return i;
	}
	return -1;
}

/*Function which reverses an array between a given start index and end index, inclusive*/
void reverse_array(int* array, const int start, const int end) {
	int start_index = start;
	int end_index = end;
	while (start_index < end_index) {
		int temp = array[start_index];
		array[start_index++] = array[end_index];
		array[end_index--] = temp;
	}
}