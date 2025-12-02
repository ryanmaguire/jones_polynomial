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

int main() 
{
	/* Starting to run tests with trefoil */
	struct PD_crossing trefoil_PD_crossings[] = { {{1, 5, 2, 4}}, {{3, 1, 4, 6}}, {{5, 3, 6, 2}} };
	struct PD_knot trefoil_PD = { 3, trefoil_PD_crossings };

	struct PD_crossing figure_eight_PD_crossings[] = { {{4,2,5,1}}, {{8,6,1,5}}, {{6,3,7,4}}, {{2,7,3,8}} };
	struct PD_knot figure_eight_PD = {4, figure_eight_PD_crossings};

	struct PD_crossing six_three_knot_PD_crossings[] = { {{4,2,5,1}}, {{8,4,9,3}}, {{12,9,1,10}}, {{10,5,11,6}}, {{6,11,7,12}}, {{2,8,3,7}} };
	struct PD_knot six_three_PD = {6, six_three_knot_PD_crossings};

	struct PD_crossing eight_21_knot_PD_crossings[] = { {{1,4,2,5}}, {{3,8,4,9}}, {{12,6,13,5}}, {{13,16,14,1}}, {{9,14,10,15}}, {{15,10,16,11}}, {{6,12,7,11}}, {{7,2,8,3}} };
	struct PD_knot eight_21_PD = {8, eight_21_knot_PD_crossings};

	struct PD_crossing nine_43_knot_PD_crossings[] = { {{4,2,5,1}}, {{10,6,11,5}}, {{8,3,9,4}}, {{2,9,3,10}}, {{14,8,15,7}}, {{15,1,16,18}}, {{11,17,12,16}}, {{17,13,18,12}}, {{6,14,7,13}} };
	struct PD_knot nine_43_PD = {9, nine_43_knot_PD_crossings};

	struct link* trefoil = PD_to_algorithm_knot(&trefoil_PD);
	printf("writhe: %d\n", writhe(trefoil));

	/*struct link* nine_43_knot = PD_to_algorithm_knot(&nine_43_PD);
	struct laurent_polynomial* test_polynomial_nine_43 = jones_polynomial(nine_43_knot);
	delete_polynomial(test_polynomial_nine_43);
	return 0;*/

	/*struct link* eight_21_knot = PD_to_algorithm_knot(&eight_21_PD);
	struct laurent_polynomial* test_polynomial_eight_21 = jones_polynomial(eight_21_knot);
	delete_polynomial(test_polynomial_eight_21);
	return 0;*/

	/*struct link* figure_eight_knot = PD_to_algorithm_knot(&figure_eight_PD);
	struct laurent_polynomial* test_polynomial_figure_eight = jones_polynomial(figure_eight_knot);
	delete_polynomial(test_polynomial_figure_eight);
	return 0;*/

	/*struct link* six_three_knot = PD_to_algorithm_knot(&six_three_PD);
	struct laurent_polynomial* test_polynomial_six_three = jones_polynomial(six_three_knot);
	print_polynomial(test_polynomial_six_three, 'q');
	delete_polynomial(test_polynomial_six_three);*/

	struct laurent_polynomial* test_polynomial = jones_polynomial(trefoil);
	print_polynomial(test_polynomial, 'q');
	delete_polynomial(test_polynomial);

	return 0;
}