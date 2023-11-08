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

/*  All typedef's and function prototypes are provided here.                  */
#include "kauffman.h"

/******************************************************************************
 *  Functions:                                                                *
 *      normalized_jones                                                      *
 *  Purpose:                                                                  *
 *      Computes the normalized Jones polynomial.                             *
 *  Arguments:                                                                *
 *      K (const struct knot *):                                              *
 *          A knot, represented by extended Gauss code.                       *
 *  Output:                                                                   *
 *      J_K (struct laurent_polynomial):                                      *
 *          The normalized Jones polynomial of K.                             *
 *  Method:                                                                   *
 *      Compute the Kauffman bracket [K] and then normalize this by the       *
 *      writhe. That is:                                                      *
 *                                                                            *
 *          J(K)(q) = (-q)^{n_{+} - 2n_{-}} [K](q) / (q + q^{-1})             *
 *                                                                            *
 *      where n_{+} is the number of positive crossings in K and n_{-} is the *
 *      number of negative crossings.                                         *
 ******************************************************************************/
struct laurent_polynomial normalized_jones(const struct knot *K)
{
    struct laurent_polynomial out = normalized_kauffman_bracket(K);
    jones_normalization(K, &out);
    return out;
}
/*  End of normalized_jones.                                                  */
