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

/* Function to scan for and perform all null triple reductions */
/* Leaves behind 0 in number_of_crossings_in_components if an unknot diagram is created */

// Travelling along emphasized strands, from left to right
//        
//                                             (top_left_crossing)           (top_right_crossing)
//                                                       \                             /
//                                                        \                           /
//                                                         \                         /
//                                       /\ top_middle_to_left_index         top_middle_to_right_index /\
//                                                            \                   /
//                                                            (top_middle_crossing)
//                                                            /                   \
//                                                          /                       \
//                                                        /                           \
//                                         /\ current_to_top_index             next_to_top_index /\
//                                                     /                                 \
// ENTER HERE ===(previous_crossing)=====(current_crossing)== next_index > ===========(next_crossing)== far_index > =====(far_crossing)=== EXIT HERE
//                                                     \                                 /
//                                      \/ current_to_bottom_index             next_to_bottom_index \/
//                                                        \                           /
//                                                          \                       /
//                                                            \                   /
//                                                           (bottom_middle_crossing)
//                                                            /                   \
//                                    \/ bottom_middle_to_left_index         bottom_middle_to_right_index \/
//                                                         /                         \
//                                                        /                           \
//                                                       /                             \
//                                            (bottom_left_crossing)        (bottom_right_crossing)
//

int null_triple(struct link* L) 
{
    int number_of_simplifications = 0;

    for (int component = 0; component < L->number_of_components; component++) {
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
                /* Great - we have a triple! Let's set up some more infrastructure. */

                struct crossing* far_crossing = next_crossing->data[far_index];
                
                int current_to_top_index = // Find which one leads to top_middle_crossing
                    (current_crossing->data[NEXT(next_index)] == top_middle_crossing) ? 
                        NEXT(next_index) :
                        PREV(next_index);
                int current_to_bottom_index = OPP(current_to_top_index);

                /* Set up the rest of the strand indices */
                int top_middle_to_right_index = OPP(current_crossing->ports[current_to_top_index]);
                int bottom_middle_to_right_index = OPP(current_crossing->ports[current_to_bottom_index]);
                int top_middle_to_left_index = OPP(next_crossing->ports[next_to_top_index]);
                int bottom_middle_to_left_index = OPP(next_crossing->ports[next_to_bottom_index]);
                
                /* Check whether this triple is a simplifiable null triple */
                if (
                    /* The vertical strand through current_crossing is all over or all under */
                    (
                        (current_to_top_index % 2) == (top_middle_to_right_index % 2) 
                        && (current_to_bottom_index % 2) == (bottom_middle_to_right_index % 2)
                    )
                    ||
                    /* The vertical strand through next_crossing is all over or all under */
                    (
                        (next_to_top_index % 2) == (top_middle_to_left_index % 2)
                        && (next_to_bottom_index % 2) == (bottom_middle_to_left_index % 2)
                    )
                ) {
                    /* Set all the other relevant crossing names */
                    struct crossing* top_right_crossing = top_middle_crossing->data[top_middle_to_right_index];
                    struct crossing* top_left_crossing = top_middle_crossing->data[top_middle_to_left_index];
                    struct crossing* bottom_right_crossing = bottom_middle_crossing->data[bottom_middle_to_right_index];
                    struct crossing* bottom_left_crossing = bottom_middle_crossing->data[bottom_middle_to_left_index];

                    /* The two strands involved in top_middle_crossing will be part of component_1
                     * and component_2, where component_1 goes to current_crossing and component_2 goes 
                     * to next_crossing */
                    int component_1, component_2;
                    if (top_middle_to_right_index % 2 == 0) { // if component_1 is under
                        component_1 = top_middle_crossing->under_component;
                        component_2 = top_middle_crossing->over_component;
                    } else {
                        component_1 = top_middle_crossing->over_component;
                        component_2 = top_middle_crossing->under_component;
                    }
                    
                    /* Update crossing counts in link component */
                    L->number_of_crossings_in_components[component_1] -= 2;
                    if (component_1 != component_2) {
                        L->number_of_crossings_in_components[component_2] -= 2;
                    }

                    /* Edge case where we are about to delete first crossing in the current component */
                    /* We will loop through this as needed anyways, and it's like impossible to avoid
                     * an OBOE because there's no knowing what direction a future traversal of the
                     * knot will use, so there if top_middle_crossing and bottom_middle_crossing are
                     * involved in the current component then we might miss one null triple check */
                    if (
                        top_middle_crossing == L->first_crossing_in_components[component_1] 
                        || bottom_middle_crossing == L->first_crossing_in_components[component_1]
                    ) {
                        L->first_crossing_in_components[component_1] = current_crossing;
                    }
                    if (
                        component_1 != component_2
                        && (
                            top_middle_crossing == L->first_crossing_in_components[component_2] 
                            || bottom_middle_crossing == L->first_crossing_in_components[component_2]
                        )
                    ) {
                        L->first_crossing_in_components[component_2] = next_crossing;
                    }

                    /* First swap positions of current_crossing and next_crossing with respect to previous_crossing and far_crossing */

                    /* Update previous_crossing */
                    int previous_crossing_leave_index = current_crossing->ports[OPP(next_index)];
                    previous_crossing->data[previous_crossing_leave_index] = next_crossing;
                    previous_crossing->ports[previous_crossing_leave_index] = OPP(far_index);

                    /* Update far_crossing */
                    int far_crossing_enter_index = next_crossing->ports[far_index];
                    far_crossing->data[far_crossing_enter_index] = current_crossing;
                    far_crossing->ports[far_crossing_enter_index] = next_index;

                    /* Update current_crossing */
                    current_crossing->data[OPP(next_index)] = next_crossing;
                    current_crossing->ports[OPP(next_index)] = far_index;
                    /* Weird edge case where the triple wraps back */
                    if (far_crossing == top_middle_crossing) {
                        current_crossing->data[next_index] = current_crossing;
                        current_crossing->ports[next_index] = current_to_top_index;
                    } else if (far_crossing == bottom_middle_crossing) {
                        current_crossing->data[next_index] = current_crossing;
                        current_crossing->ports[next_index] = current_to_bottom_index;
                    } else {
                        current_crossing->data[next_index] = far_crossing;
                        current_crossing->ports[next_index] = far_crossing_enter_index;
                    }

                    /* Update next_crossing */
                    next_crossing->data[far_index] = current_crossing;
                    next_crossing->ports[far_index] = OPP(next_index);
                    /* Weird edge case where the triple wraps back */
                    if (previous_crossing == top_middle_crossing) {
                        next_crossing->data[OPP(far_index)] = next_crossing;
                        next_crossing->ports[OPP(far_index)] = next_to_top_index;
                    } else if (previous_crossing == bottom_middle_crossing) {
                        next_crossing->data[OPP(far_index)] = next_crossing;
                        next_crossing->ports[OPP(far_index)] = next_to_bottom_index;
                    } else {
                        next_crossing->data[OPP(far_index)] = previous_crossing;
                        next_crossing->ports[OPP(far_index)] = previous_crossing_leave_index;
                    }

                    /* We will now route the remaining crossings away from top_middle_crossing and bottom_middle_crossing */
                    /* Recall that current_crossing and next_crossing have now switched */

                    /* Update top_right_crossing */
                    int top_right_crossing_enter_index = top_middle_crossing->ports[top_middle_to_right_index];
                    top_right_crossing->data[top_right_crossing_enter_index] = current_crossing;
                    top_right_crossing->ports[top_right_crossing_enter_index] = current_to_top_index;

                    /* Update top_left_crossing */
                    int top_left_crossing_enter_index = top_middle_crossing->ports[top_middle_to_left_index];
                    top_left_crossing->data[top_left_crossing_enter_index] = next_crossing;
                    top_left_crossing->ports[top_left_crossing_enter_index] = next_to_top_index;

                    /* Update bottom_right_crossing*/
                    int bottom_right_crossing_enter_index = bottom_middle_crossing->ports[bottom_middle_to_right_index];
                    bottom_right_crossing->data[bottom_right_crossing_enter_index] = current_crossing;
                    bottom_right_crossing->ports[bottom_right_crossing_enter_index] = current_to_bottom_index;

                    /* Update bottom_left_crossing*/
                    int bottom_left_crossing_enter_index = bottom_middle_crossing->ports[bottom_middle_to_left_index];
                    bottom_left_crossing->data[bottom_left_crossing_enter_index] = next_crossing;
                    bottom_left_crossing->ports[bottom_left_crossing_enter_index] = next_to_bottom_index;

                    /* Update the vertical ports of current_crossing */
                    /* Weird edge case where there's a loop */
                    if (top_right_crossing == top_middle_crossing) {
                        assert(top_right_crossing == top_left_crossing);
                        current_crossing->data[current_to_top_index] = next_crossing;
                        current_crossing->ports[current_to_top_index] = next_to_top_index;
                    } else if (top_right_crossing == next_crossing) {
                        current_crossing->data[current_to_top_index] = current_crossing;
                        current_crossing->ports[current_to_top_index] = next_index;
                    } else {
                        current_crossing->data[current_to_top_index] = top_right_crossing;
                        current_crossing->ports[current_to_top_index] = top_right_crossing_enter_index;
                    }
                    if (bottom_right_crossing == bottom_middle_crossing) {
                        assert(bottom_right_crossing == bottom_left_crossing);
                        current_crossing->data[current_to_bottom_index] = next_crossing;
                        current_crossing->ports[current_to_bottom_index] = next_to_bottom_index;
                    } else if (bottom_right_crossing == next_crossing) {
                        current_crossing->data[current_to_bottom_index] = current_crossing;
                        current_crossing->ports[current_to_bottom_index] = next_index;
                    } else {
                        current_crossing->data[current_to_bottom_index] = bottom_right_crossing;
                        current_crossing->ports[current_to_bottom_index] = bottom_right_crossing_enter_index;
                    }

                    /* Update the vertical ports of next_crossing */
                    /* Weird edge case where there's a loop */
                    if (top_left_crossing == top_middle_crossing) {
                        assert(top_right_crossing == top_left_crossing);
                        next_crossing->data[next_to_top_index] = current_crossing;
                        next_crossing->ports[next_to_top_index] = current_to_top_index;
                    } else if (top_left_crossing == current_crossing) {
                        next_crossing->data[next_to_top_index] = next_crossing;
                        next_crossing->ports[next_to_top_index] = OPP(far_index);
                    } else {
                        next_crossing->data[next_to_top_index] = top_left_crossing;
                        next_crossing->ports[next_to_top_index] = top_left_crossing_enter_index;
                    }
                    if (bottom_left_crossing == bottom_middle_crossing) {
                        assert(bottom_right_crossing == bottom_left_crossing);
                        next_crossing->data[next_to_bottom_index] = current_crossing;
                        next_crossing->ports[next_to_bottom_index] = current_to_bottom_index;
                    } else if (bottom_left_crossing == current_crossing) {
                        next_crossing->data[next_to_bottom_index] = next_crossing;
                        next_crossing->ports[next_to_bottom_index] = OPP(far_index);
                    } else {
                        next_crossing->data[next_to_bottom_index] = bottom_left_crossing;
                        next_crossing->ports[next_to_bottom_index] = bottom_left_crossing_enter_index;
                    }

                    delete_crossing(&top_middle_crossing);
                    delete_crossing(&bottom_middle_crossing);

                    number_of_simplifications++;
                }
            } 
            
            /* While we would delete top_middle_crossing and bottom_middle_crossing, this doesn't actually
             * affect the link component that we are currently traversing. This means that we can just 
             * reuse the same loop update code regardless of what happens earlier in the iteration. */

            if (current_crossing->over_component == current_crossing->under_component) {
                crossings_left_to_visit -= 1;
            } else {
                crossings_left_to_visit -= 2;
            }
            
            previous_crossing = current_crossing;
            current_crossing = current_crossing->data[next_index];
            next_index = OPP(previous_crossing->ports[next_index]);
        } while (L->number_of_crossings_in_components[component] > 0 && crossings_left_to_visit > 0);
    }

    return number_of_simplifications;
}

