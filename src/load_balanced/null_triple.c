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

//
//
//
//
//
//
//         -------------------------------------------------
//
//
//
//
//
//

enum boolean null_triple(struct link* L) 
{
    for (int component = 0; component < L->number_of_components; component++) {
        if (L->number_of_crossings_in_components[component] <= 2) { // change later
            continue;
        }

        int next_index = 2;
        struct crossing* current_crossing = L->first_crossing_in_components[component];
        struct crossing* previous_crossing = current_crossing->data[OPP(next_index)];
        do {
            
        } while (L->number_of_crossings_in_components[component] > 0 && current_crossing != L->first_crossing_in_components[component]);
    }

    return -1;
}

