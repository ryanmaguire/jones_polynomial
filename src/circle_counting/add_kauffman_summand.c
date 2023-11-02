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

/*  The powers (q + q^{-1})^n for n = 0, 1, ..., 33 are provided here.        */
#include "q_plus_q_inverse_powers.h"

/******************************************************************************
 *  Function:                                                                 *
 *      add_kauffman_summand                                                  *
 *  Purpose:                                                                  *
 *      If a knot or link L has been completely smoothed by some resolution   *
 *      of the crossings, the result is a collection of cycles. The           *
 *      contribution of this resolution is (-q)^{w(k)} (q + q^{-1})^{c(k)}    *
 *      where w(k) is the Hamming weight of the resolution k, the number of   *
 *      1's in the binary expansion of k, and c(k) is the number of cycles.   *
 *      The total formula for the Kauffman bracket is:                        *
 *                                                                            *
 *                  n                                                         *
 *                 2 - 1                                                      *
 *                 -----                                                      *
 *                 \           w(k)       -1  c(k)                            *
 *          [L] =  /       (-q)     (q + q  )                                 *
 *                 -----                                                      *
 *                 k = 0                                                      *
 *                                                                            *
 *      where [L] denotes the Kauffman bracket of L. Given the weight, number *
 *      of cycles, a possible "degree-shift", and an array of coefficients    *
 *      corresponding to [L] (being computed in-progress), add the Laurent    *
 *      polynomial (-q)^{w(k)} (q + q^{-1})^{c(k)} to the array.              *
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
 *      The number of terms in (q + q^{-1})^n is 2n + 1. Every other term is  *
 *      zero, so we can perform the sum in increments of two. If the weight   *
 *      is odd we need to subtract (q + q^{-1})^n instead of add. We loop     *
 *      through all of the coefficients and perform the arithmetic.           *
 ******************************************************************************/
void
add_kauffman_summand(unsigned int cycles,
                     unsigned int weight,
                     unsigned int degree_shift,
                     signed int *coeffs_array)
{
    /*  Integer for indexing the sum.                                         */
    unsigned int n;

    /*  The shift factor to make the entries of (-q)^{w(k)}(q+q^{-1})^{c(k)}  *
     *  align with the correct entries of the input array. The smallest       *
     *  degree element of (-q)^{w(k)}(q+q^{-1})^{c(k)} has degree w(k) - c(k) *
     *  which is given by -cycles + weight. The degree_shift is added to this *
     *  factor to make everything align properly.                             */
    const unsigned int shift = degree_shift - cycles + weight;

    /*  The number of terms in the Laurent polynomial (q+q^{-1})^{c(k)}.      */
    const unsigned int number_of_terms = 2U*cycles + 1U;

    /*  Get a pointer to the coefficient array of (q+q^{-1})^{c(k)}.          */
    const int * const coeffs = q_qinv_powers[cycles];

    /*  If the weight is odd we subtract the elements instead of add.         */
    if (weight & 1U)
    {
        /*  Loop through the elements of the array and subtract. Note that    *
         *  every other elements is zero and so we can skip these. That is,   *
         *  we may increment our dummy index by 2 every time, instead of 1.   */
        for (n = 0; n < number_of_terms; n += 2)
            coeffs_array[n + shift] -= coeffs[n];
    }

    /*  For even weights we add the polynomial to our array.                  */
    else
    {
        /*  Add the terms with the same skip-by-two step as before.           */
        for (n = 0; n < number_of_terms; n += 2)
            coeffs_array[n + shift] += coeffs[n];
    }
}
/*  End of add_kauffman_summand.                                              */
