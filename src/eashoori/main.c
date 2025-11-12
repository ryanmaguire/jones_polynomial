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
    int trefoil_data[6][3] = {
        {1, OVER, 1},  // Crossing one, Over, Positive
        {2, UNDER, 1},  // Crossing two, Under, Positive
        {3, OVER, 1},  // Crossing three, Over, Positive
        {1, UNDER, 1},  // Crossing one again, Under, Positive
        {2, OVER, 1},  // Crossing two again, Over, Positive
        {3, UNDER, 1}   // Crossing three again, Under, Positive
    };
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            trefoil.matrix[0][i][j] = trefoil_data[i][j];
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

    struct Gauss fig8;
    fig8.crossings = 4;
    fig8.components = 1;
    fig8.splices = 0;
    fig8.sizecomp = (int*)malloc(sizeof(int));
    fig8.sizecomp[0] = 8;
    fig8.matrix = (int***)malloc(sizeof(int**));
    fig8.matrix[0] = (int**)malloc(8 * sizeof(int*));
    for (int i = 0; i < 8; i++) {
        fig8.matrix[0][i] = (int*)malloc(4 * sizeof(int));
    }
    int fig8_data[8][3] = {
        {1, OVER, -1},  // Crossing one, Over, Positive
        {4, UNDER, 1},  // Crossing two, Under, Positive
        {3, OVER, 1},  // Crossing three, Over, Positive
        {1, UNDER, -1},  // Crossing one again, Under, Positive
        {2, OVER, -1},  // Crossing two again, Over, Positive
        {3, UNDER, 1},   // Crossing three again, Under, Positive
        {4, OVER, 1},  // Crossing one, Over, Positive
        {2, UNDER, -1}  // Crossing two, Under, Positive
    };
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            fig8.matrix[0][i][j] = fig8_data[i][j];
        }
    }
    fig8.startcross = 1;
    fig8.ovorun = OVER;
    fig8.sign = 1;
    //printing jones polynomial of the figure 8 knot, which is 1 - q^-2 + q^-4 - q^-6 + q^-8, when the all degrees are doubled
    printf("Jones polynomial of the figure 8 knot: ");
    struct laurent_polynomial jones_fig8 = JONES(fig8);
    print_polynomial(&jones_fig8, 'q');
    for (int i = 0; i < 6; i++) {
        free(fig8.matrix[0][i]);
    }
    free(fig8.matrix[0]);
    free(fig8.matrix);
    free(fig8.sizecomp);

    struct Gauss five2;
    five2.crossings = 5;
    five2.components = 1;
    five2.splices = 0;
    five2.sizecomp = (int*)malloc(sizeof(int));
    five2.sizecomp[0] = 10;
    five2.matrix = (int***)malloc(sizeof(int**));
    five2.matrix[0] = (int**)malloc(10 * sizeof(int*));
    for (int i = 0; i < 10; i++) {
        five2.matrix[0][i] = (int*)malloc(5 * sizeof(int));
    }
    int five2_data[10][3] = {
        {1, UNDER, -1},// Crossing one, Under, Negative
        {3, OVER, -1},// Crossing three, Over, Negative
        {4, UNDER, -1},// Crossing four, Under, Negative
        {5, OVER, -1},// Crossing five, Over, Negative
        {2, UNDER, -1},// Crossing two, Under, Negative
        {1, OVER, -1},// Crossing one, Over, Negative
        {5, UNDER, -1},// Crossing 5, Under, Negative
        {4, OVER, -1},// Crossing four, Over, Negative
        {3, UNDER, -1},// Crossing three, Under, Negative
        {2, OVER, -1}// Crossing two, Over, Negative
    };
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++) {
            five2.matrix[0][i][j] = five2_data[i][j];
        }
    }
    five2.startcross = 1;
    five2.ovorun = OVER;
    five2.sign = 1;
    //printing jones polynomial of the 5_2 knot, which is q^-6 - q^-8 + 2q^-10 - q^-12 + q^-14 - q^-16, when the all degrees are doubled
    printf("Jones polynomial of the 5_2 knot: ");
    struct laurent_polynomial jones_knot = JONES(five2);
    print_polynomial(&jones_knot, 'q');
    for (int i = 0; i < 10; i++) {
        free(five2.matrix[0][i]);
    }
    free(five2.matrix[0]);
    free(five2.matrix);
    free(five2.sizecomp);


    return 0;
}
