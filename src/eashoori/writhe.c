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

/*Now, we must carry out the skein template algorithm for t and use Lagrange interpolation on the result. THE ABOVE DEFINITELY WORKS. I AM SURE OF THIS.
Jones_Partial has some error in it. I need to rectify it...*/
int writhe(struct Gauss k1) { //This one works.
    int counter, counter1, result;
    result = 0; 
    for (counter = 0; counter < k1.components; counter++) {// Iterate over components
        for (counter1 = 0; counter1 < k1.sizecomp[counter]; counter1++) {//Iterate over crossings in each component
            result += k1.matrix[counter][counter1][2]; //Add sign of crossing
        }
    }
    return result / 2; //CROSSINGS HAPPEN TWICE!!
}
