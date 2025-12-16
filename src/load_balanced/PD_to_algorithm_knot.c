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

/* Function to convert a knot in PD code to a knot as defined in the header file */
struct link* PD_to_algorithm_knot(const struct PD_knot* K)
{
	size_t i;

	if (K == NULL)
		return NULL;

	struct link* temp = safe_malloc(sizeof(*temp));
	size_t number_of_crossings = K->number_of_crossings;

	temp->number_of_components = 1;
	temp->number_of_crossings_in_components = safe_calloc(
		MAX_CROSSINGS, sizeof(*temp->number_of_crossings_in_components)
	);

	temp->number_of_crossings_in_components[0] = number_of_crossings;

	temp->first_crossing_in_components = safe_malloc(
		MAX_CROSSINGS * sizeof(*temp->first_crossing_in_components)
	);

	struct crossing** crossings_array = safe_malloc(number_of_crossings * sizeof(*crossings_array));
	enum boolean* visited_edges = safe_malloc((2 * number_of_crossings + 1) * sizeof(enum boolean));

	for (i = 0; i <= 2 * number_of_crossings; i++)
		visited_edges[i] = FALSE;

	struct crossing** visited_edge_crossings = safe_malloc((2 * number_of_crossings + 1) * sizeof(struct crossing*));

	int* visited_edge_ports = safe_malloc((2 * number_of_crossings + 1) * sizeof(int));

	for ( i = 0; i < number_of_crossings; i++) {
		struct PD_crossing* current_crossing = K->crossings + i;
		crossings_array[i] = safe_malloc(sizeof(struct crossing));
		crossings_array[i]->id = i;
		crossings_array[i]->overdirection = (((current_crossing->data[1] - current_crossing->data[3] + 2 * number_of_crossings) % (2 * number_of_crossings)) == 1) ? OVER_POS : OVER_NEG;
		crossings_array[i]->over_component = crossings_array[i]->under_component = 0;

		for (int j = 0; j < 4; j++)
		{
			int current_edge = current_crossing->data[j];

			if (visited_edges[current_edge])
			{
				struct crossing* neighbor_crossing = visited_edge_crossings[current_edge];
				int neighbor_port = visited_edge_ports[current_edge];
				crossings_array[i]->data[j] = neighbor_crossing;
				crossings_array[i]->ports[j] = neighbor_port;
				neighbor_crossing->data[neighbor_port] = crossings_array[i];
				neighbor_crossing->ports[neighbor_port] = j;
			}

			else
			{
				visited_edges[current_edge] = TRUE;
				visited_edge_crossings[current_edge] = crossings_array[i];
				visited_edge_ports[current_edge] = j;
			}
		}
	}

	temp->first_crossing_in_components[0] = crossings_array[0];

	SAFE_FREE(crossings_array);
	SAFE_FREE(visited_edges);
	SAFE_FREE(visited_edge_crossings);
	SAFE_FREE(visited_edge_ports);

	return temp;
}