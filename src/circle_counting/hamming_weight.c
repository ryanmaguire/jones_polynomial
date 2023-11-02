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
#include "kauffman.h"

/*  Four algorithms provided, two of which are compiler-specific.             */
#define KR_ALG 0
#define NAIVE_ALG 1
#define GCC_ALG 2
#define MSVC_ALG 3

/*  The choice of algorithm. If not specified by user, try to use fastest.    */
#ifndef ALG

/*  Clang and GCC have the __builtin_popcount function, check for this.       */
#if defined(__GNUC__) || defined(__clang__)
#define ALG 2

/*  Microsoft provides intrin.h which also has a popcount function.           */
#elif defined(_MSC_VER)
#define ALG 3

/*  Otherwise revert to the naive algorithm.                                  */
#else
#define ALG 1

#endif
/*  End of GCC vs. clang vs. MSVC vs. portable.                               */

#endif
/*  End of #ifndef ALG.                                                       */

/*  The algorithm found in K&R "The C Programming Language."                  */
#if ALG == KR_ALG

unsigned int hamming_weight(unsigned int val)
{
    unsigned int count = 0U;
    for (; val; ++count)
        val &= val - 1;

    return count;
}

/*  The naive "by-hand" algorithm, counting the individual bits.              */
#elif ALG == NAIVE_ALG

/*  Basic algorithm for computing the Hamming weight of an unsigned integer   *
 *  that is sizeof(unsigned int) * CHAR_BIT bits long. There are faster       *
 *  methods, but this does not assume 32-bit int and is more portable.        */
unsigned int hamming_weight(unsigned int val)
{
    unsigned int result = 0U;

    /*  Loop over the bits of the input.                                      */
    while(val != 0U)
    {
        /*  val & 1U returns 0 if the last bit is zero, and 1 if the last     *
         *  bit is one. Summing over these gives us the Hamming weight.       */
        result += val & 1U;

        /*  Move the input 1 bit to the right.                                */
        val = val >> 1U;
    }

    return result;
}
/*  End of hamming_weight.                                                    */

/*  GCC and others (LLVM's clang) provide a built-in popcount function that   *
 *  can compute the Hamming weight much faster than the portable code.        */
#elif ALG == GCC_ALG

unsigned int hamming_weight(unsigned int val)
{
    return __builtin_popcount(val);
}

/*  MSVC equivalent of the GCC __builtin_popcount function.                   */
#elif ALG == MSVC_ALG

#include <intrin.h>

unsigned int hamming_weight(unsigned int val)
{
    return __popcnt(val);
}

/*  The user chose an illegal value for the algorithm.                        */
#else
#error "Illegal ALG value."
#endif
