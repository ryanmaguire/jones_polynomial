#include <stdlib.h>
#include "pd_code_knot.h"

/* Compute the Alexander Polynomial of a knot given an arbitrary node of its PD code representation */
struct int_polynomial pd_code_alexander_polynomial(struct pd_code_node* K)
{
	struct pd_code_node* head_node;
	struct pd_code_node* current_node = K;

	/* We will begin by first doing a quick survey to count the number of crossings of the knot */
	/* Count nodes in front of K */
	int num_crossings = 1;
	while (current_node->prev) {
		current_node = current_node->prev;
		num_crossings += 1;
	}
	head_node = current_node;

	/* Count nodes after K*/
	current_node = K;
	while (current_node->next) {
		current_node = current_node->next;
		num_crossings += 1;
	}

	/* Crossings = pd_arcs / 2 */
	int num_pd_arcs = 2 * num_crossings;

	/* This array will be populated with 1's and 0's, where 1 if the pd_arc is connected to the next one via an over strand across a crossing and 0 otherwise */
	/* This will allow us to make a table of which pd_arcs correspond to which alexander_arcs */
	/* Since arcs are numbered from 0, the label of each arc corresponds to its index. */
	int* pd_arc_connections = malloc(num_pd_arcs * sizeof(int));
	if (!pd_arc_connections) { // cooked
		return new_int_polynomial(0);
	}
	/* Initialize to all 0s */
	for (int i = 0; i < num_pd_arcs; i++) {
		pd_arc_connections[i] = 0;
	}

	/* Iterate through the linked list and fill up pd_arc_connections */
	current_node = head_node;
	int over1, over2; // The two over arcs at each crossing
	do {
		over1 = current_node->tuple->arcs[1];
		over2 = current_node->tuple->arcs[3];
		if ((over1 - over2 + num_pd_arcs) % num_pd_arcs == num_pd_arcs - 1) { // Right handed crossing
			pd_arc_connections[over1] = 1;
		}
		else { // Left handed crossing
			pd_arc_connections[over2] = 1;
		}
		current_node = current_node->next;
	} while (current_node);
	
	/* Atlas of which alexander_arc every pd_arc corresponds to. */
	int* pd_arc_atlas = malloc(num_pd_arcs * sizeof(int));
	if (!pd_arc_atlas) { // cooked
		return new_int_polynomial(0);
	}
	pd_arc_atlas[0] = 0;

	/* Check for wraparound first (if the first arc goes back before the first pd_arc) */
	int current_index = num_pd_arcs - 1;
	while (pd_arc_connections[current_index] == 1) {
		pd_arc_atlas[current_index] = 0;
		current_index--;
	}
	int last_unchecked_index = current_index;

	/* Proceed forwards from index 0 */
	current_index = 0;
	int current_alexaner_arc = 0;
	while (current_index < last_unchecked_index) {
		if (pd_arc_connections[current_index] == 0) {
			current_alexaner_arc++;
		}
		pd_arc_atlas[current_index + 1] = current_alexaner_arc;
		current_index++;
	}

	/* We now have pd_arc_atlas filled, and we can proceed with Livingston's algorithm for computing the Alexander Polynomial. */
	/* pd_arc_connections is no longer needed */
	free(pd_arc_connections);

	/* Create big matrix. Since we plan on deleting the last column and last row anyways, we will just exclude them from the beginning */
	struct int_polynomial_matrix A = new_int_polynomial_matrix(num_crossings - 1, num_crossings - 1);

	/* Alexander matrix entries */
	struct int_polynomial one_minus_t_poly = new_int_polynomial(1);
	one_minus_t_poly.coeffs[0] = 1;
	one_minus_t_poly.coeffs[1] = -1;

	struct int_polynomial t_poly = new_int_polynomial(1);
	t_poly.coeffs[0] = 0;
	t_poly.coeffs[1] = 1;

	struct int_polynomial minus_one_poly = new_int_polynomial(0);
	minus_one_poly.coeffs[0] = -1;

	struct int_polynomial zero_poly = new_int_polynomial(0);
	zero_poly.coeffs[0] = 0;

	/* Initialize A to all zeroes */
	for (unsigned int row = 0; row < A.rows; row++) {
		for (unsigned int col = 0; col < A.cols; col++) {
			A.entries[row][col] = zero_poly;
		}
	}

	/* Loop through every crossing */
	current_node = head_node;
	int i, j, k; // See Livingston Figure 3.15a and 3.15b
	int current_node_index = 0;
	while (current_node_index < num_crossings - 1) {
		over1 = current_node->tuple->arcs[1];
		over2 = current_node->tuple->arcs[3];
		if ((over1 - over2 + num_pd_arcs) % num_pd_arcs == num_pd_arcs - 1) { // Right handed crossing
			i = pd_arc_atlas[current_node->tuple->arcs[1]];
			j = pd_arc_atlas[current_node->tuple->arcs[0]];
			k = pd_arc_atlas[current_node->tuple->arcs[2]];
		}
		else { // Left handed crossing
			i = pd_arc_atlas[current_node->tuple->arcs[3]];
			j = pd_arc_atlas[current_node->tuple->arcs[2]]; // A bit of a hack - we swap j and k because their entries will be swapped
			k = pd_arc_atlas[current_node->tuple->arcs[0]]; // A bit of a hack - we swap j and k because their entries will be swapped
		}
		/* j and k are swapped if the crossing is left handed, so the resulting polynomial entries will be according to the right handed crossing in 3.15a */

		if (i != num_crossings - 1) {
			A.entries[current_node_index][i] = one_minus_t_poly;
		}
		if (j != num_crossings - 1) {
			A.entries[current_node_index][j] = minus_one_poly;
		}
		if (k != num_crossings - 1) {
			A.entries[current_node_index][k] = t_poly;
		}

		current_node = current_node->next;
		current_node_index++;
	}

	/* We will still require scaling because this might contain several extra factors of t */
	struct int_polynomial unscaled_result = determinant_int_polynomial_matrix(A, - (num_crossings - 1) / 2);

	free(pd_arc_atlas);
	free(zero_poly.coeffs);
	free(minus_one_poly.coeffs);
	free(t_poly.coeffs);
	free(one_minus_t_poly.coeffs);
	destruct_int_polynomial_matrix(A);

	unsigned int new_degree = unscaled_result.degree;
	unsigned int exponent = 0;
	while (unscaled_result.coeffs[exponent] == 0) {
		new_degree--;
		exponent++;
	}

	struct int_polynomial result = new_int_polynomial(new_degree);
	for (exponent = 0; exponent <= new_degree; exponent++) {
		result.coeffs[exponent] = unscaled_result.coeffs[exponent - result.degree + unscaled_result.degree];
	}

	free(unscaled_result.coeffs);

	return result;
}