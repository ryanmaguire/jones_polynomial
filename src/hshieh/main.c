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
	int trefoil_data[][4] = { {152, 95, 153, 96}, {153, 38, 154, 39}, {154, 135, 1, 136},  {1, 78, 2, 79}, {2, 21, 3, 22}, {3, 118, 4, 119}, {4, 61, 5, 62},  {96, 39, 97, 40}, {97, 136, 98, 137}, {98, 79, 99, 80},  {99, 22, 100, 23}, {100, 119, 101, 120}, {101, 62, 102, 63},  {102, 5, 103, 6}, {40, 137, 41, 138}, {41, 80, 42, 81},  {42, 23, 43, 24}, {43, 120, 44, 121}, {44, 63, 45, 64},  {45, 6, 46, 7}, {46, 103, 47, 104}, {138, 81, 139, 82},  {139, 24, 140, 25}, {140, 121, 141, 122}, {141, 64, 142, 65},  {142, 7, 143, 8}, {143, 104, 144, 105}, {144, 47, 145, 48},  {82, 25, 83, 26}, {83, 122, 84, 123}, {84, 65, 85, 66},  {85, 8, 86, 9}, {86, 105, 87, 106}, {87, 48, 88, 49},  {88, 145, 89, 146}, {26, 123, 27, 124}, {27, 66, 28, 67},  {28, 9, 29, 10}, {29, 106, 30, 107}, {30, 49, 31, 50},  {31, 146, 32, 147}, {32, 89, 33, 90}, {124, 67, 125, 68},  {125, 10, 126, 11}, {126, 107, 127, 108}, {127, 50, 128, 51},  {128, 147, 129, 148}, {129, 90, 130, 91}, {130, 33, 131, 34},  {68, 11, 69, 12}, {69, 108, 70, 109}, {70, 51, 71, 52},  {71, 148, 72, 149}, {72, 91, 73, 92}, {73, 34, 74, 35},  {74, 131, 75, 132}, {12, 109, 13, 110}, {13, 52, 14, 53},  {14, 149, 15, 150}, {15, 92, 16, 93}, {16, 35, 17, 36},  {17, 132, 18, 133}, {18, 75, 19, 76}, {110, 53, 111, 54},  {111, 150, 112, 151}, {112, 93, 113, 94}, {113, 36, 114, 37},  {114, 133, 115, 134}, {115, 76, 116, 77}, {116, 19, 117, 20},  {54, 151, 55, 152}, {55, 94, 56, 95}, {56, 37, 57, 38},  {57, 134, 58, 135}, {58, 77, 59, 78}, {59, 20, 60, 21},
 {60, 117, 61, 118} };
	int n = sizeof(trefoil_data) / sizeof(int) / 4;
	printf("n = %d\n", n);
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
