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

/*  All typedef's and function protocols are provided here.                   */
#include "kauffman.h"

/******************************************************************************
 *  Function:                                                                 *
 *      add_normalized_kauffman_summand                                       *
 *  Purpose:                                                                  *
 *      Same as add_kauffman_summand but normalizes the computation by        *
 *      removing a factor of (q + q^{-1}). Every complete resolution of a     *
 *      knot or link will have at least one cycle, meaning (q + q^{-1}) will  *
 *      divide the Kauffman bracket. The normalized Kauffman bracket removes  *
 *      this factor so that the bracket of the standard unknot is 1. We have: *
 *                                                                            *
 *                  n                                                         *
 *                 2 - 1                                                      *
 *                 -----                                                      *
 *                 \           w(k)       -1  c(k) - 1                        *
 *          [L] =  /       (-q)     (q + q  )                                 *
 *                 -----                                                      *
 *                 k = 0                                                      *
 *                                                                            *
 *      where [L] denotes the Kauffman bracket of L. The only difference      *
 *      from the function add_kauffman_summand is that (q+q^{-1})^{c(k)}      *
 *      has been replaced with (q+q^{-1})^{c(k)-1}.                           *
 *  Arguments:                                                                *
 *      cycles (unsigned int):                                                *
 *          The number of cycles corresponding to a complete smoothing.       *
 *      weight (unsigned int):                                                *
 *          The Hamming weight of the integer representing the smoothing.     *
 *      degree_shift (unsigned int):                                          *
 *          A shift factor for the degree. The zeroth element of the input    *
 *          array should correspond to the coefficient of the lowest degree   *
 *          term in the polynomial. Since this is a Laurent polynomial this   *
 *          term can be negative, positive, or zero. The degree_shift term is *
 *          used by the caller to ensure the entries of the expression        *
 *          (-q)^{w(k)} (q + q^{-1})^{c(k)} are added to the correct elements *
 *          of the input array.                                               *
 *      coeffs_array (signed int *):                                          *
 *          An array of coefficients for the Laurent polynomial of [L]. It is *
 *          assumed that this has been allocated sufficient memory and that   *
 *          at the start of the computation (i.e., before the first calling   *
 *          of this function), that the coefficients have been initialized to *
 *          zero. Bounds on the size of the Kauffman bracket mean that no     *
 *          more with 3*WIDTH + 2 elements are needed for the array, where    *
 *          WIDTH is the width of unsigned int (usually 32-bits).             *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Compute cycles - 1 and pass all arguments to add_kauffman_summand.    *
 *  Called Functions:                                                         *
 *      add_kauffman_summand                                                  *
 ******************************************************************************/
void
add_normalized_kauffman_summand(unsigned int cycles,
                                unsigned int weight,
                                unsigned int degree_shift,
                                signed int *coeffs_array)
{
    /*  The reduction is computed by reducing the number of cycles by 1.      */
    const unsigned int reduced = cycles - 1U;

    /*  Pass the new parameters to the old function to finish.                */
    add_kauffman_summand(reduced, weight, degree_shift, coeffs_array);
}
/*  End of add_normalized_kauffman_summand.                                   */
