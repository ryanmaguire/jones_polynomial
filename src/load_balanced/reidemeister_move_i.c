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

//                                 _________________________
//                                /                         \
//                                |                         |
//  (prev_crossing)-------(current_crossing)--next_index>---/
//                                |
//                                |
//                         (next_crossing)

// Alternative orientation

//                         (next_crossing)
//                                |
//                                |
//  (prev_crossing)-------(current_crossing)--next_index>---\
//                                |                         |
//                                \_________________________/
//                                

void reidemeister_move_i(struct link* L) 
{
    for (int component = 0; component < L->number_of_components; component++) {
        struct crossing* current_crossing = L->first_crossing_in_components[component];
        int next_index = 2;
        do {
            if (current_crossing->data[next_index] == current_crossing) {
                struct crossing* prev_crossing = current_crossing->data[OPP(next_index)];
                struct crossing* next_crossing = // Find whichever one leads to somewhere else
                    (current_crossing->data[NEXT(next_index)] == current_crossing) ? 
                        current_crossing->data[PREV(next_index)] :
                        current_crossing->data[NEXT(next_index)];
                
                int prev_crossing_leave_index = current_crossing->ports[OPP(next_index)]; // Update previous crossing
                prev_crossing->data[prev_crossing_leave_index] = next_crossing;
                prev_crossing->ports[prev_crossing_leave_index] = current_crossing->ports[next_index];

                int next_crossing_enter_index = current_crossing->ports[next_index]; // Update next crossing
                next_crossing->data[next_crossing_enter_index] = prev_crossing;
                next_crossing->ports[next_crossing_enter_index] = current_crossing->ports[OPP(next_index)];

                L->number_of_crossings_in_components[component]--; // Decrement number of crossings in link component

                next_index = OPP(current_crossing->ports[next_index]); // Set next index before deleting current_crossing
                if (current_crossing == L->first_crossing_in_components[component]) { // Edge case: if current crossing is first crossing
                    L->first_crossing_in_components[component] = prev_crossing;
                }
                delete_crossing(current_crossing);
                current_crossing = next_crossing; 
            } else {
                current_crossing = current_crossing->data[next_index];
                next_index = OPP(current_crossing->ports[next_index]);
            }
        } while (L->number_of_crossings_in_components[component] > 0 && current_crossing != L->first_crossing_in_components[component]);
    }
}