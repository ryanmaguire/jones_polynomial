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

#include "skein_template.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    struct Gauss trefoil;
    trefoil.crossings = 3;
    trefoil.components = 1;
    trefoil.splices = 0;
    trefoil.sizecomp = (int*)malloc(sizeof(int));
    trefoil.sizecomp[0] = 6;
    trefoil.matrix = (int***)malloc(sizeof(int**));
    trefoil.matrix[0] = (int**)malloc(6 * sizeof(int*));
    for (int i = 0; i < 6; i++) {
        trefoil.matrix[0][i] = (int*)malloc(3 * sizeof(int));
    }
    int data[6][3] = {
        {1, OVER, 1},  // Crossing one, Over, Positive
        {2, UNDER, 1},  // Crossing two, Under, Positive
        {3, OVER, 1},  // Crossing three, Over, Positive
        {1, UNDER, 1},  // Crossing one again, Under, Positive
        {2, OVER, 1},  // Crossing two again, Over, Positive
        {3, UNDER, 1}   // Crossing three again, Under, Positive
    };
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            trefoil.matrix[0][i][j] = data[i][j];
        }
    }
    trefoil.startcross = 1;
    trefoil.ovorun = OVER;
    trefoil.sign = 1;
    //printing jones polynomial of the trefoil knot, which is -q^8 + q^6 + q^2, when the all degrees are doubled
    printf("Jones polynomial of the trefoil knot: ");
    struct laurent_polynomial jones_trefoil = JONES(trefoil);
    print_polynomial(&jones_trefoil, 'q');
    for (int i = 0; i < 6; i++) {
        free(trefoil.matrix[0][i]);
    }
    free(trefoil.matrix[0]);
    free(trefoil.matrix);
    free(trefoil.sizecomp);
    return 0;
}
