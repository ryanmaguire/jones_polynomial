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

// next_crossing and current_crossing must have different signs
// Travelling along emphasized strands, from bottom to top
//
//           EXIT HERE
//      (same_far_crossing)   (diff_far_crossing)
//                     \\        /
//                      \\      /
//              /\ far_index  diff_far_index /\
//                        \\  /
//                   (next_crossing)
//                        /  \\
//                       /    \\
//                      /      \\
//                      \      //
//       /\ diff_next_index  next_index /\
//                        \  //
//                  (current_crossing)
//                       //   \
//                      //     \
//                     //       \
// (same_previous_crossing)   (diff_previous_crossing)
//      ENTER HERE
//

int reidemeister_move_ii(struct link* L)
{   
    int number_of_simplifications = 0;

    for (int component = 0; component < L->number_of_components; component++) {
        if (L->number_of_crossings_in_components[component] <= 1) {
            continue;
        }

        // This will be decremented by 1 if the crossing will be visitied twice, by 2 otherwise
        int crossings_left_to_visit = 2 * L->number_of_crossings_in_components[component]; 
        
        struct crossing* current_crossing = L->first_crossing_in_components[component];
        int next_index = (current_crossing->under_component == component) ? 2 : 1;
        struct crossing* previous_crossing = current_crossing->data[OPP(next_index)];
        do {
            struct crossing* next_crossing = current_crossing->data[next_index];
            int far_index = OPP(current_crossing->ports[next_index]);

            if (
                current_crossing != next_crossing &&
                /* current_crossing connects to next_crossing somewhere else */
                (current_crossing->data[PREV(next_index)] == next_crossing || current_crossing->data[NEXT(next_index)] == next_crossing)
                /* && the crossing signs are correct for an R2*/
                && (next_index % 2) == (far_index % 2)
            ) {
                /* Set all the other relevant crossing names */
                struct crossing* same_previous_crossing = previous_crossing;
                struct crossing* same_far_crossing = next_crossing->data[far_index];

                int diff_next_index = // Find whichever one leads to somewhere else from current_crossing
                    (current_crossing->data[NEXT(next_index)] == next_crossing) ? 
                        NEXT(next_index) :
                        PREV(next_index);
                struct crossing* diff_previous_crossing = current_crossing->data[OPP(diff_next_index)];

                int diff_far_index = // Find whichever one leads to somewhere else from next_crossing
                    (next_crossing->data[NEXT(far_index)] == current_crossing) ?
                        PREV(far_index) :
                        NEXT(far_index);
                struct crossing* diff_far_crossing = next_crossing->data[diff_far_index];

                /* Set new variables */
                int same_previous_crossing_leave_index = current_crossing->ports[OPP(next_index)];
                int diff_previous_crossing_leave_index = current_crossing->ports[OPP(diff_next_index)];
                int same_far_crossing_enter_index = next_crossing->ports[far_index];
                int diff_far_crossing_enter_index = next_crossing->ports[diff_far_index];

                int same_previous_crossing_new_port = next_crossing->ports[far_index];
                int diff_previous_crossing_new_port = next_crossing->ports[diff_far_index];
                int same_far_crossing_new_port = current_crossing->ports[OPP(next_index)];
                int diff_far_crossing_new_port = current_crossing->ports[OPP(diff_next_index)];
                
                /* Update same_previous_crossing */
                same_previous_crossing->data[same_previous_crossing_leave_index] = same_far_crossing;
                same_previous_crossing->ports[same_previous_crossing_leave_index] = same_previous_crossing_new_port;

                /* Update diff_previous_crossing */
                diff_previous_crossing->data[diff_previous_crossing_leave_index] = diff_far_crossing;
                diff_previous_crossing->ports[diff_previous_crossing_leave_index] = diff_previous_crossing_new_port;

                /* Update same_far_crossing */
                same_far_crossing->data[same_far_crossing_enter_index] = same_previous_crossing;
                same_far_crossing->ports[same_far_crossing_enter_index] = same_far_crossing_new_port;

                /* Update diff_far_crossing */
                diff_far_crossing->data[diff_far_crossing_enter_index] = diff_previous_crossing;
                diff_far_crossing->ports[diff_far_crossing_enter_index] = diff_far_crossing_new_port;

                /* Update crossing counts in link component */
                L->number_of_crossings_in_components[component] -= 2;
                int other_component = -1;
                if (current_crossing->over_component != component || current_crossing->under_component != component) {
                    /* Hack to calculate the index of the other component */
                    other_component = current_crossing->over_component + current_crossing->under_component - component;
                    L->number_of_crossings_in_components[other_component] -= 2;
                }

                /* Edge case where current_crossing or next_crossing is also first crossing */
                if (current_crossing == L->first_crossing_in_components[component] || next_crossing == L->first_crossing_in_components[component]) {
                    L->first_crossing_in_components[component] = same_previous_crossing;
                }
                if ( // Also do this for the other component
                    other_component != -1 
                    && (
                        current_crossing == L->first_crossing_in_components[other_component] 
                        || next_crossing == L->first_crossing_in_components[other_component]
                    )
                ) {
                    /* Here, other_component must be distinct from component. This means that we aren't
                     * trying to iterate through other_component right now, which means that we are safe
                     * to move the first crossing for other_component to some arbitrary crossing in 
                     * other_component. */
                    L->first_crossing_in_components[other_component] = diff_previous_crossing;
                }

                crossings_left_to_visit -= 4; // two crossings get die

                next_index = OPP(next_crossing->ports[far_index]);
                delete_crossing(&current_crossing);
                delete_crossing(&next_crossing);
                if (crossings_left_to_visit > 0) {
                    current_crossing = same_far_crossing; 
                }
                // No need to update previous_crossing since it is now adjacent to same_far_crossing = current_crossing

                number_of_simplifications++;
            } else {
                if (current_crossing->over_component == current_crossing->under_component) {
                    crossings_left_to_visit -= 1;
                } else {
                    crossings_left_to_visit -= 2;
                }

                previous_crossing = current_crossing;
                current_crossing = current_crossing->data[next_index];
                next_index = OPP(previous_crossing->ports[next_index]);
            }
        } while (L->number_of_crossings_in_components[component] > 0 && crossings_left_to_visit > 0);
    }

    return number_of_simplifications;
}
