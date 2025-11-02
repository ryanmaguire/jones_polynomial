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
 *
 *  with jones_polynomial.  If not, see <https://www.gnu.org/licenses/>.      *
 ******************************************************************************/
 #include "load_balanced.h"

/* Function to scan for and perform all Type II Reidemeister moves */
/* Leaves behind 0 in number_of_crossings_in_components if an unknot diagram is created */

// Travelling along emphasized strands, from bottom to top
//
//      EXIT HERE
//   same_far_crossing  diff_far_crossing
//                 \\    /
//                  \\  /
//              next_crossing
//                  /  \\
//                 /    \\
//                 \    //
//                  \  //
//             current_crossing
//                 //   \
//                //     \
// same_prev_crossing   diff_prev_crossing
//     ENTER HERE
//

void reidemeister_move_ii(struct link* L)
{
    for (int component = 0; component < L->number_of_components; component++) {
        struct crossing* current_crossing = L->first_crossing_in_components[component];
        int next_index = 2;
        do {
            if (current_crossing->data[next_index] == current_crossing) {
                
            } else {
                current_crossing = current_crossing->data[next_index];
                next_index = OPP(current_crossing->ports[next_index]);
            }
        } while (L->number_of_crossings_in_components[component] > 0 && current_crossing != L->first_crossing_in_components[component]);
    }
}