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
 ******************************************************************************
 *  Attempt of a proof of concept of computing the Jones' polynomial from     *
 *  the Gauss code of a knot.                                                 *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/10/31                                                        *
 ******************************************************************************/

/*  All of the tools are found here.                                          */
#include "kauffman.h"

/*  Several knots are provided here via signed Gauss code.                    */
#include "knot_data.h"

/*  Test of the Jones polynomial algorithm.                                   */
int main(void)
{
    /*  Convert the string to a knot.                                         */
    struct knot K = knot_from_gauss_code(FIGURE_EIGHT);

    /*  Compute the Jones polynomial. This is exponential in the number of    *
     *  crossings. For a very large input this will take a while. For a small *
     *  input like the figure-eight its instant.                              */
    struct laurent_polynomial out = normalized_jones(&K);

    /*  And print the result to the screen.                                   */
    print_poly(&out);

    return 0;
}
/*  End of main.                                                              */
