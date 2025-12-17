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

/* Function to search for the first occurence of a triple */
/* If found, returns the component number and sets the crossing as the first crossing of the component */
/* If not found, L is unchanged and -1 is returned */

/* Travelling along emphasized strands, from left to right
          
                                               (top_left_crossing)           (top_right_crossing)
                                                         \                             /
                                                          \                           /
                                                           \                         /
                                         /\ top_middle_to_left_index         top_middle_to_right_index /\
                                                              \                   /
                                                              (top_middle_crossing)
                                                              /                   \
                                                            /                       \
                                                          /                           \
                                           /\ current_to_top_index             next_to_top_index /\
                                                       /                                 \
   ENTER HERE ===(previous_crossing)=====(current_crossing)== next_index > ===========(next_crossing)== far_index > =====(far_crossing)=== EXIT HERE
                                                       \                                 /
                                        \/ current_to_bottom_index             next_to_bottom_index \/
                                                          \                           /
                                                            \                       /
                                                              \                   /
                                                             (bottom_middle_crossing)
                                                              /                   \
                                      \/ bottom_middle_to_left_index         bottom_middle_to_right_index \/
                                                           /                         \
                                                          /                           \
                                                         /                             \
                                              (bottom_left_crossing)        (bottom_right_crossing)
*/

int triple_search(const struct link* L) 
{
    for (size_t component = 0; component < L->number_of_components; component++) {
        if (L->number_of_crossings_in_components[component] <= 2) { // change later
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
            
            // Arbitrary assignment of top crossings vs bottom crossings in the diagram
            int next_to_top_index = NEXT(far_index);
            int next_to_bottom_index = OPP(next_to_top_index);

            struct crossing* top_middle_crossing = next_crossing->data[next_to_top_index];
            struct crossing* bottom_middle_crossing = next_crossing->data[next_to_bottom_index];

            /* Check whether we have a triple at all */
            if (
                /* Does current_crossing connect to top_middle_crossing and bottom_middle_crossing in some order? */
                (
                    current_crossing->data[NEXT(next_index)] == top_middle_crossing 
                    && current_crossing->data[PREV(next_index)] == bottom_middle_crossing
                )
                ||
                (
                    current_crossing->data[PREV(next_index)] == top_middle_crossing 
                    && current_crossing->data[NEXT(next_index)] == bottom_middle_crossing
                )
            ) {
                /* Great - we have a triple! Let's first check if its of type 1 or 2, either positive or negative. */
                if (next_index % 2 == far_index % 2) {
                    L->first_crossing_in_components[component] = top_middle_crossing;
                    return component;
                }

                /* Otherwise, we need to check that it is not of null type 4 (which doesn't simplify well at all). 
                 * To do this, we first need some more infrastructure. */
                
                int current_to_top_index = // Find which one leads to top_middle_crossing
                    (current_crossing->data[NEXT(next_index)] == top_middle_crossing) ? 
                        NEXT(next_index) :
                        PREV(next_index);
                int current_to_bottom_index = OPP(current_to_top_index);

                /* Set up some of the strand indices */
                int top_middle_to_right_index = OPP(current_crossing->ports[current_to_top_index]);
                int bottom_middle_to_right_index = OPP(current_crossing->ports[current_to_bottom_index]);
                
                /* Check whether this triple is not null type 4 */
                if (top_middle_to_right_index % 2 != bottom_middle_to_right_index % 2) {
                    L->first_crossing_in_components[component] = current_crossing;
                    return component;
                }
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
