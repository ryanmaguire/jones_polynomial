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
#include <stddef.h>
#include "kauffman.h"

static unsigned char have_visited[4U * MAX_CROSSINGS];

unsigned int
circle_count(const struct knot *K,
             const struct crossing_indices *ind,
             unsigned int resolution)
{
    unsigned int number_of_circles, n, road_index, crossing, code_index;
    unsigned char direction, crossing_resolution, road_number;
    enum crossing_sign sign;

    /*  The direction is stored as an unsigned char. There are two            *
     *  possibilities: forwards and backwards.                                */
    const unsigned char forward = 0x00U;
    const unsigned char backward = 0x01U;

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
        if (have_visited[n])
            continue;

        road_index = n;
        road_number = road_index & 0x03U;
        direction = road_number >> 1U;
        crossing = road_index >> 2U;

        /*  The sign is the same for over and under crossings. Grab either.   */
        sign = K->sign[ind[crossing].over];

        if (sign == positive_crossing)
        {
            if (road_number & 0x01U)
                code_index = ind[crossing].under;
            else
                code_index = ind[crossing].over;
        }

        else
        {
            if (road_number & 0x01U)
                code_index = ind[crossing].over;
            else
                code_index = ind[crossing].under;
        }

        while (!have_visited[road_index])
        {
            have_visited[road_index] = 0x01U;
            crossing_resolution = (resolution >> crossing) & 0x01U;

            if (sign == positive_crossing)
            {
                if (crossing_resolution == 0x00U)
                    road_number = 3U - road_number;
                else
                {
                    road_number = (5U - road_number) & 0x03U;
                    direction = 0x01U - direction;
                }
            }
            else
            {
                if (crossing_resolution == 0x00U)
                {
                    road_number = (5U - road_number) & 0x03U;
                    direction = 0x01U - direction;
                }
                else
                    road_number = 3U - road_number;
            }

            have_visited[4U*crossing + road_number] = 0x01U;

            if (K->type[code_index] == over_crossing)
                code_index = ind[crossing].under;
            else
                code_index = ind[crossing].over;

            if (direction == forward)
            {
                if (code_index == 2U*K->number_of_crossings - 1U)
                    code_index = 0U;
                else
                    ++code_index;
            }
            else
            {
                if (code_index == 0U)
                    code_index = 2U*K->number_of_crossings - 1U;
                else
                    --code_index;
            }

            if (K->sign[code_index] == positive_crossing)
            {
                if (K->type[code_index] == over_crossing)
                {
                    if (direction == backward)
                        road_number = 2U;
                    else
                        road_number = 0U;
                }
                else
                {
                    if (direction == forward)
                        road_number = 1U;
                    else
                        road_number = 3U;
                }
            }

            else
            {
                if (K->type[code_index] == over_crossing)
                {
                    if (direction == forward)
                        road_number = 1U;
                    else
                        road_number = 3U;
                }
                else
                {
                    if (direction == backward)
                        road_number = 2U;
                    else
                        road_number = 0U;
                }
            }

            crossing = K->crossing_number[code_index];
            road_index = (crossing << 2U) + road_number;
            sign = K->sign[code_index];
        }

        ++number_of_circles;
    }

    return number_of_circles;
}
