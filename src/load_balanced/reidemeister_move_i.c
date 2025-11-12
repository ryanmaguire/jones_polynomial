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

/* Function to scan for and perform all Type I Reidemeister moves */
/* Leaves behind 0 in number_of_crossings_in_components if an unknot diagram is created */

//                                   _________________________
//                                  /                         \
//                                  |                         |
//  (previous_crossing)-----(current_crossing)--next_index>---/
//                                  |
//                                  |
//                           (next_crossing)

// Alternative orientation

//                           (next_crossing)
//                                  |
//                                  |
//  (previous_crossing)-----(current_crossing)--next_index>---\
//                                  |                         |
//                                  \_________________________/
//                                

enum boolean reidemeister_move_i(struct link* L) 
{
    enum boolean found_something = FALSE;
    
    for (int component = 0; component < L->number_of_components; component++) {
        if (L->number_of_crossings_in_components[component] <= 0) {
            continue;
        }

        int next_index = 2;
        struct crossing* current_crossing = L->first_crossing_in_components[component];
        struct crossing* previous_crossing = current_crossing->data[OPP(next_index)];
        do {
            if (current_crossing->data[next_index] == current_crossing) {
                struct crossing* next_crossing = // Find whichever one leads to somewhere else
                    (current_crossing->data[NEXT(next_index)] == current_crossing) ? 
                        current_crossing->data[PREV(next_index)] :
                        current_crossing->data[NEXT(next_index)];
                
                /* Update previous_crossing */
                int previous_crossing_leave_index = current_crossing->ports[OPP(next_index)];
                previous_crossing->data[previous_crossing_leave_index] = next_crossing;
                previous_crossing->ports[previous_crossing_leave_index] = current_crossing->ports[next_index];
                
                /* Update next_crossing */
                int current_to_next_index = OPP(current_crossing->ports[next_index]);
                int next_crossing_enter_index = current_crossing->ports[current_to_next_index];
                next_crossing->data[next_crossing_enter_index] = previous_crossing;
                next_crossing->ports[next_crossing_enter_index] = current_crossing->ports[OPP(next_index)];
                
                /* Update crossing counts in link component */
                L->number_of_crossings_in_components[component]--;

                /* Edge case where current_crossing is also first crossing */
                if (current_crossing == L->first_crossing_in_components[component]) {
                    L->first_crossing_in_components[component] = previous_crossing;
                }

                next_index = OPP(current_crossing->ports[next_index]);
                delete_crossing(current_crossing);
                current_crossing = next_crossing; 
                // No need to update previous_crossing since it is now adjacent to next_crossing = current_crossing

                found_something = TRUE;
            } else {
                previous_crossing = current_crossing;
                current_crossing = current_crossing->data[next_index];
                next_index = OPP(previous_crossing->ports[next_index]);
            }
        } while (
            /* Edge case check to make sure we aren't trying to do stuff to an unknot */
            L->number_of_crossings_in_components[component] > 0 
            /* Keep on looping until we go around the link */
            && current_crossing != L->first_crossing_in_components[component]
        );
    }

    return found_something;
}
