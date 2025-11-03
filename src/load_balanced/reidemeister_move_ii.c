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
//        EXIT HERE
//   (same_far_crossing)  (diff_far_crossing)
//                 \\        /
//                  \\      /
//          /\ far_index   /
//                    \\  /
//               (next_crossing)
//                    /  \\
//                   /    \\
//                  /      \\
//                  \      //
//                   \   next_index /\
//                    \  //
//              (current_crossing)
//                   //   \
//                  //     \
//                 //       \
// (same_prev_crossing)   (diff_prev_crossing)
//      ENTER HERE
//

void reidemeister_move_ii(struct link* L)
{
    for (int component = 0; component < L->number_of_components; component++) {
        struct crossing* current_crossing = L->first_crossing_in_components[component];
        int next_index = 2;
        do {
            struct crossing* next_crossing = current_crossing->data[next_index];
            int far_index = OPP(current_crossing->ports[next_index]);

            if (
                /* current_crossing is connect to next_crossing somewhere else */
                (current_crossing->data[PREV(next_index)] == next_crossing || current_crossing->data[NEXT(next_index)] == next_crossing)
                /* && the crossing signs are correct for an R2*/
                && (next_index % 2) == (far_index % 2)
            ) {
                /* Set all the other relevant crossing names */
                struct crossing* same_prev_crossing = current_crossing->data[OPP(next_index)];
                struct crossing* diff_prev_crossing = // Find whichever one leads to somewhere else from current_crossing
                    (current_crossing->data[NEXT(next_index)] == next_crossing) ? 
                        current_crossing->data[PREV(next_index)] :
                        current_crossing->data[NEXT(next_index)];
                struct crossing* same_far_crossing = next_crossing->data[far_index];
                struct crossing* diff_far_crossing = // Find whichever one leads to somewhere else from next_crossing
                    (next_crossing->data[NEXT(far_index)] == current_crossing) ?
                        next_crossing->data[PREV(far_index)] :
                        next_crossing->data[NEXT(far_index)];

                
            } else {
                current_crossing = current_crossing->data[next_index];
                next_index = OPP(current_crossing->ports[next_index]);
            }
        } while (L->number_of_crossings_in_components[component] > 0 && current_crossing != L->first_crossing_in_components[component]);
    }
}