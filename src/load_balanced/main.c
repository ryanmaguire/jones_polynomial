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
	char knot_DT_code[] = "ipDGomClaKNhfJeb";
	struct DT_knot* knot_DT = make_DT_knot(knot_DT_code);
	struct PD_knot* knot_PD_code = DT_to_PD(knot_DT);

	long start_time = clock();
	for (int i = 0; i < 10000; i++)
	{
		struct link* knot = PD_to_algorithm_knot(knot_PD_code);
		struct laurent_polynomial* knot_jones = jones_polynomial(knot);
		delete_polynomial(&knot_jones);
	}

	printf("Time taken: %.2f seconds\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
	print_polynomial(jones_polynomial(PD_to_algorithm_knot(knot_PD_code)), 'q');

	return 0;
}