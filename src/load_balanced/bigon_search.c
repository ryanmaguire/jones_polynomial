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

/* Function to search for the first occurence of a bigon */
/* If found, returns the component number and sets the crossing as the first crossing of the component */
/* If not found, L is unchanged and -1 is returned */

// next_crossing and current_crossing must have the same sign
// Travelling along emphasized strands, from bottom to top
//
//           EXIT HERE
//      (same_far_crossing)   (diff_far_crossing)
//                     \\        /
//                      \\      /
//              /\ far_index   /
//                        \\  /
//                   (next_crossing)
//                        /  \\
//                       /    \\
//                      /      \\
//                      \      //
//                       \   next_index /\
//                        \  //
//                  (current_crossing)
//                       //   \
//                      //     \
//                     //       \
// (same_previous_crossing)   (diff_previous_crossing)
//      ENTER HERE
//

int bigon_search(const struct link* L) 
{  
    for (int component = 0; component < L->number_of_components; component++) {
        if (L->number_of_crossings_in_components[component] <= 1) {
            continue;
        }

        // This will be decremented by 1 if the crossing will be visitied twice, by 2 otherwise
        int crossings_left_to_visit = 2 * L->number_of_crossings_in_components[component]; 

        struct crossing* previous_crossing = NULL;
        struct crossing* current_crossing = L->first_crossing_in_components[component];
        int next_index = (current_crossing->under_component == component) ? 2 : 1;
        do {
            struct crossing* next_crossing = current_crossing->data[next_index];
            int far_index = OPP(current_crossing->ports[next_index]);

            if (
                /* current_crossing connects to next_crossing somewhere else */
                (current_crossing->data[PREV(next_index)] == next_crossing || current_crossing->data[NEXT(next_index)] == next_crossing)
                /* && the crossing signs are correct for a bigon*/
                && (next_index % 2) != (far_index % 2)
            ) {
                L->first_crossing_in_components[component] = current_crossing;
                return component;
            }

            if (current_crossing->over_component == current_crossing->under_component) {
                crossings_left_to_visit -= 1;
            } else {
                crossings_left_to_visit -= 2;
            }

            previous_crossing = current_crossing;
            current_crossing = current_crossing->data[next_index];
            next_index = OPP(previous_crossing->ports[next_index]);
        } while (crossings_left_to_visit > 0);
    }

    return -1;
}