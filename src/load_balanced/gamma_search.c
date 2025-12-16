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

/* Function to search for the first occurence of a gamma */
/* If found, returns the component number and sets the crossing as the first crossing of the component */
/* If not found, L is unchanged and -1 is returned */

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

int gamma_search(const struct link* L)
{
    struct crossing* current_crossing;//Current crossing in search
    struct crossing* next_crossing;//Next crossing in search
    int direction;//Direction of travel in search
    int dir;// Direction from current_crossing two second crossing of gamma
    for (size_t component = 0; component < L->number_of_components; component++){//Iterate over components

        // This will be decremented by 1 if the crossing will be visitied twice, by 2 otherwise
        size_t crossings_left_to_visit = 2 * L->number_of_crossings_in_components[component];

        current_crossing = L->first_crossing_in_components[component];//Current crossing should be in the current component
        direction = (current_crossing->over_component == component) ? 1 : 0;//Make sure that you're going in the right direction
        do {
            for (dir = 0; dir <4; dir++){//Check all four directions from current crossing
                if (current_crossing->data[dir]->data[(current_crossing->ports[dir]+1)%4] == current_crossing && (dir + current_crossing->ports[dir])%2 == 1){//Bigon??
                    if((current_crossing->data[(dir+1)%4] == current_crossing->data[dir]->data[(current_crossing->ports[dir]+3)%4] && (current_crossing->ports[(dir+1)%4] + current_crossing->data[dir]->ports[(current_crossing->ports[dir]+3)%4])%2 == 0) || (current_crossing->data[(dir+2)%4] == current_crossing->data[dir]->data[(current_crossing->ports[dir]+2)%4] && (current_crossing->ports[(dir+2)%4] + current_crossing->data[dir]->ports[(current_crossing->ports[dir]+2)%4])%2 == 0)){//Check whether the two other strands intersect to form a gamma: 2 cases
                        L->first_crossing_in_components[component] = current_crossing;//Set first crossing of component to current crossing (for easy passing to smoothing function)
                        return component;//Return component number
                    }

                }
            }

            if (current_crossing->over_component == current_crossing->under_component) {
                crossings_left_to_visit -= 1;
            } else {
                crossings_left_to_visit -= 2;
            }

            next_crossing = current_crossing->data[direction];//Get next crossing
            direction = OPP(current_crossing->ports[direction]);//Update direction
            current_crossing = next_crossing;// Move to next crossing
        } while (crossings_left_to_visit > 0);
    }

    return -1;
}

