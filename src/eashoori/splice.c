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

struct Gauss splice(struct Gauss k1) {
    struct Gauss modknot;
    modknot.crossings = k1.crossings - 1; //splicing reduces crossings by 1
    modknot.splices = k1.splices + 1;
    int counter, counter1, counter2, counter3;
    int len1, len2;
    counter3 = 0;
    int cases = isitsmaller(k1); //0 if crossing is a real crossing in a knot, 1 if it is some intersection between two knots....
    int mat1, col1, mat2, col2;
    for (counter = 0; counter < k1.components; counter++) { //iterate through components
        if (counter3 == 2) {// If we've found both instances, we're done!
            break;
        }
        for (counter1 = 0; counter1 < k1.sizecomp[counter]; counter1++) { //loop through the columns of each matrix
            if (counter3 == 2) {// If we've found both instances, we're done!
                break;
            }
            if (k1.matrix[counter][counter1][0] == k1.startcross) {//check if it is the right crossing
                if (counter3 == 0) {// we do not want to search for this again, so we do our search here.
                    mat1 = counter;// set mat1 to the first matrix where I find it.
                    col1 = counter1;// set col1 to the first column where I find it.
                }
                if (counter3 == 1) {
                    mat2 = counter; //set mat2 to the second matrix where I find it
                    col2 = counter1; //set col2 to the second column where I find it.
                }
                counter3++; //increment counter3 so that it is one the second time that I find k.
            }
        }
    }
    len1 = k1.sizecomp[mat1];
    len2 = k1.sizecomp[mat2];
    if (cases == 0) {
        modknot.components = k1.components + 1;//if both are in the same knot, we add one to components, but if they are in different knots, we subtract 1.
    }
    if (cases == 1) {
        modknot.components = k1.components - 1;//if both are in the same knot, we add one to components, but if they are in different knots, we subtract 1.
    }
    modknot.sizecomp = (int*)malloc(modknot.components * sizeof(int));//allocate memory to modknot.sizecomp
    if (cases == 1) {//if it is in 2 knots, merge the two knots!
        counter = 0; //initialize counters to zero
        counter1 = 0; //initialize counters to zero
        while (counter < modknot.components) {//iterate through components
            if (counter == mat2) {
                counter1++; //skip it!
            }
            modknot.sizecomp[counter] = k1.sizecomp[counter1];// copy
            if (counter == mat1) {//special case. Want to add their sizes
                modknot.sizecomp[counter] += k1.sizecomp[mat2];// should be the size of the sum.
            }
            counter++;//increment both counters.
            counter1++;
        }
    }
    if (cases == 0) {//Increments number of things by one. Must add new knot to link. I will add it to the end.
        counter = 0; //initialize counter2 to zero
        while (counter < modknot.components) {//iterate through components
            if (counter == mat1) {//special case.
                modknot.sizecomp[counter] = col2 - col1;
            }
            if (counter != mat1 && counter != modknot.components - 1) {
                modknot.sizecomp[counter] = k1.sizecomp[counter];
            }
            if (counter == modknot.components - 1) {
                modknot.sizecomp[counter] = k1.sizecomp[mat1] + col1 - col2;//length of mat1 minus stuff
            }
            counter++;//increment counter
        }
    }
    modknot.matrix = (int***)malloc(modknot.components * sizeof(int**));//allocate memory to modknot.matrix
    for (counter1 = 0; counter1 < modknot.components; counter1++) {
        modknot.matrix[counter1] = (int**)malloc(modknot.sizecomp[counter1] * sizeof(int*));//allocate memory to each matrix within modknot.matrix
        for (counter2 = 0; counter2 < modknot.sizecomp[counter1]; counter2++) {
            modknot.matrix[counter1][counter2] = (int*)malloc(3 * sizeof(int));//allocate memory to each column within the matrix
        }
    }
    if (cases == 1) {//hijack the same logic used in sizecomp to make the new matrix.
        counter = 0; //initialize counters to zero
        counter1 = 0; //initialize counters to zero
        while (counter < modknot.components) {//iterate through components
            if (counter == mat2) {//skip over second matrix. Will keep everything in the same place. Only deletes the matrix.
                counter1++; //skip it!
            }
            if (counter == mat1) {//special case. Want to add their sizes AxB, CxD->ADBC.
                for (counter2 = 0; counter2 < col1; counter2++) {
                    for (counter3 = 0; counter3 < 3; counter3++) {
                        modknot.matrix[mat1][counter2][counter3] = k1.matrix[mat1][counter2][counter3];
                    }
                }
                modknot.matrix[mat1][col1][0] = -1;//give nonsensical value for crossing number so I can skip over it later
                modknot.matrix[mat1][col1][1] = k1.matrix[mat1][col1][1];
                modknot.matrix[mat1][col1][2] = k1.matrix[mat1][col1][2];
                for (counter2 = 0; counter2 < len2 - col2 - 1; counter2++) {
                    for (counter3 = 0; counter3 < 3; counter3++) {
                        modknot.matrix[mat1][counter2 + col1 + 1][counter3] = k1.matrix[mat2][counter2 + col2 + 1][counter3];
                    }
                }
                for (counter2 = 0; counter2 < len1 - col1 - 1; counter2++) {
                    for (counter3 = 0; counter3 < 3; counter3++) {
                        modknot.matrix[mat1][counter2 + col1 + len2 - col2][counter3] = k1.matrix[mat1][counter2 + col1 + 1][counter3];
                    }
                }
                modknot.matrix[mat1][len1 + len2 - col2 - 1][0] = -1;//give nonsensical value for crossing number so I can skip over it later
                modknot.matrix[mat1][len1 + len2 - col2 - 1][1] = k1.matrix[mat2][col2][1];
                modknot.matrix[mat1][len1 + len2 - col2 - 1][2] = k1.matrix[mat2][col2][2];
                for (counter2 = 0; counter2 < col2; counter2++) {
                    for (counter3 = 0; counter3 < 3; counter3++) {
                        modknot.matrix[mat1][counter2 + len1 + len2 - col2][counter3] = k1.matrix[mat2][counter2][counter3];
                    }
                }
            }
            if (counter != mat1 && counter != mat2) {//last case
                for (counter2 = 0; counter2 < modknot.sizecomp[counter1]; counter2++) {//loop
                    for (counter3 = 0; counter3 < 3; counter3++) {//loop
                        modknot.matrix[counter][counter2][counter3] = k1.matrix[counter1][counter2][counter3]; //Set these two equal.
                    }
                }
            }
            counter++;//increment both counters.
            counter1++;
        }
    }
    if (cases == 0) {//hijacks same logic to make the new matrix
        counter = 0; //initialize counters to zero
        while (counter < modknot.components) {//iterate through components
            if (counter == mat1) {//special case. Want to add their sizes AxBxC->xB,AxC
                for (counter2 = 0; counter2 < col2 - col1; counter2++) {
                    for (counter3 = 0; counter3 < 3; counter3++) {
                        modknot.matrix[mat1][counter2][counter3] = k1.matrix[mat1][counter2 + col1][counter3];
                    }
                }
            }
            if (counter == modknot.components - 1) {
                for (counter2 = 0; counter2 < col1; counter2++) {
                    for (counter3 = 0; counter3 < 3; counter3++) {
                        modknot.matrix[counter][counter2][counter3] = k1.matrix[mat1][counter2][counter3];
                    }
                }
                for (counter2 = 0; counter2 < k1.sizecomp[mat1] - col2; counter2++) {
                    for (counter3 = 0; counter3 < 3; counter3++) {
                        modknot.matrix[counter][counter2 + col1][counter3] = k1.matrix[mat1][counter2 + col2][counter3];
                    }
                }
            }
            if (counter != mat1 && counter != modknot.components - 1) {//last case
                for (counter2 = 0; counter2 < modknot.sizecomp[counter]; counter2++) {//loop
                    for (counter3 = 0; counter3 < 3; counter3++) {//loop
                        modknot.matrix[counter][counter2][counter3] = k1.matrix[counter][counter2][counter3]; //Set these two equal.
                    }
                }
            }
            counter++;//increment both counters.
        }
    }
    for (counter = 0; counter < modknot.components; counter++) {// loop through components
        for (counter1 = 0; counter1 < modknot.sizecomp[counter]; counter1++) {//loop through crossings
            if (modknot.matrix[counter][counter1][0] == k1.startcross) {//if we have found our crossing
                modknot.matrix[counter][counter1][0] = -1;//kill it. Set it to -1. We will never care about it again!
                if (modknot.matrix[counter][counter1][1] == k1.ovorun) { //if it is the right instance
                    mat1 = counter; //set mat1 and col1 accordingly
                    col1 = counter1;
                }
            }
        }
    }
    int modcount, modcount1, modcount2;
    int found = 0;
    for (counter = 1; counter < modknot.components + 1; counter++) {
        if (found == 1) {
            break;
        }
        modcount = (counter + mat1) % modknot.components;
        for (counter1 = 1; counter1 < modknot.sizecomp[modcount] + 1; counter1++) {
            if (found == 1) {
                break;
            }
            modcount1 = (counter1 + col1) % modknot.sizecomp[modcount];
            for (counter2 = 0; counter2 < 3; counter2++) {
                if (found == 1) {
                    break;
                }
                if (modknot.matrix[modcount][modcount1][0] != -1) {
                    modknot.startcross = modknot.matrix[modcount][modcount1][0];
                    modknot.ovorun = modknot.matrix[modcount][modcount1][1];
                    modknot.sign = modknot.matrix[modcount][modcount1][2];
                    found = 1;
                }
            }
        }
    }
    return modknot;//return modified knot
}
