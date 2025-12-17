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
#include <stdio.h>

//1008895

int main()
{
	char buffer[256];

	long start_time = clock();

	FILE *fptr;

	// Open a file in read mode
	fptr = fopen("../16n_hyp_jones.txt", "r");

	char *myString;

	int i = 0;
	//1008895
	while (i < 100000 && fgets(buffer, sizeof(buffer), fptr)) {
		myString = strtok(buffer, ",");
		strtok(NULL, ","); // skip the second field (split on commas)

		//printf("Processing knot %d: %s\n", i + 1, myString);

		struct DT_knot* test_DT = make_DT_knot(myString);
		struct PD_knot* test_PD_code = DT_to_PD(test_DT);

		struct link* test_knot = PD_to_algorithm_knot(test_PD_code);
		struct laurent_polynomial* test_jones = jones_polynomial(test_knot);
		delete_polynomial(&test_jones);
		SAFE_FREE(test_DT->DT_code);
		SAFE_FREE(test_DT);
		SAFE_FREE(test_PD_code->crossings);
		SAFE_FREE(test_PD_code);

		i++;
	}

	// Close the file
	fclose(fptr);

	printf("Time taken: %.2f seconds\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
	
	/*char knot_DT_code[] = "dnKiJBlfMpEgOaHc";
	struct DT_knot* knot_DT = make_DT_knot(knot_DT_code);
	struct PD_knot* knot_PD_code = DT_to_PD(knot_DT);
	print_polynomial(jones_polynomial(PD_to_algorithm_knot(knot_PD_code)), 'q');*/

	return 0;
}