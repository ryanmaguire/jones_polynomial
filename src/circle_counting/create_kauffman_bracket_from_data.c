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

/*  malloc found here. Coefficients array is dynamically allocated.           */
#include <stdlib.h>

/*  All typedef's and function prototypes are provided here.                  */
#include "kauffman.h"

/******************************************************************************
 *  Function:                                                                 *
 *      kauffman_bracket_from_data                                            *
 *  Purpose:                                                                  *
 *      Creates a polynomial from a given data set.                           *
 *  Arguments:                                                                *
 *      data (const signed int *):                                            *
 *          The coefficients array for the polynomial.                        *
 *  Outputs:                                                                  *
 *      P (struct laurent_polynomial):                                        *
 *          The Laurent polynomial with coefficients given by the input data  *
 *          array. The lowest degree is set to the least element with a       *
 *          non-zero entry, and the highest degree is set to the largest      *
 *          element with a non-zero entry.                                    *
 ******************************************************************************/
struct laurent_polynomial
kauffman_bracket_from_data(const signed int *data)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    unsigned int n_elements, shift, n;

    /*  Struct for the output Laurent polynomial.                             */
    struct laurent_polynomial P;

    /*  We'll compute the lowest and highest degrees of the polynomial by     *
     *  searching for the least and greatest entries with non-zero elements,  *
     *  respectively. Start by setting these values to the extrema.           */
    P.lowest_degree = MIN_DEGREE;
    P.highest_degree = MAX_DEGREE;

    /*  A valid Kauffman bracket polynomial will not be zero so we can        *
     *  perform the following search without fear of infinite loops.          */

    /*  Search for the first entry that is not zero.                          */
    while (data[P.lowest_degree + DEGREE_SHIFT] == 0)
        P.lowest_degree++;

    /*  Perform a similar search to find the last non-zero entry.             */
    while (data[P.highest_degree + DEGREE_SHIFT] == 0)
        P.highest_degree--;

    /*  The total number of elements can be computed from the lowest and      *
     *  highest degrees of the polynomial.                                    */
    n_elements = (unsigned int)(P.highest_degree - P.lowest_degree + 1);

    /*  The shift factor for copying the data into the polynomial.            */
    shift = (unsigned int)(DEGREE_SHIFT + P.lowest_degree);

    /*  Allocate memory for the coefficient array of the polynomial.          */
    P.coeffs = malloc(sizeof(*P.coeffs) * n_elements);

    /*  Check if malloc failed. It returns NULL on failure.                   */
    if (!P.coeffs)
    {
        /*  Create an "empty" polynomial if malloc did indeed fail.           */
        P.coeffs = NULL;
        P.lowest_degree = 0;
        P.highest_degree = 0;
        return P;
    }

    /*  Loop through the entries and copy them to the polynomial.             */
    for (n = 0U; n < n_elements; ++n)
        P.coeffs[n] = data[n + shift];

    return P;
}
/*  End of kauffman_bracket_from_data.                                        */
