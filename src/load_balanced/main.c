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
#include <time.h>

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

	struct PD_crossing eleven_42_knot_PD_crossings[] = { {{4,2,5,1}}, {{8,4,9,3}}, {{12,5,13,6}}, {{2,8,3,7}}, {{9,18,10,19}}, {{11,21,12,20}}, {{6,13,7,14}}, {{15,10,16,11}}, {{17,22,18,1}}, {{19,15,20,14}}, {{21,16,22,17}} };
	struct PD_knot eleven_42_PD = {11, eleven_42_knot_PD_crossings};

	struct PD_crossing T_7_4_PD_crossings[] = { {{9,41,10,40}}, {{20,42,21,41}}, {{31,1,32,42}}, {{21,11,22,10}}, {{32,12,33,11}}, {{1,13,2,12}}, {{33,23,34,22}}, {{2,24,3,23}}, {{13,25,14,24}}, {{3,35,4,34}}, {{14,36,15,35}}, {{25,37,26,36}}, {{15,5,16,4}}, {{26,6,27,5}}, {{37,7,38,6}}, {{27,17,28,16}}, {{38,18,39,17}}, {{7,19,8,18}}, {{39,29,40,28}}, {{8,30,9,29}}, {{19,31,20,30}} };
	struct PD_knot T_7_4_PD = {21, T_7_4_PD_crossings};

	struct PD_crossing test_PD_crossings[] = { {{6,2,7,1}}, {{7,2,8,3}}, {{5,4,4,3}}, {{5,8,6,1}} };
	struct PD_knot test_PD = {4, test_PD_crossings};

	struct link* trefoil = PD_to_algorithm_knot(&trefoil_PD);
	//printf("writhe: %d\n", writhe(trefoil));

	struct crossing* hopf_crossing_one = (struct crossing*) safe_malloc(sizeof(struct crossing));
	struct crossing* hopf_crossing_two = (struct crossing*) safe_malloc(sizeof(struct crossing));
	for (int i = 0; i < 4; i++) {
		hopf_crossing_one->data[i] = hopf_crossing_two;
		hopf_crossing_one->ports[i] = (i % 2 == 0) ? (i + 1) : (i - 1);
		hopf_crossing_two->data[i] = hopf_crossing_one;
		hopf_crossing_two->ports[i] = (i % 2 == 0) ? (i + 1) : (i - 1);
	}
	hopf_crossing_one->overdirection = 1;
	hopf_crossing_two->overdirection = 1;
	hopf_crossing_one->over_component = 0;
	hopf_crossing_two->over_component = 1;
	hopf_crossing_one->under_component = 1;
	hopf_crossing_two->under_component = 0;
	struct link* hopf_link = (struct link*) safe_malloc(sizeof(struct link));
	hopf_link->number_of_components = 2;
	hopf_link->first_crossing_in_components = (struct crossing**) safe_malloc(2 * sizeof(struct crossing*));
	hopf_link->number_of_crossings_in_components = (int*)safe_calloc(2, sizeof(int));
	hopf_link->number_of_crossings_in_components[0] = 2;
	hopf_link->number_of_crossings_in_components[1] = 2;
	hopf_link->first_crossing_in_components[0] = hopf_crossing_one;
	hopf_link->first_crossing_in_components[1] = hopf_crossing_one;

	/*struct link* T_7_4_knot = PD_to_algorithm_knot(&T_7_4_PD);
	struct laurent_polynomial* test_polynomial_T_7_4 = jones_polynomial(T_7_4_knot);
	print_polynomial(test_polynomial_T_7_4, 'q');
	delete_polynomial(&test_polynomial_T_7_4);
	return 0;*/

	/*struct link* eleven_42_knot = PD_to_algorithm_knot(&eleven_42_PD);
	struct laurent_polynomial* test_polynomial_eleven_42 = jones_polynomial(eleven_42_knot);
	print_polynomial(test_polynomial_eleven_42, 'q');
	delete_polynomial(&test_polynomial_eleven_42);
	return 0;*/

	/*struct link* hopf_link_copy = copy_link(hopf_link);
	smooth_crossing(hopf_link_copy, hopf_link_copy->first_crossing_in_components[0], 0);
	print_link(hopf_link_copy, TRUE);*/

	//print_polynomial(jones_polynomial(hopf_link), 'q');

	long start_time = clock();
	for (int i = 0; i < 10000; i++) {
		struct link* nine_43_knot = PD_to_algorithm_knot(&nine_43_PD);
		struct laurent_polynomial* test_polynomial_nine_43 = jones_polynomial(nine_43_knot);
		delete_polynomial(&test_polynomial_nine_43);
	}
	printf("Time taken: %.2f seconds\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
	//print_polynomial(test_polynomial_nine_43, 'q');
	//delete_polynomial(&test_polynomial_nine_43);
	//return 0;

	start_time = clock();
	for (int i = 0; i < 10000; i++) {
		struct link* eight_21_knot = PD_to_algorithm_knot(&eight_21_PD);
		struct laurent_polynomial* test_polynomial_eight_21 = jones_polynomial(eight_21_knot);
		delete_polynomial(&test_polynomial_eight_21);
	}
	printf("Time taken: %.2f seconds\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
	//print_polynomial(test_polynomial_eight_21, 'q');
	//delete_polynomial(&test_polynomial_eight_21);

	start_time = clock();
	for (int i = 0; i < 10000; i++) {
		struct link* eleven_42_knot = PD_to_algorithm_knot(&eleven_42_PD);
		struct laurent_polynomial* test_polynomial_eleven_42 = jones_polynomial(eleven_42_knot);
		delete_polynomial(&test_polynomial_eleven_42);
	}
	printf("Time taken: %.2f seconds\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
	//print_polynomial(test_polynomial_eleven_42, 'q');
	//delete_polynomial(&test_polynomial_eleven_42);

	start_time = clock();
	for (int i = 0; i < 10000; i++) {
		struct link* T_7_4_knot = PD_to_algorithm_knot(&T_7_4_PD);
		struct laurent_polynomial* test_polynomial_T_7_4 = jones_polynomial(T_7_4_knot);
		delete_polynomial(&test_polynomial_T_7_4);
	}
	printf("Time taken: %.2f seconds\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
	//print_polynomial(test_polynomial_T_7_4, 'q');
	//delete_polynomial(&test_polynomial_T_7_4);

	return 0;

	/*struct link* figure_eight_knot = PD_to_algorithm_knot(&figure_eight_PD);
	print_link(figure_eight_knot, TRUE);
	struct laurent_polynomial* test_polynomial_figure_eight = jones_polynomial(figure_eight_knot);
	print_polynomial(test_polynomial_figure_eight, 'q');
	delete_polynomial(&test_polynomial_figure_eight);
	return 0;*/

	/*struct link* six_three_knot = PD_to_algorithm_knot(&six_three_PD);
	struct laurent_polynomial* test_polynomial_six_three = jones_polynomial(six_three_knot);
	print_polynomial(test_polynomial_six_three, 'q');
	delete_polynomial(&test_polynomial_six_three);*/

	//print_link(trefoil, TRUE);
	/*struct laurent_polynomial* test_polynomial = jones_polynomial(trefoil);
	print_polynomial(test_polynomial, 'q');
	delete_polynomial(&test_polynomial);*/

	return 0;
}