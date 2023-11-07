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

/*  Counts the number of cycles in a complete smoothing of a knot.            */
unsigned int
circle_count(const struct knot *K,
             const struct crossing_indices *ind,
             unsigned int resolution)
{
    /*  Declare all necessary variables. C89 requires declarations at the top.*/
    unsigned int number_of_circles, n, road_index, crossing, code_index;
    unsigned char direction, crossing_resolution, road_number;
    enum crossing_sign sign;

    /*  Array for checking off which roads have been visited.                 */
    unsigned char have_visited[4U * MAX_CROSSINGS];

    /*  The direction is stored as an unsigned char. There are two            *
     *  possibilities: forwards and backwards.                                */
    const unsigned char forward = 0x00U;

    /*  The empty knot has zero circles.                                      */
    if (!K)
        return 0U;

    /*  The unknot has 1 circle.                                              */
    if (K->number_of_crossings == 0U)
        return 1U;

    /*  If ind is a NULL pointer, there's nothing that can be done.           */
    if (!ind)
        return 0U;

    for (n = 0U; n < 4U * K->number_of_crossings; ++n)
        have_visited[n] = 0x00U;

    /*  Initialize number_of_circles to zero.                                 */
    number_of_circles = 0U;

    for (n = 0U; n < 4U*K->number_of_crossings; ++n)
    {
        /*  If we've already checked this crossing, skip it.                  */
        if (have_visited[n])
            continue;

        /*  The four "roads" at the thickened crossing are labeled as:        *
         *                                                                    *
         *       3          2         3          2                            *
         *      \  \      /  /       \  \      /  /                           *
         *       \  \    /  /         \  \    /  /                            *
         *        \  \  /  /           \  \  /  /                             *
         *         \  \/  /             \  \/  /                              *
         *          \  \ /               \ /  /                               *
         *           \  \     -           /  /     +                          *
         *          / \  \               /  / \                               *
         *         /  /\  \             /  /\  \                              *
         *        /  /  \  \           /  /  \  \                             *
         *       /  /    \  \         /  /    \  \                            *
         *      /  /      \  \       /  /      \  \                           *
         *       0          1         0          1                            *
         *                                                                    *
         *  where the + and - signs indicate the sign of the crossing and the *
         *  orientations are all directed "upwards" (hard to draw here).      *
         *  Given a number n between 0 and 4*N - 1, where N is the number of  *
         *  crossings, this value can be interpreted as a crossing and a road *
         *  number from the above picture. The crossing is n / 4 and the road *
         *  number is n mod 4, the last two bits of the integer. Compute this.*/
        road_index = n;
        crossing = road_index >> 2U;
        road_number = road_index & 0x03U;

        /*  The directions are forward = 0 and backward = 1, defined above.   *
         *  If you enter the crossing from roads 0 or 1, you are walking      *
         *  forwards to the crossing. If you enter through roads 2 or 3, you  *
         *  are walking backwards. Since we've chosen forward = 0 and         *
         *  backward = 1, we can compute the direction by bit shifting the    *
         *  road number. That is, we only care about the value of the 2's bit.*
         *  If it is 1 we are walking backwards, if it is 0 we are walking    *
         *  forwards. Compute this as well.                                   */
        direction = road_number >> 1U;

        /*  The sign is the same for over and under crossings. Grab either.   */
        sign = K->sign[ind[crossing].over];

        /*  The code index is our current position in the Gauss code. We know *
         *  the crossing number and can compute the code index using our      *
         *  indexing table "ind". Compute this value.                         */
        if (sign == positive_crossing)
        {
            /*  From the above picture, if we are at a positive crossing and  *
             *  if the road number is odd, we are on the under strand. If the *
             *  road number is even we are walking over the crossing.         */
            if (road_number & 0x01U)
                code_index = ind[crossing].under;
            else
                code_index = ind[crossing].over;
        }

        /*  Negative crossing, again appeal to the above picture.             */
        else
        {
            /*  We now look to the picture on the left drawn above for the    *
             *  negative crossing. If the road number is odd we are on the    *
             *  over stand, and if even we are on the under strand. This is   *
             *  the reverse of the previous code for a positive crossing.     */
            if (road_number & 0x01U)
                code_index = ind[crossing].over;
            else
                code_index = ind[crossing].under;
        }

        /*  Loop over every possible road, walking along paths in the knot    *
         *  generated by the complete smoothing, and count the number of      *
         *  cycles by keeping track of which roads have been visited.         */
        while (!have_visited[road_index])
        {
            /*  Mark the current road as "visited" and move to the next.      */
            have_visited[road_index] = 0x01U;

            /*  To determine which road we are going to next we need the      *
             *  value of the smoothing at this crossing. This is given by the *
             *  m^th bit of the resolution where m is the crossing number. We *
             *  can compute this by shifting the resolution down m bits and   *
             *  then zeroing everything but the least-significant bit.        */
            crossing_resolution = (resolution >> crossing) & 0x01U;

            /*  For a positive crossing the smoothings look as follows:       *
             *                                                                *
             *                                   3           2                *
             *                                  \  \       /  /               *
             *                                   \  \     /  /                *
             *                                    \  \   /  /                 *
             *                                     \  \ /  /                  *
             *       3          2                   \  |  /                   *
             *      \  \      /  /           0      /  |  \                   *
             *       \  \    /  /                  /  / \  \                  *
             *        \  \  /  /                  /  /   \  \                 *
             *         \  \/  /                  /  /     \  \                *
             *          \ /  /                  /  /       \  \               *
             *           /  /                                                 *
             *          /  / \                   3           2                *
             *         /  /\  \                 \  \       /  /               *
             *        /  /  \  \                 \  \     /  /                *
             *       /  /    \  \                 \  \   /  /                 *
             *      /  /      \  \                 \  \ /  /                  *
             *       0          1                   \_____/                   *
             *                               1      /     \                   *
             *                                     /  / \  \                  *
             *                                    /  /   \  \                 *
             *                                   /  /     \  \                *
             *                                  /  /       \  \               *
             *                                   0           1                *
             *                                                                *
             *  where once again all orientations are "upwards". The zero     *
             *  smoothing preserves the orientation whereas the one smoothing *
             *  reverses it. We use this picture to figure out which road we  *
             *  are leaving on, and which direction we are walking.           */
            if (sign == positive_crossing)
            {
                /*  For a zero smoothing we have:                             *
                 *      0 -> 3                                                *
                 *      1 -> 2                                                *
                 *      2 -> 1                                                *
                 *      3 -> 0                                                *
                 *  All points fit on the line y = 3 - x. Use this.           */
                if (crossing_resolution == 0x00U)
                    road_number = 3U - road_number;

                /*  For the one smoothing it is a bit trickier. We have:      *
                 *      0 -> 1                                                *
                 *      1 -> 0                                                *
                 *      2 -> 3                                                *
                 *      3 -> 2                                                *
                 *  The first two fit on the line y = 1 - x and the second    *
                 *  pair falls on y = 5 - x. We note that 5 mod 4 = 1 and     *
                 *  realize we can write y = (5 - x) mod 1. We compute mod 4  *
                 *  with bit-wise AND with 11_2 = 3.                          */
                else
                {
                    road_number = (5U - road_number) & 0x03U;

                    /*  The one smoothing reverses the orientation for a      *
                     *  positive crossing. Forward (zero) maps to backward    *
                     *  (one) and backward maps to forward. Swapping (0, 1)   *
                     *  with (1, 0) can be achieved using y = 1 - x.          */
                    direction = 0x01U - direction;
                }
            }

            /*  For a negative crossing the smoothings look as follows:       *
             *                                                                *
             *                                   3           2                *
             *                                  \  \       /  /               *
             *                                   \  \     /  /                *
             *                                    \  \   /  /                 *
             *                                     \  \ /  /                  *
             *       3          2                   \_____/                   *
             *      \  \      /  /           0      /     \                   *
             *       \  \    /  /                  /  / \  \                  *
             *        \  \  /  /                  /  /   \  \                 *
             *         \  \/  /                  /  /     \  \                *
             *          \  \ /                  /  /       \  \               *
             *           \  \                    0           1                *
             *          / \  \                   3           2                *
             *         /  /\  \                 \  \       /  /               *
             *        /  /  \  \                 \  \     /  /                *
             *       /  /    \  \                 \  \   /  /                 *
             *      /  /      \  \                 \  \ /  /                  *
             *       0          1                   \  |  /                   *
             *                               1      /  |  \                   *
             *                                     /  / \  \                  *
             *                                    /  /   \  \                 *
             *                                   /  /     \  \                *
             *                                  /  /       \  \               *
             *                                   0           1                *
             *                                                                *
             *  where once again all orientations are "upwards". The zero     *
             *  smoothing reverses the orientation whereas the one smoothing  *
             *  preserves it. We use this picture to figure out which road we *
             *  are leaving on, and which direction we are walking.           */
            else
            {
                /*  The swaps are a mirror of those for the positive crossing.*
                 *  We use the equations y = 3 - x and y = (5 - x) mod 4 to   *
                 *  compute, but switch which resolution uses which equation. */
                if (crossing_resolution == 0x00U)
                {
                    road_number = (5U - road_number) & 0x03U;

                    /*  Mirroring the positive crossing, for negative         *
                     *  crossings the zero smoothing reverses the orientation.*/
                    direction = 0x01U - direction;
                }

                else
                    road_number = 3U - road_number;
            }

            /*  Mark the road we leaving as visited as well.                  */
            have_visited[4U*crossing + road_number] = 0x01U;

            /*  When we change roads using the smoothing we are also          *
             *  switching which branch we are one. Over goes to under and     *
             *  vice-verse. We use this with the Gauss code to see which      *
             *  crossing we are heading for next.                             */
            if (K->type[code_index] == over_crossing)
                code_index = ind[crossing].under;
            else
                code_index = ind[crossing].over;

            /*  Move along in the Gauss code. If we are walking forwards,     *
             *  increment the code index by one to find the next crossing.    */
            if (direction == forward)
            {
                /*  If we are at the end of the Gauss code, loop back to the  *
                 *  starting part.                                            */
                if (code_index == 2U*K->number_of_crossings - 1U)
                    code_index = 0U;

                /*  Otherwise we can simply increment the index.              */
                else
                    ++code_index;
            }

            /*  If we reversed orientation at some point we are now walking   *
             *  backwards. We go to the previous entry in the Gauss code.     */
            else
            {
                /*  If we're at the start, we walk backwards to the final     *
                 *  entry in the Gauss code (it loops around).                */
                if (code_index == 0U)
                    code_index = 2U*K->number_of_crossings - 1U;

                /*  Otherwise we can simply decrement the index.              */
                else
                    --code_index;
            }

            /*  We are at the next crossing, but we need to know how we got   *
             *  there. There are four routes into the crossing. Here is the   *
             *  previous image for convenience:                               *
             *                                                                *
             *       3          2         3          2                        *
             *      \  \      /  /       \  \      /  /                       *
             *       \  \    /  /         \  \    /  /                        *
             *        \  \  /  /           \  \  /  /                         *
             *         \  \/  /             \  \/  /                          *
             *          \  \ /               \ /  /                           *
             *           \  \     -           /  /     +                      *
             *          / \  \               /  / \                           *
             *         /  /\  \             /  /\  \                          *
             *        /  /  \  \           /  /  \  \                         *
             *       /  /    \  \         /  /    \  \                        *
             *      /  /      \  \       /  /      \  \                       *
             *       0          1         0          1                        *
             *                                                                *
             *  We can translate which road we are coming into the crossing   *
             *  from by reading the type and sign of the crossing, and our    *
             *  orientation (whether we are walking forwards or backwards).   *
             *  Each possibility corresponds uniquely to one of the possible  *
             *  combinations of the three two-valued variables.               */
            if (K->sign[code_index] == positive_crossing)
            {
                if (K->type[code_index] == over_crossing)
                {
                    /*  Positive crossing and over strand. We look to the     *
                     *  picture on the right. If we are walking forwards, we  *
                     *  must be entering the crossing from road 0. Otherwise  *
                     *  we are entering from road 2.                          */
                    if (direction == forward)
                        road_number = 0U;
                    else
                        road_number = 2U;
                }

                else
                {
                    /*  Under strand, we again look to the picture on the     *
                     *  right. Forward direction corresponds to 1 and         *
                     *  walking backwards means we entered via 3.             */
                    if (direction == forward)
                        road_number = 1U;
                    else
                        road_number = 3U;
                }
            }

            /*  Negative crossing, the results mirror the positive one.       */
            else
            {
                if (K->type[code_index] == over_crossing)
                {
                    /*  We look to the left drawing now. Over crossing, if we *
                     *  are walking forwards we entered through road 1 and if *
                     *  backwards it must be road 3.                          */
                    if (direction == forward)
                        road_number = 1U;
                    else
                        road_number = 3U;
                }

                else
                {
                    /*  Lastly, negative crossing with the under strand. We   *
                     *  again appeal to the image on the left. If walking     *
                     *  forward we see that this corresponds to road 0, and   *
                     *  if backwards we are coming in through road 2.         */
                    if (direction == forward)
                        road_number = 0U;
                    else
                        road_number = 2U;
                }
            }

            /*  Update the values of everything for the next computation. The *
             *  sign and crossing number can be read from the Gauss code.     */
            crossing = K->crossing_number[code_index];
            sign = K->sign[code_index];

            /*  The road index can be determined from the road number that    *
             *  we've just computed, and the crossing number.                 */
            road_index = (crossing << 2U) + road_number;
        }

        /*  When the while loop terminates we've completed a cycle. Increment *
         *  the count.                                                        */
        ++number_of_circles;
    }

    return number_of_circles;
}
/*  End of circle_count.                                                      */
