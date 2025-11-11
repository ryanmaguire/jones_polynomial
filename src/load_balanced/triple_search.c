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

int triple_search(const struct link* L) 
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
                
            ) {
                L->first_crossing_in_components[component] = current_crossing;
                return component;
            }
            previous_crossing = current_crossing;
            current_crossing = current_crossing->data[next_index];
            next_index = OPP(previous_crossing->ports[next_index]);
        } while (
            /* Edge case check to make sure we aren't trying to do stuff to an unknot */
            L->number_of_crossings_in_components[component] > 0 
            /* Keep on looping until we go around the link */
            && current_crossing != L->first_crossing_in_components[component]
        );
    }

    return -1;
}
