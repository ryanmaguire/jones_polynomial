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

//
//
//
//
//
//
//
//
//
//
//
//
//

enum boolean null_gamma(struct link* L) 
{
    for (int component = 0; component < L->number_of_components; component++) {
        if (L->number_of_crossings_in_components[component] <= 2) {
            continue;
        }

        int next_index = 2;
        struct crossing* current_crossing = L->first_crossing_in_components[component];
        struct crossing* previous_crossing = current_crossing->data[OPP(next_index)];
        do {
            struct crossing* next_crossing = current_crossing->data[next_index];
            int far_index = OPP(current_crossing->ports[next_index]);

            if (
                (current_crossing->data[PREV(next_index)] == next_crossing || current_crossing->data[NEXT(next_index)] == next_crossing)
                && (next_crossing->data[far_index] == previous_crossing)
                && ((next_index % 2) != (far_index % 2) && (current_crossing->ports[OPP(next_index)] % 2) == (next_index % 2))
            ) {
                int former_crossing_index = previous_crossing->ports[OPP(current_crossing->ports[OPP(next_index)])];
                struct crossing* former_crossing = previous_crossing->data[OPP(current_crossing->ports[OPP(next_index)])];

                int very_far_crossing_index = previous_crossing->ports[OPP(next_crossing->ports[OPP(far_index)])];
                struct crossing* very_far_crossing = previous_crossing->data[OPP(next_crossing->ports[OPP(far_index)])];

                int side_crossing_index = 
                    (current_crossing->data[NEXT(next_index)] == next_crossing) ? 
                        PREV(next_index) :
                        NEXT(next_index);
                struct crossing* side_crossing = current_crossing->data[side_crossing_index];

                int different_side_crossing_index = 
                    (next_crossing->data[NEXT(far_index)] == current_crossing) ?
                        PREV(far_index) :
                        NEXT(far_index);
                struct crossing* different_side_crossing = next_crossing->data[]
            } else {
                previous_crossing = current_crossing;
                current_crossing = current_crossing->data[next_index];
                next_index = OPP(previous_crossing->ports[next_index]);
            }
        } while (L->number_of_crossings_in_components[component] > 0 && current_crossing != L->first_crossing_in_components[component]);
    }

    return -1;
}

