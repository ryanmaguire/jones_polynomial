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

/*  All of the tools are found here.                                          */
#include "kauffman.h"
#include "knot_data.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/*  Test of the Jones polynomial algorithm.                                   */
int main(void)
{
    // struct crossing crossings[2] = {{{1, 0, 2, 3}}, {{2, 1, 3, 0}}};
    int torus_knot_data[][4] = { {19,29,20,28}, {10,30,11,29}, {1,31,2,30}, {40,32,41,31}, {11,21,12,20}, {2,22,3,21}, {41,23,42,22}, {32,24,33,23}, {3,13,4,12}, {42,14,43,13}, {33,15,34,14}, {24,16,25,15}, {43,5,44,4}, {34,6,35,5}, {25,7,26,6}, {16,8,17,7}, {35,45,36,44}, {26,46,27,45}, {17,47,18,46}, {8,48,9,47}, {27,37,28,36}, {18,38,19,37}, {9,39,10,38}, {48,40,1,39} };
    struct crossing* knot_crossings = (struct crossing*)malloc(25 * sizeof(struct crossing));
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 4; j++) {1
            knot_crossings[i].dat[j] = torus_knot_data[i][j];
        }
    }
    struct knot K = {24, knot_crossings};
    /*  Compute the Jones polynomial. This is exponential in the number of    *
     *  crossings. For a very large input this will take a while. For a small *
     *  input like the figure-eight its instant.                              */
    clock_t time;
    time = clock();
    struct laurent_polynomial out = normalized_jones(&K);
    time = clock() - time;
    printf("time taken in seconds: %f\n", (float)time / (float)CLOCKS_PER_SEC);
    /*  And print the result to the screen.                                   */
    print_poly(&out);
    return 0;
}
/*  End of main.                                                              */
