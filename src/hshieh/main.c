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

#include "kauffman_implementation.h"
#include <stdio.h>

/*Testing the implementation of the algorithm to find the Kauffman bracket polynomial/jones polynomial of a knot*/
int main(void) {
	/*First, finding the kauffman bracket polynomial and jones polynomial of the trefoil knot*/
	int trefoil_data[][4] = { {1, 4, 2, 5}, {3, 6, 4, 1}, {5, 2, 6, 3} };
	int n = sizeof(trefoil_data) / sizeof(int) / 4;
	struct crossing* trefoil_crossings = (struct crossing*)safe_malloc((size_t)n * sizeof(struct crossing));
	for (int crossing = 0; crossing < n; crossing++)
		trefoil_crossings[crossing] = make_crossing(trefoil_data[crossing]);
	struct knot trefoil = make_knot(n, trefoil_crossings);
	printf("Kauffman bracket polynomial of the trefoil: ");
	/*Kauffman bracket polynomial with given PD code is -A^5 - A^-3 + A^-7*/
	struct laurent_polynomial trefoil_kauffman = kauffman_polynomial(&trefoil);
	print_polynomial(&trefoil_kauffman, 'A');
	printf("Jones polynomial of the trefoil: ");
	/*Jones polynomial of the trefoil is -t^4 + t^3 + t*/
	struct laurent_polynomial trefoil_jones = jones_polynomial(&trefoil);
	print_polynomial(&trefoil_jones, 't');
	printf("\n");
	/*Next, finding the Kauffman bracket polynomial and jones polynomial of knot 6_2 from Rolfsen's knot table*/
	int knot_6_2_data[][4] = { {1, 9, 2, 8}, {3, 10, 4, 11}, {5, 12, 6, 1}, {7, 3, 8, 2}, {9, 6, 10, 7}, {11, 4, 12, 5} };
	n = sizeof(knot_6_2_data) / sizeof(int) / 4;
	struct crossing* knot_6_2_crossings = (struct crossing*)safe_malloc((size_t)n * sizeof(struct crossing));
	for (int crossing = 0; crossing < n; crossing++)
		knot_6_2_crossings[crossing] = make_crossing(knot_6_2_data[crossing]);
	struct knot knot_6_2 = make_knot(n, knot_6_2_crossings); 
	printf("Kauffman bracket polynomial of knot 6_2: ");
	/*Kauffman bracket polynomial from the given PD code is A^10 - A^6 + 2A^2 - 2A^-2 + 2A^-6 - 2A^-10 + A^-14*/
	struct laurent_polynomial knot_6_2_kauffman = kauffman_polynomial(&knot_6_2);
	print_polynomial(&knot_6_2_kauffman, 'A');
	printf("Jones polynomial of knot 6_2: ");
	/*Jones polynomial of knot 6_2 is t^5 - 2t^4 + 2t^3 - 2t^2 + 2t - 1 + t^-1*/
	struct laurent_polynomial knot_6_2_jones = jones_polynomial(&knot_6_2);
	print_polynomial(&knot_6_2_jones, 't');
	return 0;
}
