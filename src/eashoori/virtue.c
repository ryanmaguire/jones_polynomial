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

struct Gauss virtue(struct Gauss k1) {//we make crossing k1.startcross virtual by setting its number to -1
    int counter, counter1, counter2, counter3 = 0; //4 counters
    int mat1, col1;
    int found = 0;
    struct Gauss modknot; // modified knot to be returned
    modknot.splices = k1.splices;
    modknot.crossings = k1.crossings - 1; //We treat this as if we have gotten rid of the crossing. Bye bye!
    modknot.components = k1.components;//components should be the same
    modknot.sizecomp = (int*)malloc(modknot.components * sizeof(int));//allocate memory to modknot.sizecomp
    for (int i = 0; i < modknot.components; i++) { //iterate over components
        modknot.sizecomp[i] = k1.sizecomp[i];//copy original knot into modknot
    }
    modknot.matrix = (int***)malloc(modknot.components * sizeof(int**)); //allocate memory
    for (int i = 0; i < modknot.components; i++) {
        modknot.matrix[i] = (int**)malloc(modknot.sizecomp[i] * sizeof(int*));
        for (int j = 0; j < modknot.sizecomp[i]; j++) {
            modknot.matrix[i][j] = (int*)malloc(3 * sizeof(int));
        }
    }
    for (int i = 0; i < modknot.components; i++) {
        for (int j = 0; j < modknot.sizecomp[i]; j++) {
            for (int k = 0; k < 3; k++) {
                modknot.matrix[i][j][k] = k1.matrix[i][j][k]; //copy original knot into modknot
            }

            if (k1.matrix[i][j][0] == k1.startcross) {//If it's the starting crossing
                modknot.matrix[i][j][0] = -1; // virtualize
                if (k1.matrix[i][j][1] == k1.ovorun) {
                    mat1 = i;//Store position of the crossing
                    col1 = j;
                }
            }
        }
    }
    int modcount, modcount1;
    for (counter = 0; counter < modknot.components; counter++) {//iterate over components
        if (found == 1) {
            break; //If I've found it, I should break out of the loop
        }
        modcount = (counter + mat1) % modknot.components; //shifted version of counter so that the current component is mat1
        for (counter1 = 0; counter1 < modknot.sizecomp[modcount]; counter1++) {// iterate over crossings of the components
            if (found == 1) {
                break; //If I've found the crossing, break
            }
            modcount1 = (counter1 + col1) % modknot.sizecomp[modcount];
            for (counter2 = 0; counter2 < 3; counter2++) { //Check each component
                if (found == 1) {
                    break;
                }
                if (modknot.matrix[modcount][modcount1][0] != -1) {//if it's not virtued
                    modknot.startcross = modknot.matrix[modcount][modcount1][0];//update startcross to this thing
                    modknot.ovorun = modknot.matrix[modcount][modcount1][1];//update ovorun to next crossing
                    modknot.sign = modknot.matrix[modcount][modcount1][2];//update sign for next crossing
                    found = 1;//IT'S BEEN FOUND!
                }
            }
        }
    }
    return modknot;//Return modknot
}
