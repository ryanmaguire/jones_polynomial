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

/* Function to scan for and perform all null gamma untwists */
/* If found, the null gamma is untwisted, and the function continues searching with the next crossing */
/* Leaves behind 0 in number_of_crossings_in_components if an unknot diagram is created */

// previous_crossing and current_crossing must share an over/under strand
// next_crossing and previous_crossing also share an over/under strand
// after twisting, a bigon is left
//
//                                  (very_far_crossing)    (former_crossing)                
//                                                  \\      /
//                                                   \\    /
//                                                    \\  /
//                                              (previous_crossing)
//                                                    /  \\
//                                                   /    \\
//                                                  /    far_index
//                                                 /        \\
//                (side_crossing)---(current_crossing)------(next_crossing)---(different_side_crossing)
//                                                 \         //
//                                              next_index  //      
//                                                   \     //          
//                                                    \   //             
//                                                     \ //  
int null_gamma(struct link* L, int* const writhe) 
{
    int number_of_simplifications = 0;

    for (int component = 0; component < L->number_of_components; component++) {
        if (L->number_of_crossings_in_components[component] <= 2) {
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
                (current_crossing->data[PREV(next_index)] == next_crossing || current_crossing->data[NEXT(next_index)] == next_crossing)
                && (next_crossing->data[far_index] == previous_crossing)
                && ((next_index % 2) != (far_index % 2) && (current_crossing->ports[OPP(next_index)] % 2) == (next_index % 2))
            ) {
                int former_crossing_index = OPP(current_crossing->ports[OPP(next_index)]);
                struct crossing* former_crossing = previous_crossing->data[former_crossing_index];

                int very_far_crossing_index = OPP(next_crossing->ports[far_index]);
                struct crossing* very_far_crossing = previous_crossing->data[very_far_crossing_index];

                int side_crossing_index = 
                    (current_crossing->data[NEXT(next_index)] == next_crossing) ? 
                        PREV(next_index) :
                        NEXT(next_index);
                struct crossing* side_crossing = current_crossing->data[side_crossing_index];

                int different_side_crossing_index = 
                    (next_crossing->data[NEXT(far_index)] == current_crossing) ?
                        PREV(far_index) :
                        NEXT(far_index);
                struct crossing* different_side_crossing = next_crossing->data[different_side_crossing_index];

                int former_crossing_enter_index = previous_crossing->ports[former_crossing_index];
                int very_far_crossing_exit_index = previous_crossing->ports[very_far_crossing_index];
                int side_crossing_exit_index = current_crossing->ports[side_crossing_index];
                int different_side_crossing_exit_index = next_crossing->ports[different_side_crossing_index];

                *writhe += ((former_crossing_index + very_far_crossing_index) % 4 == 1) ? 1 : -1;

                if (former_crossing == next_crossing) {
                    /* weird edge case */
                    current_crossing->data[OPP(next_index)] = current_crossing;
                    current_crossing->ports[OPP(next_index)] = OPP(side_crossing_index);
                } else {
                    current_crossing->data[OPP(next_index)] = former_crossing;
                    current_crossing->ports[OPP(next_index)] = former_crossing_enter_index;
                    former_crossing->data[former_crossing_enter_index] = current_crossing;
                    former_crossing->ports[former_crossing_enter_index] = OPP(next_index);
                }

                if (very_far_crossing == current_crossing) {
                    /* weird edge case */
                    next_crossing->data[far_index] = next_crossing;
                    next_crossing->ports[far_index] = OPP(different_side_crossing_index);
                } else {
                    next_crossing->data[far_index] = very_far_crossing;
                    next_crossing->ports[far_index] = very_far_crossing_exit_index;
                    very_far_crossing->data[very_far_crossing_exit_index] = next_crossing;
                    very_far_crossing->ports[very_far_crossing_exit_index] = far_index;
                }

                current_crossing->data[side_crossing_index] = next_crossing;
                current_crossing->ports[side_crossing_index] = different_side_crossing_index;
                if (side_crossing != previous_crossing && side_crossing != next_crossing) {
                    /* no weird edge case */
                    side_crossing->data[side_crossing_exit_index] = next_crossing;
                    side_crossing->ports[side_crossing_exit_index] = OPP(different_side_crossing_index);
                }

                next_crossing->data[different_side_crossing_index] = current_crossing;
                next_crossing->ports[different_side_crossing_index] = side_crossing_index;
                if (different_side_crossing != previous_crossing && different_side_crossing != current_crossing) {
                    /* no weird edge case */
                    different_side_crossing->data[different_side_crossing_exit_index] = current_crossing;
                    different_side_crossing->ports[different_side_crossing_exit_index] = OPP(side_crossing_index);
                }

                int new_side_crossing_index = OPP(different_side_crossing_index);
                int new_different_side_crossing_index = OPP(side_crossing_index);

                if (side_crossing == previous_crossing) {
                    /* weird edge case */
                    next_crossing->data[new_side_crossing_index] = next_crossing;
                    next_crossing->ports[new_side_crossing_index] = far_index;
                } else if (side_crossing == next_crossing) {
                    /* other weird edge case */
                    next_crossing->data[new_side_crossing_index] = current_crossing;
                    next_crossing->ports[new_side_crossing_index] = new_different_side_crossing_index;
                } else {
                    next_crossing->data[new_side_crossing_index] = side_crossing;
                    next_crossing->ports[new_side_crossing_index] = side_crossing_exit_index;
                }

                if (different_side_crossing == previous_crossing) {
                    /* weird edge case */
                    current_crossing->data[new_different_side_crossing_index] = current_crossing;
                    current_crossing->ports[new_different_side_crossing_index] = OPP(next_index);
                } else if (different_side_crossing == current_crossing) {
                    /* other weird edge case */
                    current_crossing->data[new_different_side_crossing_index] = next_crossing;
                    current_crossing->ports[new_different_side_crossing_index] = new_side_crossing_index;
                } else {
                    current_crossing->data[new_different_side_crossing_index] = different_side_crossing;
                    current_crossing->ports[new_different_side_crossing_index] = different_side_crossing_exit_index;
                }

                L->number_of_crossings_in_components[component]--;
                if (L->first_crossing_in_components[component] == previous_crossing) {
                    L->first_crossing_in_components[component] = (former_crossing == next_crossing) ? very_far_crossing : former_crossing;
                }

                crossings_left_to_visit -= 2;

                next_index = OPP(very_far_crossing_exit_index);
                delete_crossing(&previous_crossing);
                previous_crossing = next_crossing;
                current_crossing = very_far_crossing;

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

