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

/*  Get the road number from a crossing from the sign, type, and direction.   */
unsigned char
get_road_number(const struct knot *K, unsigned int index, unsigned char dir)
{
    /**************************************************************************
     *  We have three variables that take on values of zero and one, the sign *
     *  and type of the crossing, and the direction. These correspond to the  *
     *  eight possible ways of entering the crossing.  We make this algebraic *
     *  by solving for the values a, b, c, and d such that:                   *
     *                                                                        *
     *      road_number = a*sign*type + b*sign + c*type + d                   *
     *                                                                        *
     *  We use the following image to solve for the four parameters.          *
     *                                                                        *
     *       3          2         3          2                                *
     *      \  \      /  /       \  \      /  /                               *
     *       \  \    /  /         \  \    /  /                                *
     *        \  \  /  /           \  \  /  /                                 *
     *         \  \/  /             \  \/  /                                  *
     *          \  \ /               \ /  /                                   *
     *           \  \     -           /  /     +                              *
     *          / \  \               /  / \                                   *
     *         /  /\  \             /  /\  \                                  *
     *        /  /  \  \           /  /  \  \                                 *
     *       /  /    \  \         /  /    \  \                                *
     *      /  /      \  \       /  /      \  \                               *
     *       0          1         0          1                                *
     *                                                                        *
     *  This creates the following table:                                     *
     *                                                                        *
     *      s | t | dir | in                                                  *
     *      ----------------                                                  *
     *      + | O | --> | 0                                                   *
     *      + | O | <-- | 2                                                   *
     *      + | U | --> | 1                                                   *
     *      + | U | <-- | 3                                                   *
     *      - | O | --> | 1                                                   *
     *      - | O | <-- | 3                                                   *
     *      - | U | --> | 0                                                   *
     *      - | U | <-- | 2                                                   *
     *                                                                        *
     *  We note that the results for the positive and negative crossings      *
     *  mirror each other. We use all of this to solve for a, b, c, and d,    *
     *  noting that we have defined the following values in kauffman.h:       *
     *                                                                        *
     *      OVER_CROSSING     = 0                                             *
     *      UNDER_CROSSING    = 1                                             *
     *      POSITIVE_CROSSING = 0                                             *
     *      NEGATIVE_CROSSING = 1                                             *
     *      FORWARD           = 0                                             *
     *      BACKWARD          = 1                                             *
     *                                                                        *
     *  Which yields a = -2, b = 1, c = 1, and d = 2*dir. We compute this.    */
    const unsigned char b = K->sign[index];
    const unsigned char c = K->type[index];
    const unsigned char a = (b * c) << 1U;
    const unsigned char d = dir << 1U;
    return b + c + d - a;
}
/*  End of get_road_number.                                                   */
