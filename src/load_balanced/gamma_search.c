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

int gamma_search(const struct link* L){
    int counter;//Which component are we searching?
    struct crossing* current_crossing;//Current crossing in search
    struct crossing* next_crossing;//Next crossing in search
    int direction;//Direction of travel in search
    int found = 0;//Have we found gammas yet? 0 = no, 1 = yes
    int dir;// Direction from current_crossing two second crossing of gamma
    for (counter = 0; counter < L->number_of_components; counter++){//Iterate over components
        current_crossing = L->first_crossing_in_components[counter];//Current crossing should be in the counter-th component
        direction = (current_crossing->over_component == counter) ? 1 : 0;//Make sure that you're going in the right direction
        do {
            for (dir = 0; dir <4; dir++){//Check all four directions from current crossing
                if (current_crossing->data[dir]->data[(current_crossing->ports[dir]+1)%4] == current_crossing && (dir + current_crossing->ports[dir])%2 == 1){//Bigon??
                    if((current_crossing->data[(dir+1)%4] == current_crossing->data[dir]->data[(current_crossing->ports[dir]+3)&4] && (current_crossing->ports[(dir+1)%4] + current_crossing->data[dir]->ports[(current_crossing->ports[dir]+3)&4])%2 == 0) || (current_crossing->data[(dir+2)%4] == current_crossing->data[dir]->data[(current_crossing->ports[dir]+2)&4] && (current_crossing->ports[(dir+2)%4] + current_crossing->data[dir]->ports[(current_crossing->ports[dir]+2)&4])%2 == 0)){//Check whether the two other strands intersect to form a gamma: 2 cases
                        found = 1;//We've found a gamma!
                    }
                    
                }
            }
            if (found == 1){//If we've found a gamma
                L->first_crossing_in_components[counter] = current_crossing;//Set first crossing of component to current crossing (for easy passing to smoothing function)
                return counter;//Return component number
            }
            next_crossing = current_crossing->data[direction];//Get next crossing
            direction = OPP(current_crossing->ports[direction]);//Update direction
            current_crossing = next_crossing;// Move to next crossing
        } while (!(current_crossing == L->first_crossing_in_components[counter] && direction == ((current_crossing->over_component == counter) ? 1 : 0)));//End if we've looped all the way around the component
    }
    if (found == 0){
        return -1;
    }
}

