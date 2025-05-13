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
	int trefoil_data[][4] = {{1, 4, 2, 5}, {3, 6, 4, 1}, {5, 2, 6, 3}};
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
	/*Jones polynomial of the trefoil is -q^4 + q^3 + q*/
	struct laurent_polynomial trefoil_jones = jones_polynomial(&trefoil);
	print_polynomial(&trefoil_jones, 'q');
	printf("\n");
	/*Next, finding the Kauffman bracket polynomial and jones polynomial of knot 6_2 from Rolfsen's knot table*/
	int knot_6_2_data[][4] = {{1, 9, 2, 8}, {3, 10, 4, 11}, {5, 12, 6, 1}, {7, 3, 8, 2}, {9, 6, 10, 7}, {11, 4, 12, 5}};
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
	/*Jones polynomial of knot 6_2 is q^5 - 2q^4 + 2q^3 - 2q^2 + 2q - 1 + q^-1*/
	struct laurent_polynomial knot_6_2_jones = jones_polynomial(&knot_6_2);
	print_polynomial(&knot_6_2_jones, 'q');
	printf("\n");
	/*For a final example, finding the Kauffman bracket polynomial and jones polynomial of the torus knot T(7, 5)*/
	int torus_7_5_data[][4] = {{1, 34, 2, 35}, {6, 29, 7, 30}, {7, 52, 8, 53}, {8, 19, 9, 20}, {9, 42, 10, 43}, {14, 37, 15, 38}, {15, 4, 16, 5}, {16, 27, 17, 28}, {17, 50, 18, 51}, {22, 45, 23, 46}, {23, 12, 24, 13}, {24, 35, 25, 36}, {25, 2, 26, 3}, {30, 53, 31, 54}, {31, 20, 32, 21}, {32, 43, 33, 44}, {33, 10, 34, 11}, {38, 5, 39, 6}, {39, 28, 40, 29}, {40, 51, 41, 52}, {41, 18, 42, 19}, {46, 13, 47, 14}, {47, 36, 48, 37}, {48, 3, 49, 4}, {49, 26, 50, 27}, {54, 21, 55, 22}, {55, 44, 56, 45}, {56, 11, 1, 12}};
	n = sizeof(torus_7_5_data) / sizeof(int) / 4;
	struct crossing* torus_7_5_crossings = (struct crossing*)safe_malloc((size_t)n * sizeof(struct crossing));
	for (int crossing = 0; crossing < n; crossing++)
		torus_7_5_crossings[crossing] = make_crossing(torus_7_5_data[crossing]);
	struct knot torus_7_5 = make_knot(n, torus_7_5_crossings);
	printf("Kauffman bracket polynomial of torus knot T(7, 5): ");
	/*Kauffman bracket polynomial using the given PD code is A^36 + A^28 + A^20 - A^4 - A^-4*/
	struct laurent_polynomial torus_7_5_kauffman = kauffman_polynomial(&torus_7_5);
	print_polynomial(&torus_7_5_kauffman, 'A');
	printf("Jones polynomial of torus knot T(7, 5): ");
	/*Jones polynomial of T(7, 5) is -q^22 - q^20 + q^16 + q^14 + q^12*/
	struct laurent_polynomial torus_7_5_jones = jones_polynomial(&torus_7_5);
	print_polynomial(&torus_7_5_jones, 'q');
	return 0;
}
