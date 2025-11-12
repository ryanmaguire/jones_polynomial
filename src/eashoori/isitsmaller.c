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

int isitsmaller(struct Gauss k1) {
    int counter, counter1, counter2;
    int cases = 1; //zero if crossing is a real crossing in a knot, one if it is some intersection between two knots
    int mat1, col1, mat2, col2;
    for (counter = 0; counter < k1.components; counter++) { //iterate through components
        counter2 = 0; //initialize counter2 to zero every time I get here.
        for (counter1 = 0; counter1 < k1.sizecomp[counter]; counter1++) { //loop through the columns of each matrix
            if (k1.matrix[counter][counter1][0] == k1.startcross) {//check if it is the right crossing
                counter2++;//if it is, increment counter 2.
            }
            if (counter2 == 2) {//if counter2 has been incremented twice, it means that the crossing is not an interaction between two knots
                cases = 0;//set cases to zero.
                break;
            }
        }
        if (counter2 == 2) {//if counter2 has been incremented twice-> not an interaction between two knots
            cases = 0;//thus, we can set cases to zero.
            break;
        }
    }
    return cases;
}
