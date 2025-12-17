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

/*                                   _________________________
                                    /                         \
                                    |                         |
    (previous_crossing)-----(current_crossing)--next_index>---/
                          current_to_next_index \/
                                    |
                             (next_crossing)
*/

// Alternative orientation

/*                           (next_crossing)
                                    |
                         current_to_next_index /\
    (previous_crossing)-----(current_crossing)--next_index>---\
                                    |                         |
                                    \_________________________/
*/                                

int reidemeister_move_i(struct link* L, int* const writhe) 
{
    //printf("R1 called\n");
    int number_of_simplifications = 0;
    
    for (size_t component = 0; component < L->number_of_components; component++) {
        if (L->number_of_crossings_in_components[component] <= 0) {
            continue;
        }

        // This will be decremented by 1 if the crossing will be visitied twice, by 2 otherwise
        int crossings_left_to_visit = 2 * L->number_of_crossings_in_components[component]; 

        struct crossing* current_crossing = L->first_crossing_in_components[component];
        int next_index = (current_crossing->under_component == component) ? 2 : 1;
        struct crossing* previous_crossing = current_crossing->data[OPP(next_index)];
        do {
            if (current_crossing->data[next_index] == current_crossing) { // Perform a check for R1
                int current_to_next_index = // Find whichever one leads to somewhere else
                    (current_crossing->data[NEXT(next_index)] == current_crossing && current_crossing->ports[NEXT(next_index)] == next_index) ? 
                        PREV(next_index) :
                        NEXT(next_index);

                struct crossing* next_crossing = current_crossing->data[current_to_next_index];

                *writhe += ((next_index + OPP(current_to_next_index)) % 4 == 1) ? 1 : -1;
                
                /* Update previous_crossing */
                int previous_crossing_leave_index = current_crossing->ports[OPP(next_index)];
                previous_crossing->data[previous_crossing_leave_index] = next_crossing;
                previous_crossing->ports[previous_crossing_leave_index] = current_crossing->ports[current_to_next_index];
                
                /* Update next_crossing */
                int next_crossing_enter_index = current_crossing->ports[current_to_next_index];
                next_crossing->data[next_crossing_enter_index] = previous_crossing;
                next_crossing->ports[next_crossing_enter_index] = current_crossing->ports[OPP(next_index)];
                
                /* Update crossing counts in link component */
                L->number_of_crossings_in_components[component]--;

                /* Edge case where current_crossing is also first crossing */
                if (current_crossing == L->first_crossing_in_components[component]) {
                    L->first_crossing_in_components[component] = previous_crossing;
                }

                crossings_left_to_visit -= 2; // current_crossing always has both strands in current component

                next_index = OPP(current_crossing->ports[current_to_next_index]);
                delete_crossing(&current_crossing);
                if (crossings_left_to_visit > 0) {
                    current_crossing = next_crossing; 
                }
                // No need to update previous_crossing since it is now adjacent to next_crossing = current_crossing

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
    //printf("R1 finished\n");
    return number_of_simplifications;
}
